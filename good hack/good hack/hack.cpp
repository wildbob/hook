#include "hack.h"
#include "visual.h"

c_hack_manager g_hacks;
c_visuals temp_visuals;

void c_hack_manager::intialize()
{
	m_hacks.push_back(&temp_visuals);
}