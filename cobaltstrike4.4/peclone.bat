@echo off
java -Dfile.encoding=UTF-8 -XX:ParallelGCThreads=4 -XX:+UseParallelGC -javaagent:hook.jar -classpath ./cobaltstrike.jar pe.PEParser %*