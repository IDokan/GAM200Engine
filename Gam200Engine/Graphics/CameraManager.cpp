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

#include "CameraManager.hpp"
#include <Window/Application.hpp>
#include <Systems/Input.hpp>

Graphics::CameraManager::CameraManager()
{
	cameraStorage.clear();
	AddCamera("MainCamera");
	SelectCamera("MainCamera");
}

/**
 * \brief
 * For now, it do only set view size. However, Named for the possibility which do anything else...
 */
void Graphics::CameraManager::Init() noexcept
{
	InitializeCurrentCameraSetting();
}

void Graphics::CameraManager::InitializeCurrentCameraSetting() noexcept
{
	selectedCamera->cameraView.SetZoom(selectedCamera->cameraView.GetInitZoomSize());
	selectedCamera->cameraView.SetViewSize(Application::GetApplication()->GetWindowSize);
	selectedCamera->camera.SetCenter(vector2{ 0.f });
	selectedCamera->camera.ResetUp();
}

/**
 * \brief
 * \Notice Function name is "AddCamera" but it is able to initialize cameraSet when cameraTag is already exist value.
 * \param cameraTag : Key value for cameraStorage
 */
void Graphics::CameraManager::AddCamera(const std::string& cameraTag) noexcept
{
	cameraStorage.insert_or_assign(cameraTag, std::make_shared<CameraSet>());
}

bool Graphics::CameraManager::SelectCamera(const std::string& cameraTag) noexcept
{
	try
	{
		selectedCamera = cameraStorage.at(cameraTag).get();
	}
	catch (const std::out_of_range&)
	{
		selectedCamera = nullptr;
		// Log Something to notice fail.
		return false;
	}
	return true;
}

void Graphics::CameraManager::SetPosition(const vector2& position) noexcept
{
	selectedCamera->camera.SetCenter(position);
}

vector2 Graphics::CameraManager::GetPosition() const noexcept
{
	return selectedCamera->camera.GetCenter();
}

void Graphics::CameraManager::SetZoom(float zoom) noexcept
{
	selectedCamera->cameraView.SetZoom(zoom);
}

float Graphics::CameraManager::GetZoom() const noexcept
{
	return selectedCamera->cameraView.GetZoom();
}

void Graphics::CameraManager::SetViewSize(const vector2& size) noexcept
{
	selectedCamera->cameraView.SetViewSize(size);
}

void Graphics::CameraManager::SetViewSize(int width, int height) noexcept
{
	selectedCamera->cameraView.SetViewSize(width, height);
}

const vector2 Graphics::CameraManager::GetViewSize() const noexcept
{
	return selectedCamera->cameraView.GetViewSize();
}

void Graphics::CameraManager::SetFrameOfReference(CameraView::FrameOfReference frameOfReference) noexcept
{
	selectedCamera->cameraView.SetFrameOfReference(frameOfReference);
}

matrix3 Graphics::CameraManager::GetWorldToNDCTransform() const noexcept
{
	return selectedCamera->cameraView.GetCameraToNDCTransform() *
		selectedCamera->camera.WorldToCamera();
}

matrix3 Graphics::CameraManager::GetCameraToWorldTransform() const noexcept
{
	return selectedCamera->camera.CameraToWorld();
}

void Graphics::CameraManager::MoveUp(float dt, float distance) noexcept
{
	selectedCamera->camera.MoveUp(dt * distance);
}

void Graphics::CameraManager::MoveRight(float dt, float distance) noexcept
{
	selectedCamera->camera.MoveRight(dt * distance);
}

void Graphics::CameraManager::CameraMove(const vector2& position1, const vector2& position2, const float& zoomSize) noexcept
{
	DEBUGCameraMove(zoomSize);

    if (position1.x == -1.f ||
        position1.y == -1.f ||
        position2.x == -1.f ||
        position2.y == -1.f)
    {
        return;
    }

	PositionHandling(position1, position2);
	ZoomAndCollisionRegionHandling(vector2{ abs(position1.x - position2.x), abs(position1.y - position2.y) });
}

vector2 Graphics::CameraManager::GetDEBUGCameraRectSize() const noexcept
{
	return cameraDetectRectSize;
}

