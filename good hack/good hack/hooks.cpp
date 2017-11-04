#pragma once
#include "hooks.h"
#include "csgo.h"
#include "hack.h"
#include "entity.h"

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
		vgui_surface_hook.setup(g_csgo.m_surface);
		panel_hook.setup(g_csgo.m_panel);
	
		//hooking
		client_hook.hook_index(21, create_move_proxy);

		panel_hook.hook_index(41, paint_traverse);
	}

	void destructor()
	{
		client_hook.unhook_all();
		client_mode_hook.unhook_all();
		engine_hook.unhook_all();
		vgui_surface_hook.unhook_all();
		panel_hook.unhook_all();
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

	void __stdcall create_move(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket)
	{
		auto ofunc = client_hook.get_original<create_move_t>(21);

		ofunc(g_csgo.m_client, sequence_number, input_sample_frametime, active);

		auto local = c_entity::get_local_player();
		auto cmd = g_csgo.m_input->GetUserCmd(0, sequence_number);
		auto verified = g_csgo.m_input->GetVerifiedCmd(0, sequence_number);


		if (!cmd || cmd->command_number == 0 || !local)
			return;

		auto weapon = local->get_active_weapon();;

		if (!weapon)
			return;


		for (auto& hacks : g_hacks.m_hacks)
		{
			hacks->tick();
		}

	}

	void __stdcall paint_traverse(PVOID thisptr, int edx, unsigned int VGUIPanel, bool forceRepaint, bool allowForce)
	{		
		static auto ofunc = panel_hook.get_original<paint_traverse_t>(41);
		ofunc(thisptr, VGUIPanel, forceRepaint, allowForce);

		if (!strcmp("MatSystemTopPanel", g_csgo.m_panel->get_name(VGUIPanel)))
		{
			for (auto& hacks : g_hacks.m_hacks)
			{
				hacks->draw();
			}
		}
	}
}

