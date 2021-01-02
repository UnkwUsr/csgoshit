#include <dlfcn.h>
#include <stdint.h>
#include <cstring>
#include "interfaces.h"

IBaseClientDLL* client;
ICvar* cvar;
IClientEntityList* entityList;
IEngineClient* engine;
IEngineTrace* trace;
CGlobalVars* globalVars;
IVModelInfo* modelInfo;
IVModelRender* modelRender;
IMaterialSystem* materialSystem;

    template <typename interface>
interface* GetInterface(const char* filename, const char* version, bool exact = false)
{
    void* lib_ptr = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);

    if (!lib_ptr)
        return nullptr;

    void* interfaces_sym = dlsym(lib_ptr, "s_pInterfaceRegs");

    /* if (!interfaces_sym) */
    /* { */
    /* 	dlclose(lib_ptr); */
    /* 	return nullptr; */
    /* } */

    dlclose(lib_ptr);

    InterfaceReg* interfaces = *reinterpret_cast<InterfaceReg**>(interfaces_sym);

    for (InterfaceReg* cur_interface = interfaces; cur_interface; cur_interface = cur_interface->m_pNext)
    {
        if (exact)
        {
            if (strcmp(cur_interface->m_pName, version) == 0)
                return reinterpret_cast<interface*>(cur_interface->m_CreateFn());
        }
        else
        {
            if (strstr(cur_interface->m_pName, version) && strlen(cur_interface->m_pName) - 3 == strlen(version))
                return reinterpret_cast<interface*>(cur_interface->m_CreateFn());
        }
    }

    return nullptr;
}


void findInterfaces() {
    client = GetInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
    engine = GetInterface<IEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");
    entityList = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", "VClientEntityList");
    cvar = GetInterface<ICvar>("./bin/linux64/materialsystem_client.so", "VEngineCvar");
    trace = GetInterface<IEngineTrace>("./bin/linux64/engine_client.so", "EngineTraceClient");
    modelInfo = GetInterface<IVModelInfo>("./bin/linux64/engine_client.so", "VModelInfoClient");
    modelRender = GetInterface<IVModelRender>("./bin/linux64/engine_client.so", "VEngineModel");
    materialSystem = GetInterface<IMaterialSystem>("./bin/linux64/materialsystem_client.so", "VMaterialSystem");
}

