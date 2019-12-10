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
#include <Object/InteractiveObject/InteractiveObject.hpp>

#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>

namespace MyImGui
{
	bool isCollisionBoxShown = false;
	int stack = 0;

	static Object* collisionBox;
	void AddCollisionBox(Object* obj, Physics* physics)
	{
		//if (isCollisionBoxShown == true)
		//{
		//	return;
		//}

		Layer* hudLayer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD);
		if (hudLayer != nullptr)
		{
			// Toggle Show var
			isCollisionBoxShown = true;

			// Make Collision Box Object and Add to Object Manager
			collisionBox = new Object();
			collisionBox->AddComponent(new Sprite(collisionBox));
			collisionBox->SetObjectName(obj->GetObjectName() + " CollisionBox");
			const Physics::CollisionBox positionOfCollisionBox = physics->GetCollisionBox();
			collisionBox->SetTranslation(positionOfCollisionBox.Translation);
			collisionBox->SetScale(positionOfCollisionBox.Scale);
			collisionBox->SetDepth(-1.f);

			// If type of collision type is circle, make image as circle.
			if (physics->GetObjectType() == Physics::ObjectType::CIRCLE)
			{
				collisionBox->GetComponentByTemplate<Sprite>()->SetImage("../texture/circle.png");
			}

			hudLayer->AddObjectDynamically(collisionBox);
		}
	}

	void DeleteCollisionBox(Object* obj, Physics* physics)
	{
		if (isCollisionBoxShown == false)
		{
			return;
		}
		Layer* hudLayer = ObjectManager::GetObjectManager()->FindLayer(LayerNames::HUD);
		// Toggle Show Var
		isCollisionBoxShown = false;
		//hudLayer->DeleteObject(obj->GetObjectName() + " CollisionBox");
		collisionBox->SetDead(true);
	}

	void HelpMarker(const char* description)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(description);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	void SeparateSection(const char* description)
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text(description);
	}

	void DrawSpriteSection(Sprite* sprite)
	{
		SeparateSection("Sprite Section");
		Graphics::Color4f color = sprite->GetColor();
		ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&color), ImGuiColorEditFlags_AlphaPreview);
		sprite->SetColor(color);

		ImGui::Spacing();
		if (ImGui::Button("Button"))
		{
			sprite->SetImage("../texture/rect.png");
		}
		unsigned int* textureID = sprite->GetRefTextureHandle();
		ImGui::Text("%d", textureID);
		ImGui::Image((textureID), ImVec2(128, 128));
	}

	void DrawPhysicsSection(Object* object, Physics* physics)
	{
		SeparateSection("Physics Section");

		static vector2 velocity, gravity, vectorTranslation;
		velocity = physics->GetVelocity();
		gravity = physics->GetGravity();
        vectorTranslation = physics->GetVectorTranslation();

		ImGui::InputFloat2("Velocity", velocity.elements);
		ImGui::InputFloat2("Gravity", gravity.elements);
		ImGui::InputFloat2("VectorTranslation", vectorTranslation.elements);
		ImGui::SameLine(); HelpMarker("Read Only");

		physics->SetVelocity(velocity);
		physics->SetGravity(gravity);
        physics->SetVectorTranslation(vectorTranslation);

		static bool isCollisionBoxDrawn = false;
		if (physics->GetHasCollisionBox())
		{
			ImGui::Checkbox("Draw Check Box", &isCollisionBoxDrawn);
			if (isCollisionBoxDrawn)
			{
				AddCollisionBox(object, physics);
			}
			else
			{
				DeleteCollisionBox(object, physics);
			}
		}
	}

	void DrawInteractiveObjectSection(InteractiveObject* obj)
	{
		if (obj == nullptr)
		{
			return;
		}

		SeparateSection("InteractiveObject");
		static int numOfAttached;
		static int numOfDetached;

		numOfAttached = obj->GetAttachedNum();
		numOfDetached = obj->GetDetachedNum();

		ImGui::Text("%s", std::string("Num of Attached : " + std::to_string(numOfAttached)).c_str());
		ImGui::Text("%s", std::string("Num of Detached : " + std::to_string(numOfDetached)).c_str());
	}

	void DrawTransformSection(Object* obj)
	{
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
		ImGui::DragFloat("Rotation", &rotation, 0.005f);

		obj->SetTranslation(translation);
		obj->SetScale(scale);
		obj->SetRotation(rotation);

		if(ImGui::Button("Delete it"))
		{
			obj->SetDead(true);
		}
	}

	void InitImGui(GLFWwindow* window) noexcept
	{
#ifdef _DEBUG
		ImGui::CreateContext();
		// Set Multi-Viewports Enable.
		ImGuiIO& io = ImGui::GetIO();

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
#endif
	}

	// Merge at one or make it separate kind of Begin, Update, End...
	void UpdateImGui(bool isShowWindow, float dt) noexcept
	{
#ifdef _DEBUG
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		//if (isShowWindow)
		//	ImGui::ShowDemoWindow(&isShowWindow);
		
		// 2. Let's make my own window with ImGui Tutorial!
		ImGui::Begin("Scene");
		static int selectedLayer = -1;
		static int selected = -1;
		auto& layerContainer = ObjectManager::GetObjectManager()->GetLayerContainer();
		for (int i = 0; i < layerContainer.size(); ++i)
		{
			const auto objContainer = layerContainer.at(i)->GetObjContainer();
			const int size = objContainer.size();
			for (int j = 0; j < size; ++j)
			{
				if (ImGui::Selectable(objContainer.at(j)->GetObjectName().c_str(), selected == j && selectedLayer == i))
				{
					selectedLayer = i;
					selected = j;
				}
			}
		}
		ImGui::End();

		ImGui::Begin("Property");
		if (selectedLayer >= 0 && selectedLayer <= int(layerContainer.size()))
		{
			const auto& objContainer = layerContainer.at(selectedLayer)->GetObjContainer();
			const int objContainerSize = objContainer.size();
			if (selected >= 0 && selected < objContainerSize)
			{
				Object* obj = objContainer.at(selected).get();
				ImGui::Text("Object name is \"");	ImGui::SameLine();
				ImGui::Text(obj->GetObjectName().c_str()); ImGui::SameLine();
				ImGui::Text("\"");
				ImGui::Spacing();

				DrawTransformSection(obj);

				// If object have components display them.
				if (Sprite * sprite = obj->GetComponentByTemplate<Sprite>())
				{
					DrawSpriteSection(sprite);
				}
				if (Physics * physics = obj->GetComponentByTemplate<Physics>())
				{
					DrawPhysicsSection(obj, physics);
				}
				DrawInteractiveObjectSection(dynamic_cast<InteractiveObject*>(obj));
			}
			else
			{
				ImGui::Text("Select object in Scene window!");
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
#endif
	}

	void ClearImGui() noexcept
	{
#ifdef _DEBUG
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
#endif
	}
}
