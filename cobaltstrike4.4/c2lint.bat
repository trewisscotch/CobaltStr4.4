@echo off

java -XX:ParallelGCThreads=4 -XX:+UseParallelGC -javaagent:hook.jar -classpath ./cobaltstrike.jar c2profile.Lint %*
