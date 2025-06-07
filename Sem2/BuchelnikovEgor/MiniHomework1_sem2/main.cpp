#include "MathLibrary.h"
#include <vector>
#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");
    std::vector<double> values = {1.0, 2.0, 3.0, 44.99, 0.123, 7.222};
    double avg = Math::mean(values); 
    std::cout << "Mean value = "<< avg<<std::endl;
    double avg1 = Math::median(values);
    std::cout << "Median value = "<< avg1<<std::endl;
    double avg2 = Math::meanQuadro(values);
    std::cout << "Mean qube value = "<< avg2<<std::endl;
    double avg3 = Math::dispercer(values); 
    std::cout << "Variance of a numerical series value = "<< avg3<<std::endl;
}