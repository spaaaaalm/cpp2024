#include "mathTest.h"
#include <vector>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    std::vector<double> values = {1.0, 2.0, 3.0, 44.99, 0.123, 7.222};
    double avg = Math::mean(values); 
    std::cout << "Подсчет среднего арифметического = "<< avg<<std::endl;
    double avg1 = Math::median(values);
    std::cout << "Подсчет медианы = "<< avg1<<std::endl;
    double avg2 = Math::meanQuadro(values);
    std::cout << "Подсчет среднего квадратического = "<< avg2<<std::endl;
    double avg3 = Math::dispercer(values); 
    std::cout << "Подсчет дисперсии числового ряда = "<< avg3<<std::endl;
}