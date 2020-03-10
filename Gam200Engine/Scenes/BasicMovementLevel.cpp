/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BasicMovementLevel.cpp
Author
    - Sinil.Kang            rtd99062@gmail.com
    - Hyerin.Jung       junghl0621@gmail.com

Creation Date: 12.10.2019

    Source file for level that player learned how to move player
******************************************************************************/
#include <thread>
#include <Scenes/BasicMovementLevel.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include <States/Walking.hpp>
#include <Object/Players/Player.h>
#include <Component/Sprite/TextComponent.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>

#include <Graphics/GL.hpp>


SoundManager TestBGMSoundForDebugMode;
BasicMovementLevel::BasicMovementLevel(): background(nullptr)
{
}

BasicMovementLevel::~BasicMovementLevel()
{
}

void BasicMovementLevel::Load()
{
    fileIO* a = 0;
    a->Input("../assets/fileIO/saveloadFile.txt");

    //Loading image only
	cameraManager.Init();
   auto objManager = ObjectManager::GetObjectManager();
   loadingScene = new Object();
   loadingScene->SetObjectName("loadingScene");
   loadingScene->SetTranslation(vector2{ 1.f });
   loadingScene->SetScale(vector2{ 2000.f });
   loadingScene->AddComponent(new Sprite(loadingScene));
   loadingScene->GetComponentByTemplate<Sprite>()->SetColor(Graphics::Color4f(0));
   loadingScene->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");
   loadingScene->SetDepth(-0.f);

   Object* loadingText = new Object();
   loadingText->SetObjectName("Loading Text");
   loadingText->SetTranslation(vector2{ -100.f });
   loadingText->AddComponent(new TextComponent(loadingText));
   loadingText->GetComponentByTemplate<TextComponent>()->SetString(L"Loading");
   loadingText->SetDepth(-0.9f);

   //Worker Thread here
   GLFWwindow* context = glfwGetCurrentContext();
   HDC hdc = GetDC(glfwGetWin32Window(context));
   HGLRC offscreen_context = wglCreateContext(hdc);

   BOOL error = wglShareLists(glfwGetWGLContext(context), offscreen_context);
   if (error == FALSE)
   {
	   printf("Something is wrong!");
   }
   glfwMakeContextCurrent(NULL);

   std::thread first([&]()
	   {
		   wglMakeCurrent(hdc, offscreen_context);
		   unsigned int cnt = 0;
		   unsigned int cnt2 = 0;
		   while (isLoadingDone == false)
		   {
			   // Update loading data
			   ++cnt;
			   ++cnt2;

			   if (cnt2 % 1500 == 0)
			   {
				   loadingText->GetComponentByTemplate<TextComponent>()->SetString(L"Loading");
			   }
			   if (cnt % 500 == 0)
			   {
				   std::wstring string = loadingText->GetComponentByTemplate<TextComponent>()->GetString();
				   loadingText->GetComponentByTemplate<TextComponent>()->SetString(string + L"...");
			   }

			   Graphics::GL::begin_drawing();

			   // LoadingScene
			   const auto matrix = cameraManager.GetWorldToNDCTransform() * loadingScene->GetTransform().GetModelToWorld();
			   Sprite* sprite = loadingScene->GetComponentByTemplate<Sprite>();
			   sprite->UpdateUniforms(matrix,
				   loadingScene->GetTransform().CalculateWorldDepth());
			   Graphics::GL::draw(*sprite->GetVertices(), *sprite->GetMaterial());

			   // Loading Text
			   const auto matrix2 = cameraManager.GetWorldToNDCTransform() * loadingText->GetTransform().GetModelToWorld();
			   loadingText->GetComponentByTemplate<TextComponent>()->Draw(matrix2,
				   loadingText->GetTransform().CalculateWorldDepth());


			   Graphics::GL::end_drawing();

			   SwapBuffers(hdc);
		   }

		   wglMakeCurrent(nullptr, nullptr);
		   wglDeleteContext(offscreen_context);
	   });

   glfwMakeContextCurrent(context);
   BasicMovementLevel::InitObject();

    TestBGMSoundForDebugMode.Load_Sound();
    TestBGMSoundForDebugMode.Play_Sound(SOUNDS::BACKGROUND_SOUND);
    TestBGMSoundForDebugMode.SetVolume(BACKGROUND_SOUND, 0.2f);

   isLoadingDone = true;

   first.join();
}

void BasicMovementLevel::Update(float /*dt*/)
{
    BasicMovementLevel::Input();
    BasicMovementLevel::Collision();

    vector2 obj1Position = player1->GetComponentByTemplate<Physics>()->GetPosition();
    vector2 obj2Position = player2->GetComponentByTemplate<Physics>()->GetPosition();

    player1->SetTranslation(obj1Position);
    player2->SetTranslation(obj2Position);

    cameraManager.CameraMove(player1, player2, 1.1f);
}

void BasicMovementLevel::GameRestart()
{
}

void BasicMovementLevel::Unload()
{
	fileIO* a = 0;
	a->Output("../assets/fileIO/saveloadFile.txt");
}

void BasicMovementLevel::Input()
{
    if (input.IsKeyTriggered(GLFW_KEY_G))
    {
        if (player1->GetComponentByTemplate<Physics>()->GetIsGhost() == true)
        {
            player1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(false);
        }
        else
        {
            player1->GetComponentByTemplate<Physics>()->ActiveGhostCollision(true);
        }
    }

}

void BasicMovementLevel::Collision()
{
    player1->GetComponentByTemplate<Physics>()->ManageCollision();
}

void BasicMovementLevel::InitObject() {

    background = new Object();
    background->SetObjectName("background1");
    background->SetTranslation(vector2{ 1.f });
    background->SetScale(vector2{ 1000.f });
    background->AddComponent(new Sprite(background));
    background->AddComponent(new Physics(background));
    background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

	player1 = new Player(Player::Identifier::Player1);

	player2 = new Player(Player::Identifier::Player2);

    string = new String(player1, player2);
    string->SetDepth(-0.9f);

    goalPoint = new Object();
    goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    goalPoint->SetObjectName("goalPoint");
    goalPoint->SetTranslation(vector2{ 0.f, 500.f });
    goalPoint->SetScale(vector2{ 150.f });
    goalPoint->AddComponent(new Sprite(goalPoint));
	goalPoint->AddComponent(new GoalComponent(goalPoint, "OneWayPassLevel"));
    goalPoint->AddComponent(new Physics(goalPoint));
    goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
    goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
    goalPoint->SetDepth(-1.f);

    startPoint = new Object();
    startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
    startPoint->SetObjectName("startPoint");
    startPoint->SetTranslation(vector2{ 0.f, -500.f });
    startPoint->SetScale(vector2{ 150.f });
    startPoint->AddComponent(new Sprite(startPoint));
	startPoint->AddComponent(new GoalComponent(startPoint, "OneWayPassLevel"));
    startPoint->AddComponent(new Physics(startPoint));
    startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
    startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
    startPoint->SetDepth(-1.f);

	ObjectManager* objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(player2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(string);
	objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
	objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);

}

void AddStateTestObject()
{
	Object* obj = new Object();
	obj->SetObjectName("FSM test object");
	obj->SetDepth(-20.f);
	obj->AddComponent(new Sprite(obj));
	obj->AddComponent(new StateMachine<Object>(obj));
	obj->GetComponentByTemplate<StateMachine<Object>>()->SetGlobalState(new Walking());
	obj->SetScale(100.f);
	ObjectManager::GetObjectManager()->FindLayer(Stage)->AddObject(obj);
}