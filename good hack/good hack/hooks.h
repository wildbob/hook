#pragma once
#include "func_hook.h"
#include "interfaces.h"

typedef void(__thiscall* paint_traverse_t)(PVOID, unsigned int, bool, bool);
using create_move_t = void(__thiscall*)(i_client*, int, float, bool);

namespace g_hooks
{
	extern void __stdcall create_move(int sequence_number, float input_sample_frametime, bool active, bool& bSendPacket);
	extern void __stdcall create_move_proxy(int sequence_number, float input_sample_frametime, bool active);
	extern void __stdcall paint_traverse(PVOID thisptr, int edx, unsigned int VGUIPanel, bool forceRepaint, bool allowForce);
	//vfunc_hooks
	extern vfunc_hook client_hook;
	extern vfunc_hook d3d_hook;
	extern vfunc_hook panel_hook;
	extern vfunc_hook modelrender_hook;
	extern vfunc_hook vgui_surface_hook;
	extern vfunc_hook enginetrace_hook;
	extern vfunc_hook client_mode_hook;
	extern vfunc_hook engine_hook;
	extern vfunc_hook steam_networking;
	extern vfunc_hook game_event_hook;

	extern void destructor();
	extern void initialize();
}
