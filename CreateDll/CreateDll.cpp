// CreateDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "CreateDll.h"


int __stdcall test01(int a, int b, int c)
{
	return a+b+c;
}

int __stdcall test02(int a, int b)
{
	return a-b;
}


