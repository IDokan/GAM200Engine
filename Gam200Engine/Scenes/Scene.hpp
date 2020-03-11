/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Scene.hpp
Author
		rtd99062@gmail.com
Creation Date: 08.12.2019

	Header file for the abstract class for all of Scene
******************************************************************************/

#pragma once
#include <string>
#include <Graphics/CameraManager.hpp>

enum class GameScenes 
{
    Menu, Game, Proto, Test, Credit, None
};

class Scene abstract
{
public:
	Scene()
		:current_scene_info(GameScenes::None), next_level({}), is_next(false), cameraManager({})
	{}
	virtual ~Scene() = default;
    void GameRestartScene() noexcept;
    virtual void Update(float dt) = 0;
	void LoadScene() noexcept;
	void UnloadScene() noexcept;

	virtual void Draw() const noexcept;

	// Getters
	const Graphics::CameraManager& GetCameraManager() const noexcept;

public:
	void LevelChangeTo(std::string name);
	std::string GetChangedLevelName();
	bool isNextLevel();
	GameScenes GetSceneInfo();

protected:
    virtual void GameRestart() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
    GameScenes current_scene_info;
    std::string next_level;
    bool is_next;


	Graphics::CameraManager cameraManager{};

private:
	void InstanceDEBUGObjects();
};