Artifact Kit
------------
This package contains source code for Cobalt Strike's Artifact Kit. This kit is designed to ease the 
development of anti-virus safe artifacts.

Cobalt Strike uses artifacts from this kit to generate executables and DLLs that are safe from some
anti-virus products. Load the included artifacts.cna script to force Cobalt Strike to use your artifacts
over the built-in ones.

Cobalt Strike uses these artifacts in the following places:

	* Attacks -> Packages -> Windows Executable
	* Attacks -> Packages -> Windows Executable (S)
	* Attacks -> Web Drive-by -> Scripted Web Delivery (bitsadmin and exe)
	* Beacon's 'elevate svc-exe' command
	* Beacon's 'jump psexec' and 'jump psexec64' commands

How it Works
------------
Most anti-virus products use signatures to detect known malware. To defeat packers and crypters these
products use a virtual machine sandbox to step-through a binary and check each step against the database
of known signatures. The A/V sandboxes do not emulate all possible things a program can do. Artifact Kit 
binaries force shellcode through a process that many A/V engines can not emulate. This causes the A/V
engine to give up on processing the artifact.

dist-readfile/ (implemented in src-common/bypass-readfile.c):
	This bypass opens the current artifact file, skips to where the shellcode is stored,
	reads it, and decodes it. This is the default artifact kit loaded with Cobalt Strike.

dist-pipe/ (implemented in src-common/bypass-pipe.c)
	This bypass creates a named pipe to serve the obfuscated shellcode and a client to
	read it. Once the client reads the obfuscated shellcode it decodes it. 

Recompile
---------
To recompile everything:

$ ./build.sh

You will need the following:

- Minimal GNU for Windows Cross-Compiler - apt-get install mingw-w64

HOWTO - Add a New Bypass
-----
1. Create a file in src-common/, name it bypass-[your technique here].c
2. Open build.sh and add a line for your technique at the bottom

Integration
-----------
To use your new Artifact Kit, load artifact.cna into Cobalt Strike. Each variant of the
Artifact Kit lives in its own folder. The artifact.cna script contains a Cortana filter to
tell Cobalt Strike to use your Artifact Kit over the built-in option.

Go to Cobalt Strike -> Scripts, press Load.

Modifications
-------------
You're encouraged to make modifications to this code and use these modifications in your
engagements. Do not redistribute this source code. It is not open source. It is provided as a 
benefit to licensed Cobalt Strike users.

License
-------
This code is subject to the end user license agreement for Cobalt Strike. The complete
license agreement is at:

https://www.cobaltstrike.com/license
