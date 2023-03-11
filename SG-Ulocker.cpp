#include <Windows.h>
#include "pch.h"
#include <Minhook.h>
#include <cstdio>


uintptr_t base = (uintptr_t)GetModuleHandle(NULL);
uintptr_t GameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

uintptr_t HasSkinOffset = 0x363020;
uintptr_t HasFootstepOffset = 0x362F90;
uintptr_t HasEmoteOffset = 0x362E80;
uintptr_t HasAnimationOffset = 0x362D50;

void CreateConsole()
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
}

bool(__fastcall* HasSkin_o)(DWORD*, const char*, DWORD*); 
bool __stdcall HasSkin_h(DWORD* __this, const char* skinID, DWORD* method)
{
    return true;
}
bool(__fastcall* HasFootstep_o)(DWORD*, const char*, DWORD*);
bool __stdcall Hasfootstep_h(DWORD* __this, const char* footstepID, DWORD* method)
{
    return true;
}
bool(__fastcall* HasEmote_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasEmote_h(DWORD* __this, const char* emoteID, DWORD* method)
{
    return true;
}
bool(__fastcall* HasAnimation_o)(DWORD*, const char*, DWORD*);
bool __stdcall HasAnimation_h(DWORD* __this, const char* animationID, DWORD* method)
{
    return true;
}

void main()
{
    MH_Initialize();
    CreateConsole();
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasSkinOffset), &HasSkin_h, (LPVOID*)&HasSkin_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasFootstepOffset), &Hasfootstep_h, (LPVOID*)&HasFootstep_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmoteOffset), &HasEmote_h, (LPVOID*)&HasEmote_o);
    MH_CreateHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmoteOffset), &HasAnimation_h, (LPVOID*)&HasAnimation_o);
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasSkinOffset));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasFootstepOffset));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasEmoteOffset));
    MH_EnableHook(reinterpret_cast<LPVOID*>(GameAssembly + HasAnimationOffset));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
