/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   MainMenu.hpp
Author
        rtd99062@gmail.com
Creation Date: 07.06.2020

    Header file for the Main menu
******************************************************************************/
#pragma once
#include <Object/Menu/MenuObject.hpp>

class MainMenu : public MenuObject
{
public:
    const vector2 buttonInitSize{ 0.25f, 0.15f };
public:
    enum MenuEnum
    {
        NEWGAME,
        LOADGAME,
        HOWTOPLAY,
        OPTION,
        CREDIT,
        QUIT,
    };
public:
    MainMenu();
    virtual ~MainMenu();

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
    Object* newButton;
    Object* loadButton;
    Object* howToPlayButton;
    Object* optionButton;
    Object* creditButton;
    Object* quitButton;
    Object* selectionHighlight;
    MenuEnum currentSelection;

    Transform newTransform;
    Transform loadTransform;
    Transform howToPlayTransform;
    Transform optionTransform;
    Transform creditTransform;
    Transform quitTransform;

    bool isTransparency;

    bool playerPressEnter;
};