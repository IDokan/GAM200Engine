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

#include <array>

#pragma warning(push)
#pragma warning(disable:26451)
#pragma warning(disable:26495)
#include "MyImGui.hpp"
#include <Graphics/ImGui/imgui.h>
#include <Graphics/ImGui/imgui_impl_opengl3.h>
#include <Graphics/ImGui/imgui_impl_glfw.h>
#pragma warning (pop)
#include <Window/Application.hpp>
#include <Object/ObjectManager.hpp>
#include <Object/InteractiveObject/InteractiveObject.hpp>
// Include special objects
#include <Object/DEBUGObject/WallSpawner.hpp>
#include <Object/DEBUGObject/LevelChangeButton.hpp>
// Include Components
#include <Component/Sprite.hpp>
#include <Component/Physics.hpp>

namespace MyImGui
{
	/* Helper functions */
	void HelpMarker(const char* description);
	void MakeBigSpacing();
	void SeparateSection(const char* description);
	void DrawSpriteSection(Sprite* sprite);
	void DrawPhysicsSection(Object* object, Physics* physics);
	void DrawInteractiveObjectSection(InteractiveObject* obj);
	void DrawStringSection(String* string);
	void DrawObjectNameSection(Object* obj);
	void DrawInformation(Object* obj);
	void DrawTransformSection(Object* obj);
	void HighlightSelectedObject(Object* obj, float dt);
	void DrawLevelChangeSection(LevelChangeButton* levelChangeButton);
	void DrawWallSpawnerSection(WallSpawner* wallSpawner);
	/* End of helper functions */


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

	void MakeBigSpacing()
	{
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
	}

	void SeparateSection(const char* description)
	{
		MakeBigSpacing();
		ImGui::Text("%s", description);
	}

