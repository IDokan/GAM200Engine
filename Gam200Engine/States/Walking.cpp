/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Walking.cpp
Author
		Kang rtd99062@gmail.com
Creation Date: 01.14.2020

	Source file for walking state to test FSM works correctly.
******************************************************************************/

#include <States/Walking.hpp>

Walking::~Walking()
{
}

void Walking::Enter(Object* /*obj*/)
{
	std::cout << "Enter an Walking state!\n";
}

void Walking::Execute(Object* obj)
{
	obj->SetTranslation(obj->GetTranslation() + vector2{ -2.f, 0.f });
}

void Walking::Exit(Object* /*obj*/)
{
	std::cout << "Exit an Walking state!\n";
}