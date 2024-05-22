#pragma once

#include <webui.hpp>
extern "C" {
#include <quickjs.h>
}
namespace Global
{
	void Reg(JSContext* ctx);
};

