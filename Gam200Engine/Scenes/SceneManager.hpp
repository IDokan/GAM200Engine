/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneManager.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 08.12.2019

    Header file for the Scene Manager
******************************************************************************/

#pragma once

#include <Scenes/Scene.hpp>
#include <unordered_map>
#include <memory>

class SceneManager
{
public:
    static SceneManager *GetSceneManager();
    void GameRestart() const;
    void Init();
    void Update(float dt);
    void Clear();
    void AddScenes(std::string name, Scene *scene);

	void Draw() const noexcept;

	// Setters
	void SetNextScene(std::string sceneName) noexcept;

	// Getters
	std::vector<std::string> GetSceneNames() const noexcept;
	Scene* GetCurrentScene() noexcept;
	
    bool is_restart = false;
     
private:
    SceneManager(){};
    std::unordered_map < std::string, std::shared_ptr<Scene> > scenes;
    Scene *currentScene = nullptr;
};