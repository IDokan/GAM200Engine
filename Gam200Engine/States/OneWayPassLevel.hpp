/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OneWayPassLevel.hpp
Author
	- Sinil.Kang rtd99062@gmail.com

Creation Date: 12.10.2019

	Header file for level that string make player move easily
******************************************************************************/
#pragma once
#include <States/State.hpp>

class OneWayPassLevel : public State
{
public:
	OneWayPassLevel();
	virtual ~OneWayPassLevel();

	void Load() override;
	void Update(float dt) override;
	void Unload() override;
	
private:
};