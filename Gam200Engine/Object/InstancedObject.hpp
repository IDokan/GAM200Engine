/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   InstancedObject.hpp
Author
		sinil.gang
		rtd99062@gmail.com
Creation Date: 02.11.2020

	Header file for the InstancedObject
******************************************************************************/

#include <Object/Object.hpp>

class InstancedObject : Object
{
public:
	InstancedObject();
	~InstancedObject();

	/*
	 * TODO: Envision functions to manifest a bunch of transforms at one function call
	 */
	
private:
	std::vector<Transform> instancedTransforms;
	float sharedDepth;
};