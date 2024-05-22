#include "Win.h"
#include "Util.h"
#include <vector>
#include "cutils.h"
#include "JsEnv.h"
#include <map>
#include <functional>

namespace Win {
static JSClassID id{ 0 };
std::vector<size_t> winIds;
std::map<size_t, JSValue> callBacks;

static JSClassDef js_win_class = {
	.class_name{"Win"}, // 类名
	.finalizer{[](JSRuntime* rt, JSValue val) {
		auto winId = *(size_t*)JS_GetOpaque(val, id);
		auto ctx = JsEnv::GetContext();
		for (const auto& [key, value] : callBacks) {
			JS_FreeValue(ctx, value);
			callBacks.erase(key);
		}
		//callBacks.clear();
		//webui_destroy(winId);
		//winIds.erase(std::remove(winIds.begin(), winIds.end(), winId), winIds.end());
		//todo js_free_rt已经帮我释放了资源，所以不能再delete win了
		//如果win持有其它指针，得在这里写delete释放
		//js_free_rt(rt, win);
		//JS_FreeValue(JsEnv::GetContext(), val);
	}}
};

JSValue close(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	webui_close(winId);
	winIds.erase(std::remove(winIds.begin(), winIds.end(), winId), winIds.end());
	return JS_NewBool(ctx, true);
}

JSValue setRootFolder(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {	
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
		webui_set_root_folder(winId, str);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue show(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {	
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
		webui_show(winId, str);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue hide(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
		webui_set_hide(winId, true);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue setSize(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	
	unsigned int w, h;
	if (JS_ToUint32(ctx, &w, argv[0])){
		return MakeVal(0, JS_TAG_EXCEPTION);
	}
	if (JS_ToUint32(ctx, &h, argv[1])) {
		return MakeVal(0, JS_TAG_EXCEPTION);
	}
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	webui_set_size(winId, w,h);
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue setPosition(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {

	unsigned int x, y;
	if (JS_ToUint32(ctx, &x, argv[0])) {
		return MakeVal(0, JS_TAG_EXCEPTION);
	}
	if (JS_ToUint32(ctx, &y, argv[1])) {
		return MakeVal(0, JS_TAG_EXCEPTION);
	}
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	webui_set_position(winId, x, y);
	return MakeVal(0, JS_TAG_UNDEFINED);
}


JSValue navigate(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
		webui_navigate(winId, str);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue run(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* str = JS_ToCString(ctx, argv[0]);
	if (str) {
		auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
		webui_run(winId, str);
		JS_FreeCString(ctx, str);
	}
	return MakeVal(0, JS_TAG_UNDEFINED);
}
JSValue bind(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv) {
	const char* eleId = JS_ToCString(ctx, argv[0]);
	if (!eleId) {
		return JS_ThrowTypeError(ctx, "arg 0 error");
	}
	if (!JS_IsFunction(ctx, argv[1])) {
		return JS_ThrowTypeError(ctx, "arg 1 error");
	}	
	auto winId = *(size_t*)JS_GetOpaque(thisVal, id);
	auto bindId = webui_bind(winId, eleId, [](webui_event_t* e) {
		auto ctx = JsEnv::GetContext();
		JSValue ret = JS_Call(ctx, callBacks[e->bind_id], MakeVal(0, JS_TAG_UNDEFINED), 0, NULL);
		if (JS_IsException(ret)) {
			js_std_dump_error(ctx);
		}			
		JS_FreeValue(ctx, ret);
	});
	callBacks.insert({ bindId,JS_DupValue(ctx, argv[1]) });
	JS_FreeCString(ctx, eleId);
	return MakeVal(0, JS_TAG_UNDEFINED);
}

JSValue Constructor(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
	JSValue obj = JS_NewObjectClass(ctx, id);
	auto winId = webui_new_window();
	winIds.push_back(winId);
	JS_SetOpaque(obj, (void*)&winIds.back());
	return obj;
}

void Reg(JSContext* ctx)
{
	auto rt = JS_GetRuntime(ctx);
	JS_NewClassID(rt,&id);
	JS_NewClass(rt, id, &js_win_class);
	JSValue protoInstance = JS_NewObject(ctx);
	JS_SetPropertyStr(ctx, protoInstance, "show", JS_NewCFunction(ctx, show, "show", 1));
	JS_SetPropertyStr(ctx, protoInstance, "hide", JS_NewCFunction(ctx, hide, "hide", 0));
	JS_SetPropertyStr(ctx, protoInstance, "setSize", JS_NewCFunction(ctx, setSize, "setSize", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setPosition", JS_NewCFunction(ctx, setPosition, "setPosition", 2));
	JS_SetPropertyStr(ctx, protoInstance, "setRootFolder", JS_NewCFunction(ctx, setRootFolder, "setRootFolder", 1));
	JS_SetPropertyStr(ctx, protoInstance, "navigate", JS_NewCFunction(ctx, navigate, "navigate", 1));
	JS_SetPropertyStr(ctx, protoInstance, "close", JS_NewCFunction(ctx, close, "close", 0));
	JS_SetPropertyStr(ctx, protoInstance, "run", JS_NewCFunction(ctx, run, "run", 1));
	JS_SetPropertyStr(ctx, protoInstance, "bind", JS_NewCFunction(ctx, bind, "bind", 2));
	JSValue ctroInstance = JS_NewCFunction2(ctx, &Win::Constructor, js_win_class.class_name, 0, JS_CFUNC_constructor,0);
	JS_SetConstructor(ctx, ctroInstance, protoInstance);
	JS_SetClassProto(ctx, id, protoInstance);

	JSValue global = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, global, js_win_class.class_name, ctroInstance);
	JS_FreeValue(ctx, global);
}
void Dispose() {
	for (const auto& [key, value] : callBacks) {
		JS_FreeValue(JsEnv::GetContext(), value);
	}
	callBacks.clear();
	winIds.clear();
}
}
