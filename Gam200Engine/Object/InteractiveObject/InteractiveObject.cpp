/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   InteractiveObject.cpp
Author
		rtd99062@gmail.com
Creation Date: 12.09.2019

	Source file for the object that interact with string
******************************************************************************/

#include <Object/InteractiveObject/InteractiveObject.hpp>

InteractiveObject::InteractiveObject()
	:Object(), attachedNum(0), detachedNum(0)
{
}

InteractiveObject::~InteractiveObject()
{
}

void InteractiveObject::Attached() noexcept
{
	++attachedNum;
	DoSomethingWhenAttached();
}

void InteractiveObject::Detached() noexcept
{
	++detachedNum;
	DoSomethingWhenDetached();
}

int InteractiveObject::GetAttachedNum() const noexcept
{
	return attachedNum;
}

int InteractiveObject::GetDetachedNum() const noexcept
{
	return detachedNum;
}
