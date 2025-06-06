#include <iostream>
#include <cmath>
#include "DLL1.h"
int main()
{   //я пытался сделать с перегрузками но оказалось нельзя перегружать с отличием только в принимаемых типах данных, шаблоны тоже не помогли
    int a[3] = { 1, 2, 3 };
    int* b = a;
    std::cout << meanArifmeticInt(b, 3)<<'\n';
    std::cout << meanNumberInt(b, 3) << '\n';
    std::cout << meanQuadInt(b, 3) << '\n';
    std::cout << dispersionInt(b, 3) << '\n';
    float c[3] = { 1.2, 2.1, 3.3 };
    float* d = c;
    std::cout << meanArifmeticFloat(d, 3) <<"mA" << '\n';
    std::cout << meanNumberFloat(d, 3) << "mN" << '\n';
    std::cout << meanQuadFloat(d, 3) << "mQ" << '\n';
    std::cout << dispersionFloat(d, 3) << "D";
}