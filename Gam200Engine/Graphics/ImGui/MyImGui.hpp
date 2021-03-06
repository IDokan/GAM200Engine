/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MyImGui.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.23.2019

	Header file for My ImGui Code
******************************************************************************/
#pragma once
#pragma warning(push)
#pragma warning(disable:26451)
#pragma warning(disable:26495)
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Graphics/ImGui/imgui.h>
#pragma warning (pop)

namespace MyImGui
{
	void InitImGui(GLFWwindow* window) noexcept;
	void UpdateImGui(bool isShowWindow, float dt) noexcept;
	void ClearImGui() noexcept;
};
