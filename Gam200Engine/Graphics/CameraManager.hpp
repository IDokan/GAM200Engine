/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   CameraManager.hpp
Author
	- Sinil.Kang rtd99062@gmail.com
Creation Date: 08.21.2019

	Header file for Camera Manager that Manage whole functions of camera things
******************************************************************************/
#pragma once

#include <Graphics/Camera.hpp>
#include <Graphics/CameraView.hpp>
#include <unordered_map>

namespace Graphics
{
	class CameraManager final
	{
	public:
		CameraManager();
		~CameraManager() = default;

		void Init() noexcept;

		// Functions to control camera storage
		void AddCamera(const std::string&) noexcept;
		bool SelectCamera(const std::string&) noexcept;

		void SetPosition(const vector2&) noexcept;
		vector2 GetPosition() const noexcept;

		void SetZoom(float) noexcept;
		float GetZoom() const noexcept;

		void SetViewSize(const vector2&) noexcept;
		void SetViewSize(int, int) noexcept;
		const vector2 GetViewSize() const noexcept;

		void SetFrameOfReference(CameraView::FrameOfReference) noexcept;
		constexpr CameraView::FrameOfReference GetFrameOfReference() const noexcept { return selectedCamera->cameraView.GetFrameOfReference(); };

		matrix3 GetWorldToNDCTransform() const noexcept;
		matrix3 GetCameraToWorldTransform() const noexcept;

		void MoveUp(float dt, float distance) noexcept;
		void MoveRight(float dt, float distance) noexcept;

		void CameraMove(const vector2& position1, const vector2& position2, const float& zoomSize) noexcept;

		vector2 GetDEBUGCameraRectSize() const noexcept;
	private:
		void DEBUGCameraMove(const float& zoomSize) noexcept;
		vector2 CalculateDeltaBetweenCameraAndPlayer(vector2 objDistance, vector2 playgroundSize) noexcept;
		
	private:
		struct CameraSet
		{
			Camera camera;
			CameraView cameraView;
		};

		CameraSet* selectedCamera = nullptr;
		std::unordered_map<std::string, std::shared_ptr<CameraSet>> cameraStorage;

		vector2 cameraDetectRectSize{ 500.f, 300.f };
	};
}

