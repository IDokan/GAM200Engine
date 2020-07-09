/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CheckPoint.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 06.29.2020

	Header file for check point to save players progress
******************************************************************************/
#include <Object/Object.hpp>
#include <Graphics/Color4f.hpp>

class Player;

class CheckPoint : public Object
{
public:
	CheckPoint(const vector2& transform, Player* ptrToPlayer1, Player* ptrToPlayer2);
};