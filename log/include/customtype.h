#ifndef CUSTOMTYPE_H
#define CUSTOMTYPE_H

#include <cstdint>

#ifndef DLL_DECLARE
#define DLL_DECLARE __declspec(dllexport)
#else
#define DLL_DECLARE __declspec(dllimport)
#endif


typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef unsigned long int ulong;
typedef double float64;

#endif // CUSTOMTYPE_H