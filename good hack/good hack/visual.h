#pragma once
#include "hack.h"
#include "entity.h"

class c_visuals : public c_hack
{
private:
	struct b_box
	{
		int x, y, w, h;
	};
	b_box get_bounding_box(c_entity* entity);

public:
	virtual void tick() override;
	virtual void draw() override;
	virtual void update() override;
};