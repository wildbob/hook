#pragma once
#include "func_hook.h"
#include "interfaces.h"

namespace g_hooks
{
	extern bool __stdcall create_move(float frametime, c_cmd* pCmd);
	extern void __stdcall create_move_proxy(int sequence_number, float input_sample_frametime, bool active);
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
