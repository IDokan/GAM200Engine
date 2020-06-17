/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   HostageAlertsUIHandler.hpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 05.05.2020

	Header file for a component that manage HostageAlerts UI
******************************************************************************/
#include <Component/Component.hpp>

class StatusUI;

class StatusUIHandler : public Component
{
public:
public:
	StatusUIHandler(StatusUI* owner);
	~StatusUIHandler();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

private:
	StatusUI* ui;
};