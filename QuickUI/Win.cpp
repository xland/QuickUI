﻿#include "Win.h"
#include "Util.h"
#include <vector>
#include "cutils.h"
#include "JsEnv.h"
#include <map>
#include <functional>

namespace Win {
static JSClassID id{ 0 };
static std::map<size_t, JSValue> wins;

static unsigned int getWinId(JSContext* ctx, JSValueConst thisVal) {
	
	JSValue prop = JS_GetPropertyStr(ctx, thisVal, "id");
	unsigned int id;
	JS_ToUint32(ctx, &id, prop);
	JS_FreeValue(ctx, prop);
	return id;
}

static JSClassDef js_win_class = {
	.class_name{"Win"}, // 类名
	.finalizer{[](JSRuntime* rt, JSValue val) { } }
};



JSValue close(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
#ifdef DEBUG
	return JS_NewBool(ctx, false);
#endif
	auto winId = getWinId(ctx, thisVal);
	wins.erase(winId);
	webui_close(winId);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue destroy(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
#ifdef DEBUG
	return JS_NewBool(ctx, false);
#endif
	auto winId = getWinId(ctx, thisVal);
	wins.erase(winId);
	webui_destroy(winId);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue setRootFolder(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {	
	const char* str = JS_ToCString(ctx, argv[0]);
	if (!str) {
		return JS_ThrowTypeError(ctx, "arg error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_set_root_folder(winId, str);
	JS_FreeCString(ctx, str);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue show(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {	
	const char* str = JS_ToCString(ctx, argv[0]);
	if (!str) {
		return JS_ThrowTypeError(ctx, "arg error");
	}
	auto winId = getWinId(ctx,thisVal);
	webui_show(winId, str);
	JS_FreeCString(ctx, str);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue setProxy(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* server = JS_ToCString(ctx, argv[0]);
	if (!server) {
		return JS_ThrowTypeError(ctx, "arg error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_set_proxy(winId, server);
	JS_FreeCString(ctx, server);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue showBrowser(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* str = JS_ToCString(ctx, argv[0]);
	if (!str) {
		return JS_ThrowTypeError(ctx, "arg0 error");
	}
	unsigned int browserId;
	if (JS_ToUint32(ctx, &browserId, argv[1])) {
		JS_FreeCString(ctx, str);
		return JS_ThrowTypeError(ctx, "arg1 error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_show_browser(winId, str, browserId);
	JS_FreeCString(ctx, str);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

//JSValue hide(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
//	const char* str = JS_ToCString(ctx, argv[0]);
//	if (str) {
//		auto winId = getWinId(ctx, thisVal);
//		webui_set_hide(winId, true);
//		JS_FreeCString(ctx, str);
//	}
//	return MakeVal(0, JS_TAG_UNDEFINED);
//}
JSValue setKiosk(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	bool state = JS_ToBool(ctx, argv[0]);
	auto winId = getWinId(ctx, thisVal);
	webui_set_kiosk(winId, state);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue setPublic(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	bool state = JS_ToBool(ctx, argv[0]);
	auto winId = getWinId(ctx, thisVal);
	webui_set_public(winId, state);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue getUrl(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	auto winId = getWinId(ctx, thisVal);
	const char* ret = webui_get_url(winId);
	JSValue jsVal = JS_NewString(ctx, ret);
	return jsVal;
}

JSValue setSize(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {	
	unsigned int w, h;
	if (JS_ToUint32(ctx, &w, argv[0])){
		return JS_ThrowTypeError(ctx, "arg0 error");
	}
	if (JS_ToUint32(ctx, &h, argv[1])) {
		return JS_ThrowTypeError(ctx, "arg1 error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_set_size(winId, w,h);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue setIcon(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* icon = JS_ToCString(ctx, argv[0]);
	if (!icon) {
		return JS_ThrowTypeError(ctx, "arg0 error");
	}
	const char* iconType = JS_ToCString(ctx, argv[1]);
	if (!iconType) {
		JS_FreeCString(ctx, icon);
		return JS_ThrowTypeError(ctx, "arg1 error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_set_icon(winId, icon, iconType);
	JS_FreeCString(ctx, icon);
	JS_FreeCString(ctx, iconType);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue setProfile(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* name = JS_ToCString(ctx, argv[0]);
	if (!name) {
		return JS_ThrowTypeError(ctx, "arg0 error");
	}
	const char* path = JS_ToCString(ctx, argv[1]);
	if (!path) {
		JS_FreeCString(ctx, path);
		return JS_ThrowTypeError(ctx, "arg1 error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_set_profile(winId, name, path);
	JS_FreeCString(ctx, name);
	JS_FreeCString(ctx, path);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue setPosition(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	unsigned int x, y;
	if (JS_ToUint32(ctx, &x, argv[0])) {
		return JS_ThrowTypeError(ctx, "arg0 error");
	}
	if (JS_ToUint32(ctx, &y, argv[1])) {
		return JS_ThrowTypeError(ctx, "arg1 error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_set_position(winId, x, y);
	return MakeVal(0, JS_TAG_UNDEFINED);
}


JSValue navigate(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* str = JS_ToCString(ctx, argv[0]);
	if (!str) {
		return JS_ThrowTypeError(ctx, "arg error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_navigate(winId, str);
	JS_FreeCString(ctx, str);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue run(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* str = JS_ToCString(ctx, argv[0]);
	if (!str) {
		return JS_ThrowTypeError(ctx, "arg error");
	}
	auto winId = getWinId(ctx, thisVal);
	webui_run(winId, str);
	JS_FreeCString(ctx, str);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue bind(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* eleId = JS_ToCString(ctx, argv[0]);
	if (!eleId) {
		return JS_ThrowTypeError(ctx, "arg0 error");
	}
	if (!JS_IsFunction(ctx, argv[1])) {
		return JS_ThrowTypeError(ctx, "arg1 error");
	}	
	auto winId = getWinId(ctx, thisVal);
	auto bindId = webui_bind(winId, eleId, [](webui_event_t* e) {
		auto ctx = JsEnv::GetContext();
		JSValue arg = JS_NewObject(ctx);
		JS_SetPropertyStr(ctx, arg, "windowId", JS_NewUint32(ctx,e->window));
		JS_SetPropertyStr(ctx, arg, "eventType", JS_NewUint32(ctx, e->event_type));
		JS_SetPropertyStr(ctx, arg, "elementId", JS_NewString(ctx, e->element));
		JS_SetPropertyStr(ctx, arg, "eventNumber", JS_NewUint32(ctx, e->event_number));
		JS_SetPropertyStr(ctx, arg, "bindId", JS_NewUint32(ctx, e->bind_id));
		JSValue cbs = JS_GetPropertyStr(ctx, wins[e->window], "__cbs");
		auto cb = JS_GetPropertyUint32(ctx, cbs, e->bind_id);
		JSValue ret = JS_Call(ctx, cb, MakeVal(0, JS_TAG_UNDEFINED), 1, &arg);
		if (JS_IsException(ret)) {
			js_std_dump_error(ctx);
		}
		JS_FreeValue(ctx, cbs);
		JS_FreeValue(ctx, cb);
		JS_FreeValue(ctx, arg);
		JS_FreeValue(ctx, ret);
	});
	JSValue cbs = JS_GetPropertyStr(ctx, thisVal, "__cbs");
	JS_SetPropertyUint32(ctx, cbs, bindId, JS_DupValue(ctx, argv[1]));
	JS_FreeValue(ctx, cbs);
	JS_FreeCString(ctx, eleId);

	JSValue ret = JS_NewUint32(ctx, bindId);
	return ret;
}

JSValue Constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, id);
	auto winId = webui_new_window();
	JS_SetPropertyStr(ctx, obj, "id", JS_NewUint32(ctx,winId));
	JS_SetPropertyStr(ctx, obj, "__cbs", JS_NewArray(ctx));
	wins.insert({ winId,obj });
	return obj;
}

void Reg(JSContext* ctx)
{
	auto rt = JS_GetRuntime(ctx);
	JS_NewClassID(rt,&id);
	JS_NewClass(rt, id, &js_win_class);
	JSValue protoInstance = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, protoInstance, "show", JS_NewCFunction(ctx, show, "show", 1));
	JS_SetPropertyStr(ctx, protoInstance, "showBrowser", JS_NewCFunction(ctx, showBrowser, "showBrowser", 2));
	//JS_SetPropertyStr(ctx, protoInstance, "hide", JS_NewCFunction(ctx, hide, "hide", 0));
	JS_SetPropertyStr(ctx, protoInstance, "setKiosk", JS_NewCFunction(ctx, setKiosk, "setKiosk", 1));
	JS_SetPropertyStr(ctx, protoInstance, "setPublic", JS_NewCFunction(ctx, setPublic, "setPublic", 1));
	JS_SetPropertyStr(ctx, protoInstance, "getUrl", JS_NewCFunction(ctx, getUrl, "getUrl", 0));
	JS_SetPropertyStr(ctx, protoInstance, "setSize", JS_NewCFunction(ctx, setSize, "setSize", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setIcon", JS_NewCFunction(ctx, setIcon, "setIcon", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setProfile", JS_NewCFunction(ctx, setProfile, "setProfile", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setProxy", JS_NewCFunction(ctx, setProxy, "setProxy", 1));
	JS_SetPropertyStr(ctx, protoInstance, "setPosition", JS_NewCFunction(ctx, setPosition, "setPosition", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setRootFolder", JS_NewCFunction(ctx, setRootFolder, "setRootFolder", 1));
	JS_SetPropertyStr(ctx, protoInstance, "navigate", JS_NewCFunction(ctx, navigate, "navigate", 1));
	JS_SetPropertyStr(ctx, protoInstance, "close", JS_NewCFunction(ctx, close, "close", 0));
	JS_SetPropertyStr(ctx, protoInstance, "destroy", JS_NewCFunction(ctx, destroy, "destroy", 0));
	JS_SetPropertyStr(ctx, protoInstance, "run", JS_NewCFunction(ctx, run, "run", 1));
	JS_SetPropertyStr(ctx, protoInstance, "bind", JS_NewCFunction(ctx, bind, "bind", 2));
	JSValue ctroInstance = JS_NewCFunction2(ctx, &Win::Constructor, js_win_class.class_name, 0, JS_CFUNC_constructor,0);
	JS_SetConstructor(ctx, ctroInstance, protoInstance);
	JS_SetClassProto(ctx, id, protoInstance);

	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, js_win_class.class_name, ctroInstance);
	JS_FreeValue(ctx, global);
}
void Dispose(JSRuntime* rt) {
	wins.clear();
}
}
