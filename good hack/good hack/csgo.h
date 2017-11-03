#pragma once
#include <Windows.h>
#include "interfaces.h"

class c_csgo
{
private:
public:
	c_csgo();
	~c_csgo();
	iv_engine_client* m_engine;
	 i_client_mode* m_clientmode;
	 i_client* m_client;
	 i_client_entity_list* m_entitylist;

	void initialize();
};

extern c_csgo g_csgo;