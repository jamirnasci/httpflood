@echo off
cls
mkdir bin
gcc main.c -o bin\httpflood -l ws2_32
bin\httpflood.exe
