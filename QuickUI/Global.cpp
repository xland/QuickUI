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

	void Global::Reg(JSContext* ctx)
	{
		js_init_module_std(ctx, "std");
		js_std_add_helpers(ctx, 0, nullptr);
		js_init_module_os(ctx, "os");

		JSValue globalObj = JS_GetGlobalObject(ctx);
		JSValue consoleObj = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, consoleObj, "log", JS_NewCFunction(ctx, jsConsoleLog, "log", 1));
		JS_SetPropertyStr(ctx, globalObj, "console", consoleObj);
		JS_FreeValue(ctx, globalObj);
	}
}
