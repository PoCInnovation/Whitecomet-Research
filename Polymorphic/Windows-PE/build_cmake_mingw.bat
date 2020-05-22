@echo off
cmake -G"MinGW Makefiles" . && mingw32-make  && echo [35mSuccess, you now have a polymorphic file ![0m - [36mPoC[0m
pause