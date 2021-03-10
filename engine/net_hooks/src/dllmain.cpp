#include "pch.h"
#include "hook.h"
#include "pipe_client.h"
#include "pipe_constants.h"

#include <iostream>

SIZE_T maxLen;
LPWSABUF lpBuffers;
DWORD dwBufferCount;
LPDWORD lpNumberOfBytesRecvd;
PipeClient *pipe = NULL;

void hookWSARecvStart(SIZE_T* stack) {
    maxLen = 0;
    lpBuffers = (LPWSABUF) stack[1];
    dwBufferCount = stack[2];
    for (int i(0); i < dwBufferCount; i++) {
        WSABUF wsaBuf = lpBuffers[i];
        maxLen += wsaBuf.len;
    }
    lpNumberOfBytesRecvd = (LPDWORD) stack[3];
}

void hookWSARecvEnd() {
    if (lpNumberOfBytesRecvd) {
        DWORD len = *lpNumberOfBytesRecvd;
        if (len <= maxLen) {
            //printf("%x ", len);
            int totalLen = 0;
            for (int i(0); i < dwBufferCount && totalLen < len; i++) {
                WSABUF wsaBuf = lpBuffers[i];
                for (int i2(0); i2 < wsaBuf.len && totalLen < len; i2++) {
                    char c = wsaBuf.buf[i2];
                    totalLen++;
                    printf("%x", c);
                }
            }
        }
    }
}

void hookSend(SIZE_T* stack) {

}

void initPipe() {
    bool pipeSuccess;
    pipe = new PipeClient(pipeSuccess);
    if (pipeSuccess) {
        const char sync[] = { SYNC };
        pipe->sendData((char*)sync, 1);
    }
    else {
        /*DBG*/
    }
}

void initHooks() {
    HMODULE module = GetModuleHandleA("WS2_32.dll");
    if (module) {
        SIZE_T wsarecvStartAddr = (SIZE_T)module + 0x10500;
        HookInjector injector(wsarecvStartAddr, 15, &hookWSARecvStart);
        injector.inject();
        SIZE_T wsarecvEndAddr = (SIZE_T)module + 0x10679;
        injector = HookInjector(wsarecvEndAddr, 16, &hookWSARecvEnd);
        injector.inject();
        SIZE_T sendAddr = (SIZE_T)module + 0x2320;
        injector = HookInjector(sendAddr, 15, &hookSend);
        injector.inject();
    }
    else {
        /*DBG*/
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        initPipe();
        initHooks();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}