//
// Created by Kether on 03.11.2024.
//
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

bool schedule_example(void)
{
    HMODULE lib = LoadLibraryA("../lib/libmax.dll");
    if(NULL == lib) {
        fprintf(stderr, "Can't find library\n");
        return false;
    }


    void (*time_max)(void) = (void (*)(void))GetProcAddress(lib, "time_algorithm");
    if(NULL == time_max) {
        fprintf(stderr, "Can't find function\n");
        return false;
    }

    time_max();

    FreeLibrary(lib);
    return true;
}
