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
#include "MyImGui.hpp"
#include <Graphics/ImGui/imgui.h>
#include <Graphics/ImGui/imgui_impl_opengl3.h>
#include <Graphics/ImGui/imgui_impl_glfw.h>
#include <Application.hpp>
#include <Object/ObjectManager.hpp>
#include <Component/Sprite.hpp>

namespace MyImGui
{
	
	void InitImGui(GLFWwindow* window) noexcept
	{
		ImGui::CreateContext();
		// Set Multi-Viewports Enable.
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	// Merge at one or make it separate kind of Begin, Update, End...
	void UpdateImGui(bool isShowWindow) noexcept
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (isShowWindow)
			ImGui::ShowDemoWindow(&isShowWindow);

		// 2. Let's make my own window with ImGui Tutorial!
		ImGui::Begin("Scene");
		static int selected = -1;
		auto& objContainer = ObjectManager::GetObjectManager()->GetObjectManagerContainer();
		for(int i = 0; i < objContainer.size(); ++i)
		{
			if(ImGui::Selectable(objContainer.at(i)->GetObjectName().c_str(), selected == i))
			{
				selected = i;
			}
		}
		ImGui::End();

		ImGui::Begin("Property");
		if (selected >= 0 && selected < objContainer.size())
		{
			Object* obj = objContainer.at(selected).get();
			ImGui::Text(obj->GetObjectName().c_str());
			ImGui::Spacing();

			ImGui::Text("Transform");
			static vector2 translation{}, scale{};
			static float rotation;
			translation = obj->GetTranslation();
			rotation = obj->GetRotation();
			scale = obj->GetScale();

			ImGui::DragFloat("Translation X", &translation.x);
			ImGui::DragFloat("Translation Y", &translation.y);
			ImGui::DragFloat("Scale X", &scale.x);
			ImGui::DragFloat("Scale Y", &scale.y);
			ImGui::DragFloat("Rotation", &rotation);

			obj->SetTranslation(translation);
			obj->SetScale(scale);
			obj->SetRotation(rotation);

			// TODO: Make Object Controller followed Component
			if (Sprite* sprite = obj->GetComponentByTemplate<Sprite>())
			{
				ImGui::Separator();
				Graphics::Color4f color = sprite->GetColor();
				//ImGui::ColorEdit4("Color", )
			}
		}
		else
		{
			ImGui::Text("Select object in Scene window!");
		}
		ImGui::End();


		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO();
		// Update and Render additional Platform Windows
		// (Platform functions may change the currentOpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ClearImGui() noexcept
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}
