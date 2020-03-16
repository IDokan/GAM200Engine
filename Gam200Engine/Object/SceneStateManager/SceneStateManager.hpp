/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneStateManager.hpp
Author
	- sinil.gang		rtd99062@gmail.com
Creation Date: 03.16.2020

		Header file for Scene State Manager
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
#include <Object/Object.hpp>

class SceneStateManager : public Object
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

private:
};