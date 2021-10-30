@echo off
java -XX:ParallelGCThreads=4 -XX:+AggressiveHeap -XX:+UseParallelGC -Xmx1024M -javaagent:hook.jar -jar cobaltstrike.jar $*
