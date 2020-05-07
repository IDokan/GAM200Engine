/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneManager.cpp
Author
        dbsqhd106@gmail.com
Creation Date: 08.12.2019

    Source file for the Application.cpp
******************************************************************************/
#include <iostream>
#include <algorithm>
#include <Scenes/SceneManager.hpp>

#include  <Systems/Input.hpp>

SceneManager * SceneManager::GetSceneManager()
{
    static SceneManager* Scene_manager = new SceneManager();
    return Scene_manager;
}

void SceneManager::GameRestart() const
{
    currentScene->GameRestartScene();
}

void SceneManager::Init()
{
    currentScene = nullptr;
    scenes.clear();
}

void SceneManager::Update(float dt)
{
    if (input.IsKeyTriggered(GLFW_KEY_R))
    {
        GameRestart();
    }

    if (!is_restart) 
    {
        currentScene->Update(dt);
        if (currentScene->isNextLevel()) {
	        const std::string tmpName = currentScene->GetChangedLevelName();
            currentScene->UnloadScene();
            if (const auto & Scene = scenes.find(tmpName);
				Scene != scenes.end())
            {
				currentScene = Scene->second.get();
            }
            else
            {
				// Print DEBUG data
				std::cout << "Change level failed!\n";
            }
            currentScene->LoadScene();
        }
    }
    else
    {
        //std::cout << "Resume!\n";
    }

}

void SceneManager::Clear()
{
	currentScene->UnloadScene();
    currentScene = nullptr;

    scenes.clear();
}

void SceneManager::AddScenes(std::string name, Scene * Scene)
{
    auto tmp = std::make_pair(name, Scene);
    if (currentScene == nullptr) {
        // Why does it be right logic? I should double check
    	// if (Scene->GetSceneInfo() == GameScenes::Menu ) 
		{
            currentScene = Scene;
            currentScene->LoadScene();
        }
    }
    scenes.insert(tmp);
}

// Helper function to get a Draw from each Scene
void SceneManager::Draw() const noexcept
{
	currentScene->Draw();
}

void SceneManager::SetNextScene(std::string sceneName) noexcept
{
	currentScene->LevelChangeTo(sceneName);
}

std::vector<std::string> SceneManager::GetSceneNames() const noexcept
{
	std::vector<std::string> SceneNames;
	std::for_each(std::begin(scenes), std::end(scenes), [&](const std::pair< std::string, std::shared_ptr<Scene>>& SceneUnit)
		{
			SceneNames.push_back(SceneUnit.first);
		}
	);

	return SceneNames;
}

Scene* SceneManager::GetCurrentScene() const noexcept
{
	return currentScene;
}
