#include "JsEnv.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "Win.h"
#include "Global.h"


static JsEnv* env;
JSContext* ctx;
JSRuntime* rt;

static JSContext* JS_NewCustomContext(JSRuntime* rt)
{
    JSContext* ctx = JS_NewContext(rt);
    if (!ctx)
        return NULL;
    return ctx;
}

JsEnv::JsEnv()
{
    rt = JS_NewRuntime();
    if (!rt) {
        fprintf(stderr, "Failed to create runtime\n");
        return;
    }
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(rt);
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    ctx = JS_NewCustomContext(rt);
    if (!ctx) {
        fprintf(stderr, "Failed to create context\n");
        JS_FreeRuntime(rt);
        return;
    }

    Global::Reg(ctx);
    Win::Reg(ctx);
    LoadIndexJs(ctx);
    js_std_loop(ctx);
}

void JsEnv::Dispose()
{
    Win::Dispose();
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    delete env;
}

JsEnv::~JsEnv()
{  
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

void JsEnv::LoadIndexJs(JSContext* ctx)
{
    uint8_t* buf;
    size_t buf_len;
    buf = js_load_file(ctx, &buf_len, "main.js");
    if (!buf) {
        int a = 1;
        //load js error
    }
    JSValue val;
    char* buf1 = reinterpret_cast<char*>(const_cast<uint8_t*>(buf));
    val = JS_Eval(ctx, buf1, buf_len, "main.js", JS_EVAL_TYPE_MODULE);
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        return;
    }
    JS_FreeValue(ctx, val);
    js_free(ctx, buf);
}

int JsEnv::RegModel(JSContext* ctx, JSModuleDef* m)
{
    Win::Reg(ctx);
    return 0;
}