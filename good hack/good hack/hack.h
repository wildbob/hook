#pragma once
#include "csgo.h"
#include <vector>

class c_hack
{
private:
public:
	virtual void tick() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
};

class c_hack_manager
{
private:
public:
	void intialize();
	std::vector<c_hack*> m_hacks;
};

extern c_hack_manager g_hacks;