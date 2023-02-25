
#include <cstdint>
#include <MinHook.h>

class InputHandler_PIUIO {
public:
    char pad[0xA0];
    uint32_t GameLights[2][33];
};

uintptr_t oSetLightsMappings;
void __fastcall hk_InputHandler_PIUIO_SetLightsMappings(InputHandler_PIUIO* handler) {
    (decltype(&hk_InputHandler_PIUIO_SetLightsMappings)(oSetLightsMappings))(handler);

    handler->GameLights[0][0] = 4;
    handler->GameLights[0][1] = 8;
    handler->GameLights[0][2] = 16;
    handler->GameLights[0][3] = 32;
    handler->GameLights[0][4] = 64;
    handler->GameLights[1][0] = 0x40000;
    handler->GameLights[1][1] = 0x80000;
    handler->GameLights[1][2] = 0x100000;
    handler->GameLights[1][3] = 0x200000;
    handler->GameLights[1][4] = 0x400000;
}

extern "C" __declspec(dllexport) void HidD_SetFeature() {

}

extern "C" __declspec(dllexport) void HidD_GetAttributes() {

}

extern "C" __declspec(dllexport) void HidD_GetHidGuid() {

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call != DLL_PROCESS_ATTACH)
        return true;

    if (MH_Initialize() != MH_OK) 
        MessageBoxA(NULL, "Failed to initialize MinHook", NULL, MB_ICONERROR);

    uintptr_t pPXXBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL));
    uintptr_t pSetLightsMappings = pPXXBase + 0x22A580;

    if (MH_CreateHook(reinterpret_cast<LPVOID>(pSetLightsMappings), hk_InputHandler_PIUIO_SetLightsMappings, reinterpret_cast<LPVOID*>(&oSetLightsMappings))) 
        MessageBoxA(NULL, "Failed to hook InputHandler_PIUIO::SetLightsMappings", NULL, MB_ICONERROR);

    if (MH_EnableHook(MH_ALL_HOOKS))
        MessageBoxA(NULL, "Failed to enable hooks", NULL, MB_ICONERROR);

    return true;
}