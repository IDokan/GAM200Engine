/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   TestInteractionObject.hpp
Author
		rtd99062@gmail.com
Creation Date: 12.09.2019

	Header file for the test object whether interact work or not
******************************************************************************/
#pragma once

#include <Object/InteractiveObject/InteractiveObject.hpp>
class TestInteractionObject : public InteractiveObject
{
public:
	TestInteractionObject();
	virtual ~TestInteractionObject();

	void DoSomethingWhenAttached() override;
	void DoSomethingWhenDetached() override;
};