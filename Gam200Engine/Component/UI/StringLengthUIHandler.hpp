/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringLengthUIHandler.hpp
Author
		sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

	Header file for a component that manage StringLength UI
******************************************************************************/
#include <Component/Component.hpp>

class StringLengthUI;

class StringLengthUIHandler : public Component
{
public:
	StringLengthUIHandler(StringLengthUI* owner);
	~StringLengthUIHandler();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Clear();

private:
	StringLengthUI* ui;
	bool shouldShowing;
};