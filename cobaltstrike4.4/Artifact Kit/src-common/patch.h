/*
 * Artifact Kit - A means to disguise and inject our payloads... *pHEAR*
 * (c) 2014 Strategic Cyber LLC
 *
 * See http://www.advancedpentest.com/license
 *
 * Shared code to accept a binary patch in a way that's compatible with
 * the Cortana script artifact.cna.
 *
 * If you choose to modify the patching process--you will need to modify
 * this file and recompile the artifact kit.
 */

void spawn(void * buffer, int length, char * key);

typedef struct {
	int  offset;
	int  length;
	char key[4];
	int  gmh_offset;
	int  gpa_offset;
	char payload[DATA_SIZE];
} phear;

extern char data[DATA_SIZE];
