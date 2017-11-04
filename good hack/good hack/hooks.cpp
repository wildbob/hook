#pragma once
#include "hooks.h"
#include "csgo.h"
#include "hack.h"

namespace g_hooks
{
	vfunc_hook client_hook;
	vfunc_hook d3d_hook;
	vfunc_hook panel_hook;
	vfunc_hook modelrender_hook;
	vfunc_hook vgui_surface_hook;
	vfunc_hook enginetrace_hook;
	vfunc_hook client_mode_hook;
	vfunc_hook engine_hook;
	vfunc_hook steam_networking;
	vfunc_hook game_event_hook;

	void initialize()
	{
		client_hook.setup(g_csgo.m_client);
		client_mode_hook.setup(g_csgo.m_clientmode);	
		engine_hook.setup(g_csgo.m_engine);
	
		client_hook.hook_index(21, create_move_proxy);
	}

	void destructor()
	{
		client_hook.unhook_all();
		client_mode_hook.unhook_all();
		engine_hook.unhook_all();
	}

	__declspec(naked) void __stdcall create_move_proxy(int sequence_number, float input_sample_frametime, bool active)
	{
		__asm
		{
			push ebp
			mov  ebp, esp
			push ebx
			lea  ecx, [esp]
			push ecx
			push dword ptr[active]//active
			push dword ptr[input_sample_frametime]//input_sample_frametime
			push dword ptr[sequence_number]//sequence_number
			call create_move
			pop  ebx
			pop  ebp
			retn 0Ch
		}
	}

	bool __stdcall create_move(float frametime, c_cmd* pCmd)
	{
		if (!pCmd)
			return false;

		if (!pCmd->command_number)
			return false;


		for (auto& hacks : g_hacks.m_hacks)
		{
			hacks->tick();
		}

	}
}

