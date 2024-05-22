#pragma once
#include <webui.hpp>
extern "C" {
#include <quickjs.h>
}
namespace Win
{
	void Reg(JSContext* ctx);
	void Dispose();
};