	void DrawSpriteSection(Sprite* sprite)
	{

		SeparateSection("Sprite Section");
		Graphics::Color4f color = sprite->GetColor();
		ImGui::ColorEdit4("Color", reinterpret_cast<float*>(&color), ImGuiColorEditFlags_AlphaPreview);
		sprite->SetColor(color);

		ImGui::Spacing();

        static int resultPrintFlag = 0;

		static constexpr size_t BUFFER_SIZE = 128;
		static char* filePath{};
		filePath = const_cast<char*>(sprite->GetImagePath().c_str());
		ImGui::InputText("file path", filePath, BUFFER_SIZE);
		if (ImGui::Button("Change sprite!"))
		{
            if (sprite->SetImage(filePath))
            {
                resultPrintFlag = 1;
            }
            else
            {
                resultPrintFlag = -1;
            }
		}

        if (resultPrintFlag > 0)
        {
            ImGui::SameLine();
            ImGui::Text("Image Loading succeed! :D");
        }
        else if (resultPrintFlag < 0)
        {
            ImGui::SameLine();
            ImGui::Text("Image Loading Failed.. :(");
        }
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

		physics->SetCollisionBoxPosition(object->GetTranslation());
		physics->SetCollisionBoxScale(object->GetScale());
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

	void DrawStringSection(String* string)
	{
		SeparateSection("String Section");

		// Length of string
		ImGui::Text("%s", std::string("Entire string length is " + std::to_string(string->GetStringLength())).c_str());

		// Num of vertices
		const auto& vertices = string->GetVertices();
		ImGui::Text("%s", std::string("There is " + std::to_string(vertices.size()) + " vertices").c_str());

		for (size_t i = 0; i < vertices.size(); ++i)
		{
			MakeBigSpacing();

			// Specify what the number of current vertex is
			const StringVertex& vertex = vertices.at(i);
			ImGui::Text("%s", std::string("Vertex " + std::to_string(i)).c_str());

			// Position of vertex
			ImGui::Text("%s", std::string("Position : " + std::to_string(vertex.position.x) + ' ' + std::to_string(vertex.position.y)).c_str());

			// The center position of attached object
			ImGui::Text("%s", std::string("The center Position of attached object: ").c_str());
			ImGui::Text("\t%s", std::string(std::to_string(vertex.centerPositionOfCollidedObject.x) + ' ' + std::to_string(vertex.centerPositionOfCollidedObject.y)).c_str());

			// Information of the attached object
			if (Object* obj = vertex.attachedObject;
				obj != nullptr)
			{
				ImGui::Text("%s", std::string("Attached Object name is ").c_str());
				ImGui::Text("\t%s", obj->GetObjectName().c_str());
				ImGui::Text("The type of attached object");
				ImGui::Text("\t%s", obj->GetStringOfObjectType().c_str());
			}
			else
			{
				ImGui::Text("Attached object is nullptr!");
			}
		}
	}

	void DrawTransformSection(Object* obj)
	{
		ImGui::Text("Transform");
		static vector2 translation{}, scale{};
		static float rotation;
		static float depth;
		translation = obj->GetTranslation();
		rotation = obj->GetRotation();
		scale = obj->GetScale();
		depth = obj->GetDepth();

		ImGui::DragFloat("Translation X", &translation.x);
		ImGui::DragFloat("Translation Y", &translation.y);
		ImGui::DragFloat("Scale X", &scale.x);
		ImGui::DragFloat("Scale Y", &scale.y);
		ImGui::DragFloat("Rotation", &rotation, 0.005f);
		ImGui::DragFloat("Depth", &depth);

		obj->SetTranslation(translation);
		obj->SetScale(scale);
		obj->SetRotation(rotation);
		obj->SetDepth(depth);

		if (ImGui::Button("Delete it"))
		{
			obj->SetDead(true);
		}
	}

	void DrawObjectNameSection(Object* obj)
	{
		ImGui::Text("Object name is \"");	ImGui::SameLine();
		ImGui::Text(obj->GetObjectName().c_str()); ImGui::SameLine();
		ImGui::Text("\"");
		ImGui::Spacing();
	}

	void DrawInformation(Object* obj, float dt)
	{
		// Draw Object Name first -> It is essential
		DrawObjectNameSection(obj);

		// Draw special object, after draw it return this function
		{
			// Draw level chang button description if given object is that
			if (LevelChangeButton * levelChangeButton = dynamic_cast<LevelChangeButton*>(obj);
				levelChangeButton != nullptr)
			{
				DrawLevelChangeSection(levelChangeButton);
				return;
			}

			// Draw string object description if given object is that
			if (String * string = dynamic_cast<String*>(obj);
				string != nullptr)
			{
				DrawStringSection(string);
				return;
			}
		}
		// Draw Transform section
		DrawTransformSection(obj);

		{
			// If object have special components display them.
			if (Sprite * sprite = obj->GetComponentByTemplate<Sprite>();
				sprite != nullptr)
			{
				HighlightSelectedObject(obj, dt);

				DrawSpriteSection(sprite);
			}
			if (Physics * physics = obj->GetComponentByTemplate<Physics>())
			{
				DrawPhysicsSection(obj, physics);
			}
		}

		// Draw Interactive Object
		DrawInteractiveObjectSection(dynamic_cast<InteractiveObject*>(obj));

		// Draw Wall Spawner object
		if (WallSpawner* wallSpawner = dynamic_cast<WallSpawner*>(obj);
			wallSpawner != nullptr)
		{
			DrawWallSpawnerSection(wallSpawner);
		}
	}

	void HighlightSelectedObject(Object* obj, float dt)
	{
		if (obj == nullptr || obj->GetComponentByTemplate<Sprite>() == nullptr)
		{
			return;
		}

		static Object* selectedObj = nullptr;
		static Graphics::Color4f originalColor{};
		static Graphics::Color4f startColor{ 0.f };
		static float localTimer{ 0.f };

		if (selectedObj != obj)
		{
			// recover data of selected data
			if (selectedObj != nullptr && localTimer < 1.f)
			{
				selectedObj->GetComponentByTemplate<Sprite>()->SetColor(originalColor);
			}

			// Initialize local timer
			localTimer = 0.f;

			// Save data of selected object
			selectedObj = obj;
			originalColor = obj->GetComponentByTemplate<Sprite>()->GetColor();
		}


		// Update color when only needed
		if (localTimer < 1.f)
		{
			localTimer += dt;

			obj->GetComponentByTemplate<Sprite>()->SetColor(startColor + (originalColor - startColor) * localTimer);
		}
	}

	void DrawLevelChangeSection(LevelChangeButton* levelChangeButton)
	{
		SeparateSection("Level Change Button");
		const std::vector<std::string> stateNames = levelChangeButton->GetStateNames();

		for (size_t i = 0; i < stateNames.size(); ++i)
		{
			if (ImGui::Button(stateNames.at(i).c_str()))
			{
				levelChangeButton->ChangeLevel(stateNames.at(i));
			}
		}
	}

	void DrawWallSpawnerSection(WallSpawner* wallSpawner)
	{
		SeparateSection("Wall Spawner");

		if (ImGui::Button("Spawn wall!"))
		{
			wallSpawner->SpawnWall();
		}
	}
#ifdef _DEBUG
	void InitImGui(GLFWwindow* window) noexcept
#else
    void InitImGui(GLFWwindow* /*window*/) noexcept
#endif
	{
#ifdef _DEBUG
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
#endif
	}

	// Merge at one or make it separate kind of Begin, Update, End...
#ifdef _DEBUG
	void UpdateImGui(bool /*isShowWindow*/, float dt) noexcept
#else
    void UpdateImGui(bool /*isShowWindow*/, float /*dt*/) noexcept
#endif
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
		static int selectedLayer = -1;
		static int selected = -1;
		auto& layerContainer = ObjectManager::GetObjectManager()->GetLayerContainer();
		std::vector<std::string> layerNames;
		for (size_t i = 0; i < layerContainer.size(); i++)
		{
			layerNames.push_back(layerContainer.at(i)->GetNameAsString());
		}
		for (size_t i = 0; i < layerNames.size(); ++i)
		{
			ImGui::Begin(layerNames.at(i).c_str());
			const auto objContainer = layerContainer.at(i)->GetObjContainer();
			const size_t size = objContainer.size();
			for (int j = 0; j < static_cast<int>(size); ++j)
			{
				if (ImGui::Selectable(objContainer.at(j)->GetObjectName().c_str(), selected == j && static_cast<size_t>(selectedLayer) == i))
				{
					selectedLayer = static_cast<int>(i);
					selected = j;
				}
			}
			ImGui::End();
		}

		ImGui::Begin("Property");
		if (selectedLayer >= 0 && selectedLayer <= int(layerContainer.size()))
		{
			const auto& objContainer = layerContainer.at(selectedLayer)->GetObjContainer();
			const size_t objContainerSize = objContainer.size();
			if (selected >= 0 && selected < static_cast<int>(objContainerSize))
			{
				Object* obj = objContainer.at(selected).get();

				// Draw all information about selected object in here!
				DrawInformation(obj, dt);
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

		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
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
