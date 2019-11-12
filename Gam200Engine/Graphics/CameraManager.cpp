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
#include <Application.hpp>
#include <Input.hpp>

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
	selectedCamera->cameraView.SetViewSize(Application::GetApplication()->GetWindowSize);
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

	vector2 cameraPosition = GetPosition();

	vector2 distance{ position1 - cameraPosition };

	vector2 cameraDetectRectSize{ 500.f, 300.f };

	vector2 player1Delta = CalculateDeltaBetweenCameraAndPlayer(position1 - cameraPosition, cameraDetectRectSize);

	vector2 player2Delta = CalculateDeltaBetweenCameraAndPlayer(position2 - cameraPosition, cameraDetectRectSize);

	vector2 totalDelta{};

	printf("player1Delta x = %f, y = %f\n", player1Delta.x, player1Delta.y);
	printf("player2Delta x = %f, y = %f\n\n\n", player2Delta.x, player2Delta.y);
	if (player1Delta.x == 0 && player1Delta.y == 0)
	{
		totalDelta += player2Delta;
	}
	if (player2Delta.x == 0 && player2Delta.y == 0)
	{
		totalDelta += player1Delta;
	}
	
	SetPosition(cameraPosition + totalDelta);
}

void Graphics::CameraManager::DEBUGCameraMove(const float& zoomSize) noexcept
{
#ifdef _DEBUG

	// Camera Movement
	if (input.IsMouseButtonTriggered(GLFW_MOUSE_BUTTON_RIGHT))
	{
		input.SetPresentMousePosition(input.GetMousePosition());
	}
	if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
	{
		const vector2& mousePosition = input.GetMousePosition();
		const vector2& presentMousePosition = input.GetPresentMousePosition();

		selectedCamera->camera.SetCenter(
			selectedCamera->camera.GetCenter() + (presentMousePosition - mousePosition)
		);

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

