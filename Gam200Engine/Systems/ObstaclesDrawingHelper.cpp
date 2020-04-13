/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ObstaclesDrawingHelper.cpp
Author
		rtd99062@gmail.com
Creation Date: 03.10.2020

	Source file for obstacles drawing helper
******************************************************************************/
#include <Systems/ObstaclesDrawingHelper.hpp>

#include <Object/Object.hpp>
#include <Component/Sprite/Sprite.hpp>
#include <Graphics/GL.hpp>

ObstaclesDrawingHelper* ObstaclesDrawingHelper::Get()
{
	static ObstaclesDrawingHelper* helper = new ObstaclesDrawingHelper();
	return helper;
}

void ObstaclesDrawingHelper::Init() noexcept
{
	if (obstacles == nullptr)
	{
		obstacles = new Object();
	}
	if (obstaclesSprite == nullptr)
	{
		obstaclesSprite = new Sprite(obstacles);
	}

	obstacles->SetDepth(-0.5f);
	obstaclesSprite->Init();
	obstaclesSprite->SetInstancingMode(Sprite::InstanceModes::ADVANCED);
	obstaclesSprite->SetImage("../assets/textures/BLOCK_W.png");
}

void ObstaclesDrawingHelper::Draw(std::vector<vector2>* obstaclesTextureCoordinates, std::vector<Graphics::Color4ub>* obstacleColors, std::vector<matrix3>* obstaclesMatrix) noexcept
{
	obstaclesSprite->UpdateInstancingValues(obstaclesTextureCoordinates, obstacleColors, obstaclesMatrix, obstacles->GetTransform().CalculateWorldDepth());
	Graphics::GL::drawInstanced(*obstaclesSprite->GetVertices(), *obstaclesSprite->GetMaterial());
}

ObstaclesDrawingHelper::~ObstaclesDrawingHelper()
{
	if (obstacles != nullptr)
	{
		delete obstacles;
	}
	if (obstaclesSprite != nullptr)
	{
		delete obstaclesSprite;
	}
}
