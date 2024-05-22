#pragma once
extern "C" {
#include <quickjs.h>
}

#ifdef DEBUG
void InitDebuger();
#endif

constexpr JSCFunctionListEntry MakeJsFunc(const char* name, uint8_t length, JSCFunction* func) {
    return JSCFunctionListEntry{
        .name{name},
        .prop_flags{ JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE },
        .def_type{JS_DEF_CFUNC},
        .magic{0},
        .u = {
            .func{
                .length{length},
                .cproto{JS_CFUNC_generic},
                .cfunc{
                    .generic{func}
                }
            }
        }
    };
};
constexpr JSValue MakeVal(int32_t val, int64_t tag) {
    return { 
        .u{
            .int32{val}
        },
        .tag{tag}
    };
}
