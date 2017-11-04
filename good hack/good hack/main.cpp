#include <process.h>
#include "csgo.h"
#include "hooks.h"

void cheat_init(PVOID pParam)
{
	g_utils::GetHandleSafe("serverbrowser.dll");

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	SetConsoleTitle("good hack");

	g_csgo.initialize();
	g_hooks::initialize();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		_beginthread(cheat_init, 0, NULL);

		break;

	case DLL_PROCESS_DETACH:

		break;
	}

	return TRUE;
}