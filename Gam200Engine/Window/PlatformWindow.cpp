/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   PlatformWindow.cpp
Author
    - jaemin.woo wjm9932@gmail.com
Creation Date: 08.05.2019

    Source file for making window
******************************************************************************/
#define UNUSED

#include <Window/PlatformWindow.hpp>
#include <Systems/Input.hpp>
#include <Graphics/glCheck.hpp>
#include <Graphics/GL.hpp>
#include <Graphics/ImGui/MyImGui.hpp>
#include <Scenes/SceneManager.hpp>

#include <stb_image.h>

namespace
{
    float originalBgmVolume;
    struct WindowSizePosition
    {
        WindowSizePosition(float width, float height, float x = 0.f, float y = 0.f)
            :width(width), height(height), x(x), y(y)
        {}

        float width;
        float height;
        float x;
        float y;
    };

    WindowSizePosition GetWindowValueByResolution(WindowSizePosition raw)
    {
        float  virtual_width = 1600;
        float virtual_height = 900;
        float targetAspectRatio = virtual_width / virtual_height;

        float adjustedWidth = static_cast<float>(raw.width);
        // Why + 0.5f ?
        float adjustedHeight = (adjustedWidth / targetAspectRatio + 0.5f);

        // if height is shorter than width,
        if (adjustedHeight > static_cast<float>(raw.height))
        {
            adjustedHeight = static_cast<float>(raw.height);
            adjustedWidth = (adjustedHeight * targetAspectRatio + 0.5f);
        }
        float vp_x = (static_cast<float>(raw.width) / 2.f) - (adjustedWidth / 2.f);
        float vp_y = (static_cast<float>(raw.height) / 2.f) - (adjustedHeight / 2.f);

        return WindowSizePosition{ adjustedWidth, adjustedHeight, vp_x, vp_y };
    }

    void KeyCallback(GLFWwindow*, int key, int scancode, int action, int)
    {
        UNUSED(scancode);
        input.SetKeyboardInput(key, action);
    }
    void MousePositionCallback(GLFWwindow* window, double xPos, double yPos)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        WindowSizePosition result = GetWindowValueByResolution(WindowSizePosition{ static_cast<float>(width), static_cast<float>(height) });

        vector2 virtualSize{ 1600, 900 };

        xPos = (xPos - result.x) * virtualSize.x / result.width;
        yPos = (yPos - result.y) * virtualSize.y / result.height;

        input.SetMousePos(static_cast<float>(xPos), static_cast<float>(yPos));
    }
    //Added by Robin
    void MinimizeWindowCallback(GLFWwindow* window, int)
    {
        const int minimized = glfwGetWindowAttrib(window, GLFW_ICONIFIED);
       
        if (minimized) {
            if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::MainMenu) {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::HOWTOPLAY_MAIN_BGM);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(HOWTOPLAY_MAIN_BGM, 0.f);
            }
            else if(SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::HowToPlay)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::HOWTOPLAY_MAIN_BGM);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(HOWTOPLAY_MAIN_BGM, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Credit)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::CREADIT_BGM);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(CREADIT_BGM, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level1)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::BACKGROUND_SOUND);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level2)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::BACKGROUND_SOUND);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level3)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::BACKGROUND_SOUND);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level4)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::BACKGROUND_SOUND2);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND2, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level5)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::BACKGROUND_SOUND2);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND2, 0.f);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level6)
            {
                originalBgmVolume = SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().GetCurrentChVolume(SOUNDS::BACKGROUND_SOUND2);
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND2, 0.f);
            }
            glfwWaitEvents();
        }
        else {
            if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::MainMenu) {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(HOWTOPLAY_MAIN_BGM, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::HowToPlay)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(HOWTOPLAY_MAIN_BGM, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Credit)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(CREADIT_BGM, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level1)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level2)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level3)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level4)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND2, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level5)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND2, originalBgmVolume);
            }
            else if (SceneManager::GetSceneManager()->GetCurrentScene()->GetSceneInfo() == GameScenes::Level6)
            {
                SceneManager::GetSceneManager()->GetCurrentScene()->GetSoundManager().SetVolume(BACKGROUND_SOUND2, originalBgmVolume);
            }
        }

    }
    void MouseButtonCallback(GLFWwindow*, int button, int action, int)
    {
        input.SetMouseButtonInput(button, action);
    }
    void MouseWheelScroll(GLFWwindow*, double x_offset, double y_offset)
    {
        input.SetMouseWheel(x_offset, y_offset);
    }
    void WindowSizeCallback(GLFWwindow*, int width, int height)
    {
        WindowSizePosition result = GetWindowValueByResolution(WindowSizePosition{ static_cast<float>(width), static_cast<float>(height) });

        Graphics::GL::set_display_area(
            static_cast<int>(result.width),
            static_cast<int>(result.height),
            static_cast<int>(result.x),
            static_cast<int>(result.y));
    }
}

