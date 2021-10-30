/*
 * Cobalt Strike Artifact Kit
 *
 * (c) 2013 Strategic Cyber LLC
 *
 * See http://www.advancedpentest.com/license
 *
 * This is a plain jane executable
 */

#include "windows.h"

void start(HINSTANCE handle);

int main(int argc, char * argv[]) {
	start(NULL);

	/* sleep so we don't exit */
	while (TRUE)
		Sleep(10000);

	return 0;
}
