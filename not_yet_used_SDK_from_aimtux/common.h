#pragma once
#include <cstring>



    template <typename T>
T GetSymbolAddress(const char* filename, const char* symbol)
{
    void* handle = dlopen(filename, RTLD_NOW);
    T result = reinterpret_cast<T>(dlsym(handle, symbol));
    dlclose(handle);

    return result;
};
