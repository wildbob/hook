#pragma once
#include "csgo.h"

c_csgo g_csgo;


c_csgo::c_csgo()
{
	m_client = nullptr;
	m_clientmode = nullptr;
	m_engine = nullptr;
	m_entitylist = nullptr;
}

c_csgo::~c_csgo()
{
	delete[] m_client;
	delete[] m_clientmode;
	delete[] m_engine;
	delete[] m_entitylist;
}


void c_csgo::initialize()
{
	if (!m_engine)
		m_engine = g_utils::get_interface<iv_engine_client>("engine.dll", "VEngineClient");

	if (!m_client)
		m_client = g_utils::get_interface<i_client>("client.dll", "VClient");

	if (!m_entitylist)
		m_entitylist = g_utils::get_interface<i_client_entity_list>("client.dll", "VClientEntityList");

	if (!m_clientmode)
		m_clientmode = **(i_client_mode***)((*(uintptr_t**)m_client)[10] + 0x5);
}