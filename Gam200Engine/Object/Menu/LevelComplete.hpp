/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   LevelComplete.hpp
Author
        rtd99062@gmail.com
Creation Date: 07.13.2020

    Header file for the Level Complete Menu
******************************************************************************/
#pragma once
#include <Object/Menu/MenuObject.hpp>

class ParticleEmitter;

class LevelComplete : public MenuObject
{
public:
    const vector2 buttonInitSize{ 0.5f, 0.25f };
public:
    enum MenuEnum
    {
        Go2NextLevel,
        Back2Main,
    };
public:
    LevelComplete();
    virtual ~LevelComplete();

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
    Object* goNextButton;
    Object* goMainMenuButton;
    Object* selectionHighlight;
    ParticleEmitter* confetti;
    MenuEnum currentSelection;

    Transform nextTransform;
    Transform mainMenuTransform;

    bool isTransparency;

    bool playerPressEnter;

};