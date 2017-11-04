#pragma once
#include "hack.h"

class c_visuals : public c_hack
{
private:
public:
	virtual void tick() override;
	virtual void draw() override;
	virtual void update() override;
};