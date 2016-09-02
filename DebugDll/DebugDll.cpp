// DebugDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DebugDll.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int r1 = test01(7, 8, 1);
	int r2 = test02(7, 3);
	printf_s("结果是：%d\n", r1);
	printf_s("结果是：%d\n", r2);
	getchar();
	return 0;
}

