/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   GoalComponent.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 12.13.2019

	Header file for goal component that will be attached at goal object
******************************************************************************/
#pragma once
#include <string>
#include <Component/Component.hpp>

class GoalComponent : public Component
{
public:
	GoalComponent(Object* obj, const std::string& targetStage_);
	virtual ~GoalComponent();
	
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Clear() override;

private:
	std::string targetStage;
	Object* targetObject;
};