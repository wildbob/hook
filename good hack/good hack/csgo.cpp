#pragma once
#include "csgo.h"

c_csgo g_csgo;


c_csgo::c_csgo()
{
	m_client = nullptr;
	m_clientmode = nullptr;
	m_engine = nullptr;
	m_entitylist = nullptr;
	m_surface = nullptr;
	m_panel = nullptr;
	m_input = nullptr;
}

c_csgo::~c_csgo()
{
	delete[] m_client;
	delete[] m_clientmode;
	delete[] m_engine;
	delete[] m_entitylist;
	delete[] m_surface;
	delete[] m_panel;
	delete[] m_input;
}


void c_csgo::initialize()
{
	if (!m_engine)
		m_engine = g_utils::get_interface<iv_engine_client>("engine.dll", "VEngineClient");

	if (!m_client)
		m_client = g_utils::get_interface<i_client>("client.dll", "VClient");

	if (!m_entitylist)
		m_entitylist = g_utils::get_interface<i_client_entity_list>("client.dll", "VClientEntityList");

	if (!m_surface)
		m_surface = g_utils::get_interface< i_surface >("vguimatsurface.dll", "VGUI_Surface");

	if (!m_clientmode)
		m_clientmode = **(i_client_mode***)((*(uintptr_t**)m_client)[10] + 0x5);

	if (!m_panel)
		m_panel = g_utils::get_interface<i_panel>("vgui2.dll", "VGUI_Panel");

	if (!m_input)
		m_input = **reinterpret_cast< i_input*** >((*reinterpret_cast< uintptr_t** >(m_client))[15] + 0x1);
}