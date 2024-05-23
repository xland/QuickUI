#include "Global.h"
#include "Util.h"

extern "C" {
#include <quickjs.h>
#include "quickjs-libc.h"
}

namespace Global {

	JSValue jsConsoleLog(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		for (int i = 0; i < argc; i++) {
			const char* str = JS_ToCString(ctx, argv[i]);
			if (str) {
				printf("%s", str);
				JS_FreeCString(ctx, str);
			}
		}
		printf("\n");
		return MakeVal(0, JS_TAG_UNDEFINED);
	}

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

	void Global::Reg(JSContext* ctx)
	{
		auto rt = JS_GetRuntime(ctx);
		js_std_set_worker_new_context_func(JsNewCustomContext);
		js_std_init_handlers(rt);

		js_init_module_std(ctx, "std");
		js_init_module_os(ctx, "os");

		JSValue globalObj = JS_GetGlobalObject(ctx);
		JSValue console = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, jsConsoleLog, "log", 1));
		JS_SetPropertyStr(ctx, globalObj, "console", console);
		JS_FreeValue(ctx, globalObj);

		
	}
}
