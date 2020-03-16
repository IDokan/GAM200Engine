/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuScene.cpp
Author
	- jiwon.jung jjwon6218@gmail.com
Creation Date: 03.13.2020

	Source file for scene which works as menu
******************************************************************************/
#include <Scenes/MenuScene.hpp>
#include <Component/Scripts/GoalComponent.hpp>
#include <Component/Physics.hpp>
#include <Object/Object.hpp>
#include <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Systems/FileIO.hpp>
#include <Sounds/SoundManager.hpp>
#include <Component/StateMachine.hpp>
#include <States/Walking.hpp>

MenuScene::MenuScene() : background(nullptr)
{

}

MenuScene::~MenuScene()
{

}

void MenuScene::Load()
{
	fileIO* fileio = new fileIO;
	fileio->Input("../assets/fileIO/menuSettings.txt", &player1, &player2, &string);

	MenuScene::InitObject();
	cameraManager.Init();
}

void MenuScene::Update(float /*dt*/)
{
}

void MenuScene::GameRestart()
{
}

void MenuScene::Unload()
{
}

void MenuScene::Input()
{
}

void MenuScene::Collision()
{
}

void MenuScene::InitObject()
{
}



