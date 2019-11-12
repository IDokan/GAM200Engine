/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringPhysics.hpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 11.04.2019

    Header file for StringPhysics
******************************************************************************/

#pragma once
#include "Component/Physics.hpp"

class StringPhyscis : public Physics
{
public:
    virtual void Init() override;
    virtual void Update(float dt) override;
    virtual void Clear() override;

private:

};
