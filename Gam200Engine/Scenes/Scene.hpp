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
#include <Sounds/SoundManager.hpp>
#include <Graphics/GL.hpp>

class SceneStateManager;
class String;
class Player;

enum class GameScenes 
{
    Menu, Game, Proto, Test, Credit, None
};

class Scene abstract
{
public:
	Scene()
		:current_scene_info(GameScenes::None), next_level({}), is_next(false), cameraManager({}), soundManager({}), sceneStateManager(nullptr), player1(nullptr), player2(nullptr), string(nullptr)
	{}
	virtual ~Scene() = default;
	void GameRestartScene() noexcept;
	virtual void Update(float dt) = 0;
	void LoadScene() noexcept;
	void UnloadScene() noexcept;

	virtual void Draw() noexcept;

	// Getters
	const Graphics::CameraManager& GetCameraManager() const noexcept;
	SoundManager& GetSoundManager() noexcept;

public:
	void LevelChangeTo(std::string name);
	std::string GetChangedLevelName();
	bool isNextLevel();
	GameScenes GetSceneInfo();

	//Thread work for loading
	void InitLoadingScene();


protected:
	virtual void GameRestart() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	void SetPlayerSpawnPosition(vector2 player1Position, vector2 player2Position);
    GameScenes current_scene_info;
    std::string next_level;
    bool is_next;


	Graphics::CameraManager cameraManager{};
	SoundManager soundManager{};
	SceneStateManager* sceneStateManager;

	vector2 player1SpawnPosition{};
	vector2 player2SpawnPosition{};

	Player* player1{};
	Player* player2{};

	String* string{};

private:
	std::vector<matrix3> obstacleMatrices;
	void DrawObject(Object* obj, matrix3 offset = MATRIX3::build_identity()) noexcept;
private:
	void InitDEBUGObjects();
	void InitRequiredObjects();
	void CleanRequiredObjects();

	//Loading...
	Object* loadingScene{};
	Object* loadingText{};
	Object* loadingAnimation{};
	bool isLoadingDone = false;
};