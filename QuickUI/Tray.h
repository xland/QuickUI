#pragma once

extern "C" {
#include <webui.h>
#include <quickjs.h>
}
namespace Tray
{
	void Reg(JSContext* ctx);
};
