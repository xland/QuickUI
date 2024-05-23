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

	JSValue exit(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		webui_exit();
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue clean(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		webui_clean();
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue deleteAllProfiles(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		webui_delete_all_profiles();
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue setDefaultRootFolder(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
		const char* str = JS_ToCString(ctx, argv[0]);
		if (str) {
			webui_set_default_root_folder(str);
			JS_FreeCString(ctx, str);
		}
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
		JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

		js_init_module_std(ctx, "std");
		js_init_module_os(ctx, "os");

		JSValue globalObj = JS_GetGlobalObject(ctx);
		JSValue console = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, jsConsoleLog, "log", 1));
		JS_SetPropertyStr(ctx, globalObj, "console", console);

		JSValue webui = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, webui, "setDefaultRootFolder", JS_NewCFunction(ctx, setDefaultRootFolder, "setDefaultRootFolder", 1));
		JS_SetPropertyStr(ctx, webui, "exit", JS_NewCFunction(ctx, exit, "exit", 0));
		JS_SetPropertyStr(ctx, webui, "clean", JS_NewCFunction(ctx, clean, "clean", 0));
		JS_SetPropertyStr(ctx, webui, "deleteAllProfiles", JS_NewCFunction(ctx, deleteAllProfiles, "deleteAllProfiles", 0));
		JS_SetPropertyStr(ctx, globalObj, "webui", webui);
		
		JS_FreeValue(ctx, globalObj);

		js_std_loop(ctx);
	}
}
