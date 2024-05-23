#pragma once
extern "C" {
#include <webui.h>
#include <quickjs.h>
#include <quickjs-libc.h>
}

namespace WebUI
{
	void Reg(JSContext* ctx);
};

