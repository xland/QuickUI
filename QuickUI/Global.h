#pragma once

extern "C" {
#include <webui.h>
#include <quickjs.h>
}
namespace Global
{
	void Reg(JSContext* ctx);
	JSContext* JsNewCustomContext(JSRuntime* rt);
};

