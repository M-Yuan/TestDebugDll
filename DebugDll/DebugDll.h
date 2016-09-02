#pragma once

#pragma comment(lib, "../Debug/CreateDll.lib")
#pragma comment(lib, "../Release/CreateDll.lib")
extern "C" _declspec(dllimport) int __stdcall test01(int a, int b, int c);
extern "C" _declspec(dllimport) int __stdcall test02(int a, int b);
