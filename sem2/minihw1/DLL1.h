#pragma once
#ifdef DLL1_EXPORTS
#define DLL1_API __declspec(dllexport)
#else
#define DLL1_API __declspec(dllimport)
#endif 

extern "C" DLL1_API float meanArifmeticInt(int* a, int len);

extern "C" DLL1_API int meanNumberInt(int* a, int len);

extern "C" DLL1_API float meanQuadInt(int* a, float len);

extern "C" DLL1_API float dispersionInt(int* a, float len);

extern "C" DLL1_API float meanArifmeticFloat(float* a, int len);

extern "C" DLL1_API float meanNumberFloat(float* a, int len);

extern "C" DLL1_API float meanQuadFloat(float* a, int len);

extern "C" DLL1_API float dispersionFloat(float* a, int len);