bool PlatformWindow::CreateWindow() noexcept
{
    
    if (!glfwInit())
    {
        return false;
    }

    xPos = 100;
    yPos = 100;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);



    GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
    window = glfwCreateWindow(mode->width, mode->height, "engine", pMonitor, nullptr);
    glfwSetWindowPos(window, xPos, yPos);
	GLFWimage icon[1];
	icon[0].pixels = stbi_load("../assets/textures/Icon/icon.png", &icon[0].width, &icon[0].height, 0, 4);
	glfwSetWindowIcon(window, 1, &icon[0]);

	if (!window)
	{
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MousePositionCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseWheelScroll);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetWindowTitle(window, "Cheese Roll");
    glfwSetWindowIconifyCallback(window, MinimizeWindowCallback);
	glfwSwapInterval(true);
    glEnable(GL_DEPTH_BUFFER);


    MyImGui::InitImGui(window);
    glewInit();


    return true;
}

void PlatformWindow::PollEvent() noexcept
{
    glCheck(glfwPollEvents());
}

void PlatformWindow::SwapBackBuffer() noexcept
{
    glCheck(glfwSwapBuffers(window));
}

bool PlatformWindow::IsFullscreen() noexcept
{
    return glfwGetWindowMonitor(window);
}

void PlatformWindow::TurnOnMonitorVerticalSynchronization(bool enable) noexcept
{
    isVsyncOn = enable;
    glCheck(glfwSwapInterval(enable));
}

bool PlatformWindow::IsMonitorVerticalSynchronizationOn() noexcept
{
    return isVsyncOn;
}

void PlatformWindow::ToggleFullscreen() noexcept
{
    if (!IsFullscreen())
    {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		glCheck(glfwGetWindowPos(window, &xPos, &yPos));
		glCheck(glfwGetWindowSize(window, &xSize, &ySize));
		glCheck(glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0));
		glCheck(glViewport(0, 0, mode->width, mode->height));
		windowSize.width = static_cast<float>(mode->width);
		windowSize.height = static_cast<float>(mode->height);
	}
	else
	{
		glCheck(glfwSetWindowMonitor(window, nullptr, xPos, yPos, xSize, ySize, 0));
		glCheck(glViewport(0, 0, xSize, ySize));
		windowSize.width = static_cast<float>(xSize);
		windowSize.height = static_cast<float>(ySize);

		GLFWimage icon[1];
		icon[0].pixels = stbi_load("../assets/textures/Icon/icon.png", &icon[0].width, &icon[0].height, 0, 4);
		glfwSetWindowIcon(window, 1, &icon[0]);
	}
}

vector2 PlatformWindow::GetPlatformWindowSize() noexcept
{
    return windowSize;
}

bool PlatformWindow::ShouldClose() noexcept
{
    return glfwWindowShouldClose(window);
}

/**
 * \brief
 * It's kind of clean up function for window
 * I found it from Cherno.
 */
void PlatformWindow::ClearWindow() const noexcept
{
    glfwDestroyWindow(window);
    glfwTerminate();

}
//glfw �Լ��߿��� ���� minimize���� �ƴ��� üũ�ϴ� �Լ��� ��ã�ڴ�
//
