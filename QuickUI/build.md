# 编译webui
## 准备
修改 Makefile.nmake

主要是下面这几行，让release版编译到release目录下去
```
release:
	@- mkdir dist\release >nul 2>&1
	@- cd $(MAKEDIR)/dist/release
```

## 编译
打开 cmd

执行此批处理：
```
C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat
```
在CMD中执行命令
```
nmake -f Makefile debug
nmake -f Makefile
```

# 编译QuickJs

cmake编译没问题；
include quickjs.h时，编译本项目时有问题：

```C++
- return JS_MKVAL(JS_TAG_INT, val);
+ return JSValue{
+     .u{ JSValueUnion{.int32 = val } }, .tag{ JS_TAG_INT }
+ };
```

这个问题要改三处

Quick默认是没有console对象的