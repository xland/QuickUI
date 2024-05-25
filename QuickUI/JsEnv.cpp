#include "JsEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "Win.h"
#include "Global.h"
#include "WebUI.h"
#include "Util.h"


static JsEnv* env;
JSContext* ctx;
JSRuntime* rt;

JsEnv::JsEnv()
{
    rt = JS_NewRuntime();
    if (!rt) {
        fprintf(stderr, "Failed to create runtime\n");
        return;
    }
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
    ctx = JsNewCustomContext(rt);
    Global::Reg(ctx);
    WebUI::Reg(ctx);
    Win::Reg(ctx);
    loadIndexJs(ctx);
    
}

void JsEnv::Dispose()
{
    Win::Dispose(rt);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    delete env;
}

void JsEnv::Init()
{
    env = new JsEnv();
}

JsEnv* JsEnv::Get()
{
    return env;
}


JSContext* JsEnv::GetContext()
{
    return ctx;
}

void JsEnv::loadIndexJs(JSContext* ctx)
{
    auto mainFilePath = "main.js";
    size_t bufLen;
    uint8_t* buf = js_load_file(ctx, &bufLen, mainFilePath);
    if (!buf) {
        perror("load file error:");
        perror(mainFilePath);
    }
    char* bufStr = reinterpret_cast<char*>(const_cast<uint8_t*>(buf));
    JSValue val = JS_Eval(ctx, bufStr, bufLen, mainFilePath, JS_EVAL_TYPE_MODULE);
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        return;
    }
    JS_FreeValue(ctx, val);
    js_free(ctx, buf);
}