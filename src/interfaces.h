#include "sdk.h"

extern ICvar* cvar;
extern IBaseClientDLL* client;
extern IClientEntityList* entityList;
extern IEngineClient* engine;
extern IEngineTrace* trace;
extern CGlobalVars* globalVars;
extern IVModelInfo* modelInfo;
extern IVModelRender* modelRender;
extern IMaterialSystem* materialSystem;


typedef KeyValues* (*KeyValuesFromStringFn) (char const *szName, char const *szStringVal, char const **ppEndOfParse);
extern KeyValuesFromStringFn KeyValuesFromString;

void findInterfaces();

typedef void* (*InstantiateInterfaceFn) ();

struct InterfaceReg
{
    InstantiateInterfaceFn m_CreateFn;
    const char *m_pName;
    InterfaceReg *m_pNext;
};

