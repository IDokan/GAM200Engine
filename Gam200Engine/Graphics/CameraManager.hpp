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

class Object;
class Player;

namespace Graphics
{
	class CameraManager final
	{
	private:
		typedef int EyesightTypeCode;
		#define	UP 1 << 0
		#define	RIGHT 1 << 1
		#define	DOWN 1 << 2
		#define	LEFT 1 << 3

	public:
		CameraManager();
		~CameraManager() = default;

		void Init(Player* player1 = nullptr, Player* player2 = nullptr) noexcept;

		void InitializeCurrentCameraSetting(Player* player1 = nullptr, Player* player2 = nullptr) noexcept;
		
		// Functions to control camera storage
		void AddCamera(const std::string&) noexcept;
		bool SelectCamera(const std::string&) noexcept;

		void SetPosition(const vector2&) noexcept;
		vector2 GetPosition() const noexcept;

		void SetZoom(float) noexcept;
		float GetZoom() const noexcept;
		constexpr float GetInitZoomSize() const noexcept;

		void SetViewSize(const vector2&) noexcept;
		void SetViewSize(int, int) noexcept;
		const vector2 GetViewSize() const noexcept;

		void SetFrameOfReference(CameraView::FrameOfReference) noexcept;
		constexpr CameraView::FrameOfReference GetFrameOfReference() const noexcept { return selectedCamera->cameraView.GetFrameOfReference(); };

		matrix3 GetWorldToNDCTransform() const noexcept;
		matrix3 GetCameraToWorldTransform() const noexcept;
		matrix3 GetCameraToNDCTransform() const noexcept;

		void MoveUp(float dt, float distance) noexcept;
		void MoveRight(float dt, float distance) noexcept;

		void CameraMove(float dt, const Object* player1, const Object* player2, const float& zoomSize) noexcept;
		
		void EditorCameraMoveUp(float distance) noexcept;
		void EditorCameraMoveLeft(float distance) noexcept;

		vector2 GetDEBUGCameraRectSize() const noexcept;

		void StartShakingCamera(float time, float magnitude);

		void StartZoomFromOutside(bool isStart, float t);
		void ZoomInLerpFromOutsize();
	private:
		void DEBUGCameraMove(const float& zoomSize) noexcept;
		vector2 CalculateDeltaBetweenCameraAndPlayer(vector2 objDistance, vector2 playgroundSize) noexcept;
		void ZoomAndCollisionRegionHandling(vector2 distanceBetweenPlayer) noexcept;
		void PositionHandling(float dt, const Object* player1, const Object* player2) noexcept;

		vector2 LinearInterpolation(vector2 currentPosition, vector2 targetPosition, float t);
		
		// Deprecated function
		void CalculateDirectionOffset(const Object* player1, const Object* player2, float offset, vector2& resultOffset) noexcept;
		EyesightTypeCode CalculateEyesightType(vector2 velocity) noexcept;
		vector2 GetUnitVectorWithGivenCode(EyesightTypeCode code) noexcept;

		// Camera shaking functions
		void ShakeCameraWhenAppropriate(float dt);
		float EaseOutQuint(float dt);
		bool IsShaking() const;


	private:
		struct CameraSet
		{
			Camera camera;
			CameraView cameraView;
		};

		CameraSet* selectedCamera = nullptr;
		std::unordered_map<std::string, std::shared_ptr<CameraSet>> cameraStorage;

		vector2 initCameraDetectRectSize{ 550.f, 400.f };
		vector2 cameraDetectRectSize{ initCameraDetectRectSize };

		constexpr static float maximumEyesightOffset_X{ 400.f };
		constexpr static float maximumEyesightOffset_Y{ 225.f };

		float initialShakingTime;
		float shakingTime;
		float shakingMagnitude;

		bool isZoomingFromOutside;
		float zoomT;
	};

	constexpr float CameraManager::GetInitZoomSize() const noexcept
	{
		return selectedCamera->cameraView.GetInitZoomSize();
	}
}

