/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   StringPiece.cpp
Author

Creation Date:

	Source file for the String Piece Object
******************************************************************************/
#include <Object/Strings/StringPiece.hpp>
#include <Component/StringSprite.hpp>
#include <Component/StringPhysics.hpp>

StringPiece::StringPiece()
{
	AddComponent(new StringSprite(this));
	//AddComponent(new StringPhyscis(this));			// TODO: Remove comment mark when physics are implemented
}
