/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   SceneComplete.hpp
Author
		Kang rtd99062@gmail.com
Creation Date: 03.16.2020

	Header file for SceneComplete State
		if both players reached goal, both player start dancing to celebrate their achievements.
																			--------- -> This is my hope
******************************************************************************/
#pragma once

#include <States/State.hpp>
#include <Object/SceneStateManager/SceneStateManager.hpp>

class Object;
class ParticleEmitter;

class SceneComplete : public State<SceneStateManager>
{
public:
	enum SelectionEnum
	{
		Back2Main,
		Go2NextLevel,
		OutOfEnum,
	};
public:
	static SceneComplete* Get();

	void Enter(SceneStateManager* manager) override;
	void Execute(SceneStateManager* manager, float dt) override;
	void Exit(SceneStateManager* manager) override;


	void PrepareAssets() noexcept;
	void CleanAssets() noexcept;

private:
	SceneComplete();
	void SetCurrentSelection(SelectionEnum newValue);
	void UpdateSelection() noexcept;
	Object* GetSelectedObject();
	void UpdateSelectionHighlightTransformation();
	void UpdateSelectionHighlightTransparency(float dt);

	Object* menuBackground;
	Object* backToMain;
	Object* goToNextLevel;
	ParticleEmitter* confetti;
	Object* selectionHighlight;
	SelectionEnum currentSelection;

	bool isTransparency;
};

