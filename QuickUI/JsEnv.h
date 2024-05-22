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

private:
	static void loadIndexJs(JSContext* ctx);
	JsEnv();
};

