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

#pragma once
#include <iostream>
#include <vector>
#include <string>

class Observer
{
public:
    virtual void update() = 0;
};

class Subject
{
    std::vector<Observer*> observerList{};
public:
    Subject() = default;
    void addObserver(Observer *obs);
    void removeObserver(Observer *obs);
    void notify();
};

//It will be using later like under example.
//class Example : public Observer
//{
//public:
//    Subject* ex;
//    Example(Subject * o)
//    {
//        ex = o;
//        ex->addObserver(this);
//    }
//    void update()override {
//        std::cout << "Hello! I'm example! " << std::endl;
//    }
//};
