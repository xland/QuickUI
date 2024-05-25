#include "Util.h"

#ifdef DEBUG
#include <iostream>
#include <fcntl.h>
#include <Windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
void InitDebuger() {
    //AttachConsole(ATTACH_PARENT_PROCESS) == TRUE;
    //AllocConsole();
    //auto std_handle = (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
    //auto con_handle = _open_osfhandle(std_handle, _O_TEXT);
    //auto fp = _fdopen(con_handle, "w");
    //freopen_s(&fp, "CONOUT$", "w", stdout);
    //std_handle = (intptr_t)GetStdHandle(STD_ERROR_HANDLE);
    //con_handle = _open_osfhandle(std_handle, _O_TEXT);
    //fp = _fdopen(con_handle, "w");
    //freopen_s(&fp, "CONOUT$", "w", stderr);
    if (!::AttachConsole(ATTACH_PARENT_PROCESS) && ::IsDebuggerPresent()) {
        if (::AllocConsole()) {
            FILE* unused;
            if (freopen_s(&unused, "CONOUT$", "w", stdout)) {
                _dup2(_fileno(stdout), 1);
            }
            if (freopen_s(&unused, "CONOUT$", "w", stderr)) {
                _dup2(_fileno(stdout), 2);
            }
            std::ios::sync_with_stdio();
        }
    }
}
#endif

JSContext* JsNewCustomContext(JSRuntime* rt)
{
    JSContext* ctx = JS_NewContext(rt);
    if (!ctx) {
        fprintf(stderr, "Failed to create context\n");
        JS_FreeRuntime(rt);
        return nullptr;
    }
    return ctx;
}