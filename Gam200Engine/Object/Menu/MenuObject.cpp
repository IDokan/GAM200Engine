/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MenuObject.hpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Declaration for Menu Object
    Menu Object is an abstract object that is designed to be drived by Menu Object
******************************************************************************/
#include <Object/Menu/MenuObject.hpp>

MenuObject::~MenuObject()
{

}

MenuObject::MenuObject()
    :Object()
{
    SetObjectType(ObjectType::Menu);
}
