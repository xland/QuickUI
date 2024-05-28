#include "Clipboard.h"
#include "Util.h"

namespace Clipboard {

	JSValue readText(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue writeText(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue readHTML(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue writeHTML(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue readImage(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue writeImage(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}
	JSValue clear(JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
		return MakeVal(0, JS_TAG_UNDEFINED);
	}

	void Clipboard::Reg(JSContext* ctx)
	{
		auto rt = JS_GetRuntime(ctx);

		JSValue globalObj = JS_GetGlobalObject(ctx);
		JSValue clipboard = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, clipboard, "readText", JS_NewCFunction(ctx, readText, "log", 1));
		JS_SetPropertyStr(ctx, clipboard, "writeText", JS_NewCFunction(ctx, writeText, "warn", 1));
		JS_SetPropertyStr(ctx, clipboard, "readHTML", JS_NewCFunction(ctx, readHTML, "info", 1));
		JS_SetPropertyStr(ctx, clipboard, "writeHTML", JS_NewCFunction(ctx, writeHTML, "error", 1));

		JS_SetPropertyStr(ctx, clipboard, "readImage", JS_NewCFunction(ctx, readImage, "log", 1));
		JS_SetPropertyStr(ctx, clipboard, "writeImage", JS_NewCFunction(ctx, writeImage, "warn", 1));
		JS_SetPropertyStr(ctx, clipboard, "clear", JS_NewCFunction(ctx, clear, "info", 1));

		JS_SetPropertyStr(ctx, globalObj, "clipboard", clipboard);
		JS_FreeValue(ctx, globalObj);
	}
}