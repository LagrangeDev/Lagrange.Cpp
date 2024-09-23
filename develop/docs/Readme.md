# 开发
## 基础开发环境 - 编译必须
（可选不同） Vscode + Cmake + MsvcX64 + Vcpkg

## 条件编译定义添加 - 非编译必须
需要添加分析文件时 IntelliSense 引擎要使用的预处理器定义的列表

```
_WIN_PLATFORM_
_DARWIN_PLATFORM_
_LINUX_PLATFORM_
```