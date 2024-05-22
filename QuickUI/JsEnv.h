#pragma once

extern "C" {
#include <quickjs.h>
#include "quickjs-libc.h"
}

class JsEnv
{
public:
	static void Init();
	static void Dispose();
	static JsEnv* Get();
	static JSContext* GetContext();
	static int RegModel(JSContext* ctx, JSModuleDef* m);
	~JsEnv();
	static void LoadIndexJs(JSContext* ctx);

private:
	JsEnv();
};

