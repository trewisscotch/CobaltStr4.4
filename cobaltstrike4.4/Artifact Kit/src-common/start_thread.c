/*
 * (c) 2017 Strategic Cyber LLC
 *
 * See https://www.cobaltstrike.com/license
 */
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/* We need a macro to set the architecture-appropriate register to make this work */
#ifdef _M_X64
#define SET_REG(ctx, value) ctx.Rcx = (DWORD64)value
#else
#define SET_REG(ctx, value) ctx.Eax = (DWORD)value
#endif

/* x86 -> x86, x64 -> x64 */
void start_thread(HANDLE hProcess, PROCESS_INFORMATION pi, LPVOID lpStartAddress) {
	CONTEXT ctx;

	/* try to query some information about our thread */
	ctx.ContextFlags = CONTEXT_INTEGER;
	if (!GetThreadContext(pi.hThread, &ctx))
		return;

	/* update the Eax value to our new start address */
	SET_REG(ctx, lpStartAddress);
	if (!SetThreadContext(pi.hThread, &ctx))
		return;

	/* kick off the thread, please */
	ResumeThread(pi.hThread);
}
