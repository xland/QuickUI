#include "WebUI.h"
#include "Util.h"

namespace WebUI {
	JSValue exit(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		webui_exit();
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue clean(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		webui_clean();
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue wait(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		js_std_loop(ctx);
		webui_wait();
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue setTimeout(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		unsigned int second;
		if (JS_ToUint32(ctx, &second, argv[0])) {
			return MakeVal(0, JS_TAG_EXCEPTION);
		}
		webui_set_timeout(second);
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
	void WebUI::Reg(JSContext* ctx)
	{
		JSValue globalObj = JS_GetGlobalObject(ctx);
		JSValue webui = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, webui, "setDefaultRootFolder", JS_NewCFunction(ctx, setDefaultRootFolder, "setDefaultRootFolder", 1));
		JS_SetPropertyStr(ctx, webui, "exit", JS_NewCFunction(ctx, exit, "exit", 0));
		JS_SetPropertyStr(ctx, webui, "clean", JS_NewCFunction(ctx, clean, "clean", 0));
		JS_SetPropertyStr(ctx, webui, "wait", JS_NewCFunction(ctx, wait, "wait", 0));
		JS_SetPropertyStr(ctx, webui, "setTimeout", JS_NewCFunction(ctx, setTimeout, "setTimeout", 1));
		JS_SetPropertyStr(ctx, webui, "deleteAllProfiles", JS_NewCFunction(ctx, deleteAllProfiles, "deleteAllProfiles", 0));
		JS_SetPropertyStr(ctx, globalObj, "webui", webui);
		JS_FreeValue(ctx, globalObj);
	}
}