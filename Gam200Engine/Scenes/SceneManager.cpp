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
#include <Object/SceneStateManager/SceneStateManager.hpp>
#include  <Systems/Input.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Object/ObjectManager.hpp>
#include <Object/DepthStandard.hpp>

namespace Lerp
{
    float EaseOutCubic(float t)
    {
        float reverseT = 1 - t;
        return 1 - (reverseT * reverseT * reverseT);
    }
    float EaseOutQuart(float t)
    {
        float reverseT = 1 - t;
        return 1 - (reverseT * reverseT * reverseT * reverseT);
    }
}

SceneManager* SceneManager::GetSceneManager()
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
    isTransitioning = false;
    isEnteringTransition = false;
    transitionTimer = 0.f;
    currentScene = nullptr;
    scenes.clear();
}

void SceneManager::Update(float dt)
{
    if (input.IsKeyTriggered(GLFW_KEY_R))
    {
        GameRestart();
    }
    if (input.IsKeyTriggered(GLFW_KEY_N))
    {
        SetNextScene(currentScene->GetSceneStateManager()->GetNameOfSelectedLevel());
    }

    if (!is_restart)
    {
        if (isEnteringTransition == true)
        {
            // Start to draw entering transition
            if (isTransitioning == false)
            {
                transitionTimer = 0.f;

                isTransitioning = true;
            }
            else
            {
                // Update entering transition
                transitionTimer += dt;

                transitionImage->SetTranslation(vector2{ 0.f, - (3.f * Lerp::EaseOutQuart(transitionTimer)) });

                // When entering transition is done.
                if (transitionTimer > 1.f)
                {
                    transitionImage = nullptr;
                    isEnteringTransition = false;
                    isTransitioning = false;
                    transitionTimer = 0.f;
                }
            }
        }

        // Call Scene Update
        currentScene->Update(dt);

        if (currentScene->isNextLevel()) 
        {
            // Start to drawing end transition
            if (isTransitioning == false)
            {
                transitionTimer = 0.f;

                transitionImage = CreateTransitionImage(true);

                isTransitioning = true;
            }
            else
            {
                // When end transition is done, Do real Loading
                if (transitionTimer > 1.f)
                {
                    const std::string tmpName = currentScene->GetChangedLevelName();

                    currentScene->UnloadScene();

                    if (const auto& Scene = scenes.find(tmpName);
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

                    isTransitioning = false;
                    isEnteringTransition = true;
                    transitionTimer = 0.f;

                    transitionImage = CreateTransitionImage(false);
                }
                // Update transition
                else
                {
                    transitionTimer += dt;
                    transitionImage->SetTranslation(vector2{ 0.f, 3.f - (3.f * Lerp::EaseOutCubic(transitionTimer)) });
                }
            }
        }
    }
    else
    {
        //std::cout << "Resume!\n";
    }

}

void SceneManager::Clear()
{
    isTransitioning = false;
    isEnteringTransition = false;
    transitionTimer = 0.f;

    currentScene->UnloadScene();
    currentScene = nullptr;

    scenes.clear();
}

void SceneManager::AddScenes(std::string name, Scene* Scene)
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

Scene* SceneManager::GetCurrentScene() noexcept
{
    return currentScene;
}

Object* SceneManager::CreateTransitionImage(bool isEntering)
{
    Object* newObject;
    newObject = new Object();
    if (isEntering)
    {
        newObject->SetTranslation(vector2{ 0.f, 1000.f });
    }
    else
    {
        newObject->SetTranslation(vector2{ 0.f });
    }
    newObject->SetScale(vector2{2.f, 4.f});
    newObject->SetObjectName("Transition Name");
    newObject->SetDepth(Depth_Standard::TransitionHUD);
    Sprite* image = new Sprite(newObject);
    newObject->AddComponent(image);
    image->SetImage("../assets/textures/UI/TransitionCheese.png");
    ObjectManager::GetObjectManager()->FindLayer(HUD)->AddObjectDynamically(newObject);

    return newObject;
}
