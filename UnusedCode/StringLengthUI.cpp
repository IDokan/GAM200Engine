/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringLengthUI.cpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 03.30.2020

    Header file for an interface object of BodyOfStringLengthUI
        When string start to stretch, this showed up
******************************************************************************/
#include <Object/HUD/StringLengthUI.hpp>
#include <Object/HUD/BodyOfStringLengthUI.hpp>
#include <Object/ObjectManager.hpp>
#include <iostream>

StringLengthUI::StringLengthUI()
{
    body = new BodyOfStringLengthUI();
    body->SetObjectName("Body Of String UI");
    ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD)->AddObject(body);
}

StringLengthUI::~StringLengthUI()
{
    std::cout << "Dtor of StringLengthUI is called\n";
}
