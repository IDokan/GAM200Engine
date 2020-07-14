/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   HowtoPlay.cpp
Author
	- jjwon6218@gmail.com
Creation Date: 05.29.2020

	cpp file for how to play level
******************************************************************************/
#include <Scenes/HowtoPlay.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include "Component/Button.hpp"
#include "Object/DepthStandard.hpp"
#include <Scenes/SceneManager.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include <Component/Sprite/TextComponent.hpp>

HowToPlay::HowToPlay()
{
    isMenu = true;
}

HowToPlay::~HowToPlay()
{

}

void HowToPlay::Load()
{
	HowToPlay::InitObject();
	cameraManager.Init();
	SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::HOWTOPLAY_MAIN_BGM);
}

void HowToPlay::Update(float dt)
{
	float currXaxis = cameraManager.GetPosition().x;
	if ((input.IsKeyTriggered(GLFW_KEY_LEFT) || input.IsKeyTriggered(GLFW_KEY_A)) && cameraManager.GetPosition().x > 0.0f)
	{
		cameraManager.SetPosition(vector2{ currXaxis - 1500.f, 0.f });
	}
	if ((input.IsKeyTriggered(GLFW_KEY_RIGHT) || input.IsKeyTriggered(GLFW_KEY_D)) && cameraManager.GetPosition().x < 4500.0f)
	{
		cameraManager.SetPosition(vector2{ currXaxis + 1500.f, 0.f });
	}

	HowToPlay::Input();
}

void HowToPlay::GameRestart()
{

}

void HowToPlay::Unload()
{
}

void HowToPlay::Input()
{
	if (input.IsAnyKeyTriggered() && !input.IsKeyTriggered(GLFW_KEY_LEFT) && !input.IsKeyTriggered(GLFW_KEY_RIGHT) && !input.IsKeyTriggered(GLFW_KEY_A) && !input.IsKeyTriggered(GLFW_KEY_D))
	{
		SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().Play_Sound(SOUNDS::UNDO_SOUND);
        SceneManager::GetSceneManager()->SetNextScene("MenuScene");
	}
}

void HowToPlay::Collision()
{
}

