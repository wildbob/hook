#pragma once
#include "visual.h"
#include "math.h"
#include "drawings.h"
#include "entity.h"

auto c_visuals::get_bounding_box(c_entity* entity) -> b_box
{
	b_box box{};

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	Vector m_min = *entity->get_min();
	Vector m_max = *entity->get_max();

	const matrix3x4_t& trans = entity->ent_world_transform();

	Vector points[] = {
		Vector(m_min.x, m_min.y, m_min.z),
		Vector(m_min.x, m_max.y, m_min.z),
		Vector(m_max.x, m_max.y, m_min.z),
		Vector(m_max.x, m_min.y, m_min.z),
		Vector(m_max.x, m_max.y, m_max.z),
		Vector(m_min.x, m_max.y, m_max.z),
		Vector(m_min.x, m_min.y, m_max.z),
		Vector(m_max.x, m_min.y, m_max.z)
	};

	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++) {
		g_math::vector_transform(points[i], trans, pointsTransformed[i]);
	}


	if (!g_drawings.world_to_screen(pointsTransformed[3], flb) || !g_drawings.world_to_screen(pointsTransformed[5], brt)
		|| !g_drawings.world_to_screen(pointsTransformed[0], blb) || !g_drawings.world_to_screen(pointsTransformed[4], frt)
		|| !g_drawings.world_to_screen(pointsTransformed[2], frb) || !g_drawings.world_to_screen(pointsTransformed[1], brb)
		|| !g_drawings.world_to_screen(pointsTransformed[6], blt) || !g_drawings.world_to_screen(pointsTransformed[7], flt))
		return box;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	auto left = flb.x;
	auto top = flb.y;
	auto right = flb.x;
	auto bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	box.x = left;
	box.y = top;
	box.w = right - left;
	box.h = bottom - top;

	return box;
}


void c_visuals::tick()
{

}

void c_visuals::update()
{

}

void c_visuals::draw()
{
	for (int i = 0; i < g_csgo.m_entitylist->get_hightest_entity_index(); i++)
	{
		c_entity* entity = static_cast<c_entity*>(g_csgo.m_entitylist->get_entity(i));

		if (!entity->is_valid_player())
			continue;

		auto b_box = this->get_bounding_box(entity);

		g_drawings.draw_outlined_rect(b_box.x, b_box.y, b_box.w, b_box.h, Color(255, 0, 0, 255));
	}
}