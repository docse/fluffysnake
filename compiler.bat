@echo off
title [Fluffysnake1]Compiler

if not exist "o\" mkdir o\
:recompile
echo Starting compiling...

echo =============================
echo [MAIN]
g++ src/main.cpp -c
g++ *.o -o Fluffysnake1
move *.o o >NUL
echo DONE....
echo ==============================

echo Press any key to recompile...
pause >NUL
goto recompile
