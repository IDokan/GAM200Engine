/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   BaseMenu.hpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Header file for the Base menu
******************************************************************************/
#pragma once
#include <Object/Menu/MenuObject.hpp>

class BaseMenu : public MenuObject
{
public:
    const vector2 buttonInitSize{ 0.5f, 0.25f };
public:
    enum MenuEnum
    {
        Resume,
        Option,
        Quit,
    };
public:
    BaseMenu();
    virtual ~BaseMenu();

    virtual MenuObject* MenuUpdate(float dt);
    virtual void AddChildObjectsDynamically();
    virtual void CleanChildObjects();

    virtual void LerpIn(float timer);
    virtual void LerpOut(float timer);

private:
    void SetCurrentSelection(MenuEnum newValue);
    void UpdateSelection() noexcept;
    Object* GetSelectedObject();
    void UpdateSelectionHighlightTransformation();
    void UpdateSelectionHighlightTransparency(float dt);

    float EaseInBounce(float timer);
    float EaseOutBounce(float timer);

private:
    Object* menuBackground;
    Object* resumeButton;
    Object* optionButton;
    Object* exitButton;
    Object* selectionHighlight;
    MenuEnum currentSelection;

    Transform resumeTransform;
    Transform optionTransform;
    Transform exitTransform;

    bool isTransparency;

    bool playerPressEnter;

};