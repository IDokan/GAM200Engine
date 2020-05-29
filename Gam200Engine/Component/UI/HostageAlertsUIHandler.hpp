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

#include <Vector2.hpp>
class HostageAlertsUI;

class HostageAlertsUIHandler : public Component
{
public:
	const vector2 hidePosition{ -1.3f, -1.55f };
	const vector2 showPosition{ -0.78f, -0.6f };
public:
	HostageAlertsUIHandler(HostageAlertsUI* owner);
	~HostageAlertsUIHandler();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

private:
	vector2 EaseOutElastic(float t);
	vector2 EaseInQuad(float t);

	void UpdateTimer(float dt);
private:
	HostageAlertsUI* ui;
	bool shouldShowing;

	float timer;
	bool isSoundPlay;
};