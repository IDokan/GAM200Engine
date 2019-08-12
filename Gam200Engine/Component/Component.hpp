#pragma once
class Component
{
public:
	Component();
	virtual ~Component();

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Clear() = 0;


};

