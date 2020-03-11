/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ObstaclesDrawingHelper.hpp
Author
		rtd99062@gmail.com
Creation Date: 03.10.2020

	Header file for obstacles drawing helper
******************************************************************************/
#include <vector>
#include <matrix3.hpp>

class Object;
class Sprite;

class ObstaclesDrawingHelper
{
public:
	static ObstaclesDrawingHelper* Get();
	void Init() noexcept;
	void Draw(std::vector<matrix3>* obstaclesMatrix) noexcept;
	~ObstaclesDrawingHelper();
private:
	ObstaclesDrawingHelper() : obstacles(nullptr), obstaclesSprite(nullptr) {}
	Object* obstacles;
	Sprite* obstaclesSprite;
};