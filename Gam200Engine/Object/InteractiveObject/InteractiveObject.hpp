/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   InteractiveObject.hpp
Author
		rtd99062@gmail.com
Creation Date: 12.09.2019

	Header file for the object that interact with string
******************************************************************************/
#pragma once
#include <Object/Object.hpp>

class InteractiveObject abstract : public Object
{
public:
	InteractiveObject();
	virtual ~InteractiveObject();

	void Attached() noexcept;
	void Detached() noexcept;
	
	virtual void DoSomethingWhenAttached() = 0;
	virtual void DoSomethingWhenDetached() = 0;

	int GetAttachedNum() const noexcept;
	int GetDetachedNum() const noexcept;
protected:
	int attachedNum;
	int detachedNum;
};