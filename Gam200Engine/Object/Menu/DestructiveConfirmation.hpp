/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   DestructiveConfirmation.hpp
Author
        rtd99062@gmail.com
Creation Date: 06.19.2020

    Header file for DestructiveConfirmation
******************************************************************************/
#pragma once
#include <Object/Menu/MenuObject.hpp>
#include <functional>

class DestructiveConfirmation : public MenuObject
{
public:
    const vector2 buttonInitSize{ 0.45f, 0.245f };
public:
    enum MenuEnum
    {
        Sure,
        No,
    };
public:
    DestructiveConfirmation();
    virtual ~DestructiveConfirmation();

    virtual MenuObject* MenuUpdate(float dt);
    virtual void AddChildObjectsDynamically();
    virtual void CleanChildObjects();

    virtual void LerpIn(float timer);
    virtual void LerpOut(float timer);

    void SetDoThis(std::function<void(void)> newDoThis);

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
    Object* sureButton;
    Object* noButton;
    Object* selectionHighlight;
    MenuEnum currentSelection;

    Transform sureTransform;
    Transform noTransform;

    bool isTransparency;

    bool playerPressEnter;

    std::function<void(void)> doThis;
};