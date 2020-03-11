/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Editor.cpp
Author
	- Jiwon Jung jjwon6218@gmail.com

Creation Date: 1.7.2020

	Source file for editor
******************************************************************************/
#include <Scenes/Editor.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Object/Object.hpp>
#include <Object/Strings/String.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>

//void ObjectSelectionChecker(vector2 mousePos);

Editor::Editor(): mousePosX(0.0f), mousePosY(0.0f), background(nullptr), objectSwitch(chosenObject::obstacle)
{

}

Editor::~Editor()
{
	objectNum = 0;
	objectName.clear();
}

void Editor::GameRestart()
{
}

void Editor::Load()
{
	//fileIO* a = 0;
	//a->Input("../assets/fileIO/saveloadFile.txt");
	
	Editor::InitObject();

	cameraManager.Init();

	objectSwitch = chosenObject::obstacle;
	
}

void Editor::Update(float /*dt*/)
{
	Editor::Input();
}

void Editor::Unload()
{
	fileIO* a = 0;
	a->Output("../assets/fileIO/EditorCheck.txt");
}

void Editor::Input()
{
	auto objManager = ObjectManager::GetObjectManager();
	mousePosX = input.GetMouseRelativePosition().x;
	mousePosY = input.GetMouseRelativePosition().y;

	/******************** Object choosing with num pad ********************/
	if (input.IsKeyPressed(GLFW_KEY_1))
	{
		objectSwitch = chosenObject::obstacle;
	}
	else if (input.IsKeyPressed(GLFW_KEY_2))
	{
		objectSwitch = chosenObject::startpoint;
	}
	else if (input.IsKeyPressed(GLFW_KEY_3))
	{
		objectSwitch = chosenObject::goalpoint;
	}
	else if (input.IsKeyPressed(GLFW_KEY_4))
	{
		objectSwitch = chosenObject::player1;
	}
	else if (input.IsKeyPressed(GLFW_KEY_5))
	{
		objectSwitch = chosenObject::player2;
	}
	else if (input.IsKeyPressed(GLFW_KEY_6))
	{
		objectSwitch = chosenObject::adjustment;
	}

	/********************Camera Movement*********************/

	if (input.IsKeyPressed(GLFW_KEY_UP))
	{
		cameraManager.EditorCameraMoveUp(5.f);
	}
	else if (input.IsKeyPressed(GLFW_KEY_DOWN))
	{
		cameraManager.EditorCameraMoveUp(-5.f);
	}
	else if (input.IsKeyPressed(GLFW_KEY_LEFT))
	{
		cameraManager.EditorCameraMoveLeft(5.f);
	}
	else if (input.IsKeyPressed(GLFW_KEY_RIGHT))
	{
		cameraManager.EditorCameraMoveLeft(-5.f);
	}

	/******************** Creating and Adjusting objects ********************/
	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
	{
		if (objectSwitch == chosenObject::obstacle)
		{
			Object* object = new Object();
			objectName.append("obj");
			objectName.append(std::to_string(objectNum));
			++objectNum;
			object->SetObjectName(objectName);
			objectName.clear();
			object->SetTranslation(vector2{ mousePosX, mousePosY });
			object->SetScale(vector2{ 100.f, 100.f });
			object->AddComponent(new Sprite(object));
			object->AddComponent(new Physics(object));
			object->SetObjectType(Object::ObjectType::OBSTACLE);
			object->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(object, Physics::ObjectType::RECTANGLE);
			object->SetDepth(-1.f);
			objManager->FindLayer(LayerNames::Stage)->AddObject(object);
		}
		else if (objectSwitch == chosenObject::startpoint)
		{
			startPoint = new Object();
			startPoint->SetObjectName("startPoint");
			startPoint->SetTranslation(vector2{ mousePosX, mousePosY });
			startPoint->SetScale(vector2{ 150.f });
			startPoint->AddComponent(new Sprite(startPoint));
			startPoint->AddComponent(new Physics(startPoint));
			startPoint->SetObjectType(Object::ObjectType::OBSTACLE);
			startPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(startPoint, Physics::ObjectType::RECTANGLE);
			startPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/startPoint.png");
			startPoint->SetDepth(-1.f);
			objManager->FindLayer(LayerNames::Stage)->AddObject(startPoint);
		}
		else if (objectSwitch == chosenObject::goalpoint)
		{
			goalPoint = new Object();
			goalPoint->SetObjectType(Object::ObjectType::OBSTACLE);
			goalPoint->SetObjectName("goalPoint");
			goalPoint->SetTranslation(vector2{ mousePosX, mousePosY });
			goalPoint->SetScale(vector2{ 150.f });
			goalPoint->AddComponent(new Sprite(goalPoint));
			goalPoint->AddComponent(new GoalComponent(goalPoint, "BasicmovementLevel"));
			goalPoint->AddComponent(new Physics(goalPoint));
			goalPoint->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(goalPoint, Physics::ObjectType::RECTANGLE);
			goalPoint->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/goalPoint.png");
			goalPoint->SetDepth(-1.f);
			objManager->FindLayer(LayerNames::Stage)->AddObject(goalPoint);
		}
		else if (objectSwitch == chosenObject::player1)
		{
			player1 = new Object();
			player1->SetObjectType(Object::ObjectType::PLAYER_1);
			player1->SetObjectName("player1");
			player1->SetTranslation(vector2{ mousePosX, mousePosY });
			player1->SetScale(vector2{ 150.f });
			player1->AddComponent(new Sprite(player1));
			player1->AddComponent(new Physics(player1));
			player1->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p1.png");
			player1->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player1, Physics::ObjectType::RECTANGLE);
			player1->SetDepth(-1.f);
			objManager->FindLayer(LayerNames::Stage)->AddObject(player1);
		}
		else if (objectSwitch == chosenObject::player2)
		{
			player2 = new Object();
			player2->SetObjectName("player2");
			player2->SetObjectType(Object::ObjectType::PLAYER_2);
			player2->SetTranslation(vector2{ mousePosX, mousePosY });
			player2->SetScale(vector2{ 150.f });
			player2->AddComponent(new Sprite(player2));
			player2->AddComponent(new Physics(player2));
			player2->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/p2.png");
			player2->GetComponentByTemplate<Physics>()->SetCollisionBoxAndObjectType(player2, Physics::ObjectType::RECTANGLE);
			player2->SetDepth(-1.f);
			objManager->FindLayer(LayerNames::Stage)->AddObject(player2);

			string = new String(player1, player2);
			objManager->FindLayer(LayerNames::Stage)->AddObject(string);
		}
		else if (objectSwitch == chosenObject::adjustment)
		{
			/*vector2 currMousePosition = input.GetMouseRelativePosition();
			ObjectSelectionChecker(currMousePosition);*/
		}
	}
}
void Editor::InitObject() 
{
	background = new Object();
	background->SetObjectName("background");
	background->SetTranslation(vector2{ 1.f });
	background->SetScale(vector2{ 1500.f });
	background->AddComponent(new Sprite(background));
	background->AddComponent(new Physics(background));
	background->GetComponentByTemplate<Sprite>()->SetImage("../assets/textures/table.png");

	auto objManager = ObjectManager::GetObjectManager();
	objManager->FindLayer(LayerNames::BackGround)->AddObject(background);
}

//void ObjectSelectionChecker(vector2 mousePos)
//{
//	std::string objNameException = "background";
//
//	const auto& objectContainer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::Stage)->GetObjContainer();
//	for (const auto& object : objectContainer)
//	{
//		if (objNameException != object->GetObjectName())
//		{
//			vector2 min{ object->GetTranslation() - (object->GetScale() / 2.f) };
//			vector2 max{ object->GetTranslation() + (object->GetScale() / 2.f) };
//
//			if (mousePos.x < min.x || mousePos.y < min.y ||
//				mousePos.x > max.x || mousePos.y > max.y)
//				continue;
//			else
//			{
//				Graphics::Color4f originalColor{};
//				Graphics::Color4f checkColor{ 0.5f };
//
//				originalColor = object->GetComponentByTemplate<Sprite>()->GetColor();
//
//				for (int i = 0; i < 3000; ++i)
//				{
//					if(i == 0)
//						object->GetComponentByTemplate<Sprite>()->SetColor(checkColor);
//				}
//
//				object->GetComponentByTemplate<Sprite>()->SetColor(originalColor);
//			}
//
//		} //if (object->GetObjectName != "background")
//	}
//} //end of function ObjectSelectionChecker