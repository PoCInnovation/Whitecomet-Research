@echo off
(cmake -G "MinGW Makefiles" . && mingw32-make  && echo Success, you now have a polymorphic file ! - PoC) || echo Failed
pause
