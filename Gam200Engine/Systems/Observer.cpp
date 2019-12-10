/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.hpp
Author
        dbsqhd106@gmail.com
Creation Date: 08.29.2019

    Header file for the Application.cpp
******************************************************************************/

#include <Systems/Observer.hpp>

void Subject::addObserver(Observer *obs) {
    observerList.push_back(obs);
}
void Subject::removeObserver(Observer *obs) {
    observerList.erase(std::find(observerList.begin(), observerList.end(), obs));
}
void Subject::notify()
{
    for (const auto &obs : observerList)
    {
        obs->update();
    }
}
