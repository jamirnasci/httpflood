@echo off
cls
gcc main.c -o bin\httpflood -l ws2_32
bin\httpflood.exe