void HowToPlay::InitObject()
{
	//Movement part
	movementIndicator1 = new Object();
	movementIndicator1->SetObjectName("movementIndicator1");
	movementIndicator1->SetTranslation(vector2{ -200.f, 200.f });
	movementIndicator1->SetScale(vector2{ 280.f, 235.f });
	movementIndicator1->AddComponent(new Sprite(movementIndicator1));
	movementIndicator1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/wasdSign.png");
	movementIndicator1->SetObjectType(Object::ObjectType::TEST);
	movementIndicator1->SetDepth(Depth_Standard::WoodSign);

	movementIndicator2 = new Object();
	movementIndicator2->SetObjectName("movementIndicator2");
	movementIndicator2->SetTranslation(vector2{ 200.f, 200.f });
	movementIndicator2->SetScale(vector2{ 280.f, 235.f });
	movementIndicator2->AddComponent(new Sprite(movementIndicator2));
	movementIndicator2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/arrowSign.png");
	movementIndicator2->SetObjectType(Object::ObjectType::TEST);
	movementIndicator2->SetDepth(Depth_Standard::WoodSign);

	movementExplanation = new Object();
	movementExplanation->SetObjectName("movementExplanation");
	movementExplanation->SetTranslation(vector2{ 0.f, -50.f });
	movementExplanation->SetScale(vector2{ 500.f, 125.f });
	movementExplanation->AddComponent(new Sprite(movementExplanation));
	movementExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay1.png");
	movementExplanation->SetObjectType(Object::ObjectType::TEST);
	movementExplanation->SetDepth(Depth_Standard::WoodSign);

	rightArrow = new Object();
	rightArrow->SetObjectName("movementExplanation");
	rightArrow->SetTranslation(vector2{ 0.f, -250.f });
	rightArrow->SetScale(vector2{ 100.f, 100.f });
	rightArrow->AddComponent(new Sprite(rightArrow));
	rightArrow->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/rightarrow.png");
	rightArrow->SetObjectType(Object::ObjectType::TEST);
	rightArrow->SetDepth(Depth_Standard::WoodSign);

	Object* quarter = new Object();
	TextComponent* quarterText = new TextComponent(quarter);
	quarter->SetTranslation(vector2{ 650.f, 400.f });
	quarter->AddComponent(quarterText);
	quarterText->SetString(L"1/4");
	quarter->SetObjectName("quarter");

	//Size part
	sizeIndicator = new Object();
	sizeIndicator->SetObjectName("sizeIndicator");
	sizeIndicator->SetTranslation(vector2{ 1500.f, 200.f });
	sizeIndicator->SetScale(vector2{ 338.f, 276.f });
	Animation* animation = new Animation(sizeIndicator);
	sizeIndicator->AddComponent(animation);
	animation->SetImage("../assets/textures/sizeSign.png");
	animation->SetNumOfState(1);
	animation->SetSpeed(2.5f);
	animation->SetFrame(6);
	sizeIndicator->SetObjectType(Object::ObjectType::TEST);
	sizeIndicator->SetDepth(Depth_Standard::WoodSign);

	sizeExplanation = new Object();
	sizeExplanation->SetObjectName("sizeExplanation");
	sizeExplanation->SetTranslation(vector2{ 1500.f, -50.f });
	sizeExplanation->SetScale(vector2{ 625.f, 125.f });
	sizeExplanation->AddComponent(new Sprite(sizeExplanation));
	sizeExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay2.png");
	sizeExplanation->SetObjectType(Object::ObjectType::TEST);
	sizeExplanation->SetDepth(Depth_Standard::WoodSign);

	arrows1 = new Object();
	arrows1->SetObjectName("arrows1");
	arrows1->SetTranslation(vector2{ 1500.f, -250.f });
	arrows1->SetScale(vector2{ 375.f, 100.f });
	arrows1->AddComponent(new Sprite(arrows1));
	arrows1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/nextpage.png");
	arrows1->SetObjectType(Object::ObjectType::TEST);
	arrows1->SetDepth(Depth_Standard::WoodSign);

	Object* twoquarter = new Object();
	TextComponent* twoquarterText = new TextComponent(twoquarter);
	twoquarter->SetTranslation(vector2{ 2150.f, 400.f });
	twoquarter->AddComponent(twoquarterText);
	twoquarterText->SetString(L"2/4");
	twoquarter->SetObjectName("twoquarter");

	//Movable box part
	movableBox = new Object();
	movableBox->SetObjectName("movableBox");
	movableBox->SetTranslation(vector2{ 3200.f, 200.f });
	movableBox->SetScale(vector2{ 100.f, 100.f });
	movableBox->AddComponent(new Sprite(movableBox));
	movableBox->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object.png");
	movableBox->SetObjectType(Object::ObjectType::TEST);
	movableBox->SetDepth(Depth_Standard::WoodSign);

    movableBox1 = new Object();
    movableBox1->SetObjectName("movableBox");
    movableBox1->SetTranslation(vector2{ 2800.f, 200.f });
    movableBox1->SetScale(vector2{ 100.f, 100.f });
    movableBox1->AddComponent(new Sprite(movableBox1));
    movableBox1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/moving_object_UP.png");
    movableBox1->SetObjectType(Object::ObjectType::TEST);
    movableBox1->SetDepth(Depth_Standard::WoodSign);

	movableBoxExplanation = new Object();
	movableBoxExplanation->SetObjectName("movableBoxExplanation");
	movableBoxExplanation->SetTranslation(vector2{ 3000.f, -50.f });
	movableBoxExplanation->SetScale(vector2{ 625.f, 125.f });
	movableBoxExplanation->AddComponent(new Sprite(movableBoxExplanation));
	movableBoxExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay3.png");
	movableBoxExplanation->SetObjectType(Object::ObjectType::TEST);
	movableBoxExplanation->SetDepth(Depth_Standard::WoodSign);

	arrows2 = new Object();
	arrows2->SetObjectName("arrows2");
	arrows2->SetTranslation(vector2{ 3000.f, -250.f });
	arrows2->SetScale(vector2{ 375.f, 100.f });
	arrows2->AddComponent(new Sprite(arrows2));
	arrows2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/nextpage.png");
	arrows2->SetObjectType(Object::ObjectType::TEST);
	arrows2->SetDepth(Depth_Standard::WoodSign);

	Object* threequarter = new Object();
	TextComponent* threequarterText = new TextComponent(threequarter);
	threequarter->SetTranslation(vector2{ 3650.f, 400.f });
	threequarter->AddComponent(threequarterText);
	threequarterText->SetString(L"3/4");
	threequarter->SetObjectName("threequarter");

	//Checkpoint part
	checkpoint = new Object();
	checkpoint->SetObjectName("checkpoint");
	checkpoint->SetTranslation(vector2{ 4300.f, 200.f });
	checkpoint->SetScale(vector2{ 300.f, 300.f });
	checkpoint->AddComponent(new Sprite(checkpoint));
	checkpoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/closedFridge.png");
	checkpoint->SetObjectType(Object::ObjectType::TEST);
	checkpoint->SetDepth(Depth_Standard::WoodSign);

	checkpoint1 = new Object();
	checkpoint1->SetObjectName("checkpoint");
	checkpoint1->SetTranslation(vector2{ 4700.f, 200.f });
	checkpoint1->SetScale(vector2{ 300.f, 300.f });
	checkpoint1->AddComponent(new Sprite(checkpoint1));
	checkpoint1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/openedFridge.png");
	checkpoint1->SetObjectType(Object::ObjectType::TEST);
	checkpoint1->SetDepth(Depth_Standard::WoodSign);

	checkpointExplanation = new Object();
	checkpointExplanation->SetObjectName("checkpointExplanation");
	checkpointExplanation->SetTranslation(vector2{ 4500.f, -50.f });
	checkpointExplanation->SetScale(vector2{ 500.f, 125.f });
	checkpointExplanation->AddComponent(new Sprite(checkpointExplanation));
	checkpointExplanation->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/howtoplay4.png");
	checkpointExplanation->SetObjectType(Object::ObjectType::TEST);
	checkpointExplanation->SetDepth(Depth_Standard::WoodSign);

	leftArrow = new Object();
	leftArrow->SetObjectName("leftArrow");
	leftArrow->SetTranslation(vector2{ 4500.f, -250.f });
	leftArrow->SetScale(vector2{ 100.f, 100.f });
	leftArrow->AddComponent(new Sprite(leftArrow));
	leftArrow->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/leftarrow.png");
	leftArrow->SetObjectType(Object::ObjectType::TEST);
	leftArrow->SetDepth(Depth_Standard::WoodSign);

	Object* fourquarter = new Object();
	TextComponent* fourquarterText = new TextComponent(fourquarter);
	fourquarter->SetTranslation(vector2{ 5150.f, 400.f });
	fourquarter->AddComponent(fourquarterText);
	fourquarterText->SetString(L"4/4");
	fourquarter->SetObjectName("fourquarter");

	press = new Object();
	press->SetObjectName("press");
	press->SetTranslation(vector2(200, -400));
	TextComponent* text = new TextComponent(press);
	press->AddComponent(text);
	text->SetString(L"Press Left or Right to Move Page \n Press Other Keys to Main Menu");
	press->SetObjectName("press");

	press1 = new Object();
	press1->SetObjectName("press1");
	press1->SetTranslation(vector2(1700, -400));
	TextComponent* text1 = new TextComponent(press1);
	press1->AddComponent(text1);
	text1->SetString(L"Press Left or Right to Move Page \n Press Other Keys to Main Menu");
	press1->SetObjectName("press1");

	press2 = new Object();
	press2->SetObjectName("press2");
	press2->SetTranslation(vector2(3200, -400));
	TextComponent* text2 = new TextComponent(press2);
	press2->AddComponent(text2);
	text2->SetString(L"Press Left or Right to Move Page \n Press Other Keys to Main Menu");
	press2->SetObjectName("press2");

	press3 = new Object();
	press3->SetObjectName("press3");
	press3->SetTranslation(vector2(4700, -400));
	TextComponent* text3 = new TextComponent(press3);
	press3->AddComponent(text3);
	text3->SetString(L"Press Left or Right to Move Page \n Press Other Keys to Main Menu");
	press3->SetObjectName("press3");
	////Object manager part
	auto objManager = ObjectManager::GetObjectManager();

	objManager->FindLayer(LayerNames::Stage)->AddObject(movementIndicator1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movementIndicator2);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movementExplanation);
	objManager->FindLayer(LayerNames::Stage)->AddObject(rightArrow);
	objManager->FindLayer(LayerNames::Stage)->AddObject(quarter);

	objManager->FindLayer(LayerNames::Stage)->AddObject(sizeIndicator);
	objManager->FindLayer(LayerNames::Stage)->AddObject(sizeExplanation);
	objManager->FindLayer(LayerNames::Stage)->AddObject(arrows1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(twoquarter);

	objManager->FindLayer(LayerNames::Stage)->AddObject(movableBox);
    objManager->FindLayer(LayerNames::Stage)->AddObject(movableBox1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(movableBoxExplanation);
	objManager->FindLayer(LayerNames::Stage)->AddObject(arrows2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(threequarter);

	objManager->FindLayer(LayerNames::Stage)->AddObject(checkpoint);
	objManager->FindLayer(LayerNames::Stage)->AddObject(checkpoint1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(checkpointExplanation);
	objManager->FindLayer(LayerNames::Stage)->AddObject(leftArrow);
	objManager->FindLayer(LayerNames::Stage)->AddObject(fourquarter);

	objManager->FindLayer(LayerNames::Stage)->AddObject(press);
	objManager->FindLayer(LayerNames::Stage)->AddObject(press1);
	objManager->FindLayer(LayerNames::Stage)->AddObject(press2);
	objManager->FindLayer(LayerNames::Stage)->AddObject(press3);
}
