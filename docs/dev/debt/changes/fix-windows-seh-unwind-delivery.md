# libc

## change [exception unwinder]

- The Windows libc [exception unwinder](../../../core/libs/prx/libc/src/exception/Unwind.cpp) cannot run arbitrary Windows exception or termination handlers. It accepts GCC C and C++ handlers identified by a project's `.sehgcc` section and interprets their LSDA with the guest personalities. 64-bit MinGW SEH builds retain `.pdata` function records so exceptions raised within `libstdc++-6.dll` (such as `regex_error` or `filesystem_error`) are delivered to project `catch` handlers without aborting. A handler in an unmarked module, such as a C++ cleanup through `__gxx_personality_seh0` in `libstdc++-6.dll` or a system DLL function like `qsort` in `ucrtbase.dll` (Windows 10 22H2), still stops unwinding and the exception is reported as unhandled. SjLj exceptions are unsupported; Scoop GCC 15.2.0 selects them when SEH is disabled and lacks the System V ABI SEH compiler fix carried by MSYS2.
