// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

/****************************************************************************************************************************

DllMain 简介

    系统是在什么时候调用DllMain函数的呢？静态链接时，或动态链接时调用LoadLibrary和FreeLibrary都会调用DllMain函数。DllMain的第
二个参数fdwReason指明了系统调用Dll的原因，它可能是:：

DLL_PROCESS_ATTACH、

DLL_PROCESS_DETACH、

DLL_THREAD_ATTACH、

DLL_THREAD_DETACH。

以下从这四种情况来分析系统何时调用了DllMain。

1.进程映射

DLL_PROCESS_ATTACH

    大家都知道，一个程序要调用Dll里的函数，首先要先把DLL文件映射到进程的地址空间。要把一个DLL文件映射到进程的地址空间，有两种
方法：静态链接和动态链接的LoadLibrary或者LoadLibraryEx。

    当一个DLL文件被映射到进程的地址空间时，系统调用该DLL的DllMain函数，传递的fdwReason参数为DLL_PROCESS_ATTACH，这种调用只会发
生在第一次映射时。如果同一个进程后来为已经映射进来的DLL再次调用LoadLibrary或者LoadLibraryEx，操作系统只会增加DLL的使用次数，它
不会再用DLL_PROCESS_ATTACH调用DLL的DllMain函数。不同进程用LoadLibrary同一个DLL时，每个进程的第一次映射都会用DLL_PROCESS_ATTACH
调用DLL的DllMain函数。

可参考DllMainTest的DLL_PROCESS_ATTACH_Test函数。


2.进程卸载

DLL_PROCESS_DETACH

    当DLL被从进程的地址空间解除映射时，系统调用了它的DllMain，传递的fdwReason值是DLL_PROCESS_DETACH。当DLL处理该值时，它应该
执行进程相关的清理工作。

那么什么时候DLL被从进程的地址空间解除映射呢？两种情况：
◆FreeLibrary解除DLL映射（有几个LoadLibrary，就要有几个FreeLibrary）
◆进程结束而解除DLL映射，在进程结束前还没有解除DLL的映射，进程结束后会解除DLL映射。（如果进程的终结是因为调用了TerminateProcess，
系统就不会用DLL_PROCESS_DETACH来调用DLL的DllMain函数。这就意味着DLL在进程结束前没有机会执行任何清理工作。）

注意：当用DLL_PROCESS_ATTACH调用DLL的DllMain函数时，如果返回FALSE，说明没有初始化成功，系统仍会用DLL_PROCESS_DETACH调用DLL的
DllMain函数。因此，必须确保清理那些没有成功初始化的东西。

可参考DllMainTest的DLL_PROCESS_DETACH_Test函数。

3.线程映射

DLL_THREAD_ATTACH

    当进程创建一线程时，系统查看当前映射到进程地址空间中的所有DLL文件映像，并用值DLL_THREAD_ATTACH调用DLL的DllMain函数。新创
建的线程负责执行这次的DLL的DllMain函数，只有当所有的DLL都处理完这一通知后，系统才允许进程开始执行它的线程函数。

注意: DLL_THREAD_ATTACH 跟 DLL_PROCESS_ATTACH 的区别，我们在前面说过，第n(n>=2)次以后地把DLL映像文件映射到进程的地址空间时，
是不再用DLL_PROCESS_ATTACH调用DllMain的。而DLL_THREAD_ATTACH不同，进程中的每次建立线程，都会用值DLL_THREAD_ATTACH调用DllMain
函数，哪怕是线程中建立线程也一样。


4.线程卸载

DLL_THREAD_DETACH

    如果线程调用了ExitThread来结束线程（线程函数返回时，系统也会自动调用ExitThread），系统查看当前映射到进程空间中的所有DLL
文件映像，并用DLL_THREAD_DETACH来调用DllMain函数，通知所有的DLL去执行线程级的清理工作。

注意：如果线程的结束是因为系统中的一个线程调用了TerminateThread，系统就不会用值DLL_THREAD_DETACH来调用所有DLL的DllMain函数。
****************************************************************************************************************************/




