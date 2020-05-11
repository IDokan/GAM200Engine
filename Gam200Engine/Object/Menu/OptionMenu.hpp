/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   OptionMenu.hpp
Author
        rtd99062@gmail.com
Creation Date: 05.11.2020

    Header file for the Option menu
******************************************************************************/
#pragma once
#include <Object/Menu/MenuObject.hpp>

class OptionMenu : public MenuObject
{
public:
    enum MenuEnum
    {
        Unknown
    };
public:
    OptionMenu();
    virtual ~OptionMenu();

    virtual MenuObject* MenuUpdate(float dt);
    virtual void AddChildObjectsDynamically();

private:
    void SetCurrentSelection(MenuEnum newValue);
    void UpdateSelection() noexcept;
    Object* GetSelectedObject();
    void UpdateSelectionHighlightTransformation();
    void UpdateSelectionHighlightTransparency(float dt);

private:
    Object* unknownButton;
    Object* selectionHighlight;
    MenuEnum currentSelection;

    bool isTransparency;
};