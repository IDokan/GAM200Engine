/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   EventManager.hpp
Author
	- sinil.gang rtd99062@gmail.com
Creation Date: 03.15.2020

	Source file for Scene State Manager
		This manager manages state of scene.
		Scene State consist of three different state.
			1. PlayerIsDead
				When Any player is dead, show 'press R to restart' and change players state with Message System.
			2. SceneComplete
				if both players reached goal, both player start dancing to celebrate their achievements.
			3. GameIsRunning
				Nothing to do in here.
******************************************************************************/
#pragma once

class SceneStateManager
{
public:
	enum class SceneState
	{
		GameIsRunning,
		PlayerIsDead,
		SceneComplete,
		NumOfSceneStates,
	};

	SceneStateManager();
	SceneState GetCurrentSceneState() const noexcept;
	void ChangeCurrentSceneState(SceneState newSceneState) noexcept;

	// This function must be called in Application::Update(float dt)
		// -> However, specific location is will be determined. (Before message dispatching, After ??? )
	// It does different behavior depends on current SceneState
	void Update(float dt);

private:
	SceneState currentSceneState;
};