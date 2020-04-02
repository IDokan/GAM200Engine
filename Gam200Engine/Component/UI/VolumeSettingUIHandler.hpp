/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   VolumeSettingUIHandler.hpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

	Header file for a component that manage VolumeSetting UI
******************************************************************************/
#include <Component/Component.hpp>

class VolumeSettingBar;

class VolumeSettingUIHandler : public Component
{
public:
	VolumeSettingUIHandler(VolumeSettingBar* owner);
	~VolumeSettingUIHandler();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

private:
	VolumeSettingBar* ui;
};