#ifdef _DEBUG
void Graphics::CameraManager::DEBUGCameraMove(const float& zoomSize) noexcept
#else
void Graphics::CameraManager::DEBUGCameraMove(const float& /*zoomSize*/) noexcept
#endif  
{
#ifdef _DEBUG

	// Camera Movement
	if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_RIGHT))
	{
		input.SetPresentMousePosition(input.GetMouseAbsolutePosition());
	}
	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		// Get an relative distance with current zoom size
		const vector2& mousePosition = input.GetMouseAbsolutePosition();
		const vector2& distance = (input.GetPresentMousePosition() - mousePosition) / selectedCamera->cameraView.GetZoom();

		// Apply distance into current Up and Right vector
		selectedCamera->camera.MoveRight(distance.x);
		selectedCamera->camera.MoveUp(distance.y);

		input.SetPresentMousePosition(mousePosition);
	}

	// Camera Zoom In and Out
	if (input.MouseWheelScroll() > 0)
	{
		selectedCamera->cameraView.SetZoom(
			selectedCamera->cameraView.GetZoom() * zoomSize
		);
	}
	if (input.MouseWheelScroll() < 0)
	{
		selectedCamera->cameraView.SetZoom(
			selectedCamera->cameraView.GetZoom() / zoomSize
		);
	}

	// Disable camera rotation
	//// Rotating Camera
	//if (input.IsKeyPressed(GLFW_KEY_E))
	//{
	//	selectedCamera->camera.Rotate(0.05f);
	//}
	//if (input.IsKeyPressed(GLFW_KEY_Q))
	//{
	//	selectedCamera->camera.Rotate(-0.05f);
	//}
#endif
}

vector2 Graphics::CameraManager::CalculateDeltaBetweenCameraAndPlayer(vector2 objDistance, vector2 playgroundSize) noexcept
{
	vector2 delta{};
	if (objDistance.x - playgroundSize.x > 0)
	{
		delta.x += (objDistance.x - playgroundSize.x);
	}
	else if (objDistance.x + playgroundSize.x < 0)
	{
		delta.x += (objDistance.x + playgroundSize.x);
	}
	if (objDistance.y - playgroundSize.y > 0)
	{
		delta.y += (objDistance.y - playgroundSize.y);
	}
	else if (objDistance.y + playgroundSize.y < 0)
	{
		delta.y += (objDistance.y + playgroundSize.y);
	}
	return delta;
}

void Graphics::CameraManager::ZoomAndCollisionRegionHandling(vector2 distanceBetweenPlayer) noexcept
{

	// Zoom Out part
	if (distanceBetweenPlayer.x > 2 * cameraDetectRectSize.x)
	{
		SetZoom(GetZoom()*((2 * cameraDetectRectSize.x) / distanceBetweenPlayer.x));
		cameraDetectRectSize.x = distanceBetweenPlayer.x / 2;
	}
	if (distanceBetweenPlayer.y > 2 * cameraDetectRectSize.y)
	{
		SetZoom(GetZoom() * ((2 * cameraDetectRectSize.y) / distanceBetweenPlayer.y));
		cameraDetectRectSize.y = distanceBetweenPlayer.y / 2;
	}

	// Zoom In part
	if (cameraDetectRectSize.x > initCameraDetectRectSize.x)
	{
		if (distanceBetweenPlayer.x< 2 * cameraDetectRectSize.x)
		{
			SetZoom(GetZoom() * ((2 * cameraDetectRectSize.x) / distanceBetweenPlayer.x));
			cameraDetectRectSize.x = distanceBetweenPlayer.x / 2;
		}
	}
	if (cameraDetectRectSize.y > initCameraDetectRectSize.y)
	{
		if (distanceBetweenPlayer.y < 2 * cameraDetectRectSize.y)
		{
			SetZoom(GetZoom() * ((2 * cameraDetectRectSize.y) / distanceBetweenPlayer.y));
			cameraDetectRectSize.y = distanceBetweenPlayer.y / 2;
		}
	}

	if (cameraDetectRectSize.x < initCameraDetectRectSize.x)
	{
		cameraDetectRectSize.x = initCameraDetectRectSize.x;
	}
	if (cameraDetectRectSize.y < initCameraDetectRectSize.y)
	{
		cameraDetectRectSize.y = initCameraDetectRectSize.y;
	}
}

void Graphics::CameraManager::PositionHandling(vector2 position1, vector2 position2) noexcept
{
	vector2 cameraPosition = GetPosition();

	vector2 player1Delta = CalculateDeltaBetweenCameraAndPlayer(position1 - cameraPosition, cameraDetectRectSize);

	vector2 player2Delta = CalculateDeltaBetweenCameraAndPlayer(position2 - cameraPosition, cameraDetectRectSize);

	vector2 totalDelta{player1Delta + player2Delta};

	SetPosition(cameraPosition + totalDelta);
}


