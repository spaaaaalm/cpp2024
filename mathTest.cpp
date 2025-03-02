#include "mathTest.h"
#include <iostream>
#include <algorithm>
#include <cmath>

double Math::mean(const std::vector<double>& data){
    double sum = 0;
    for (double tempValue : data) {
        sum += tempValue;
    }
    return sum/data.size();
}
double Math::median(std::vector<double> data) {
    int n = data.size();
    if (n == 0) return 0;

    std::sort(data.begin(), data.end());

    if (n % 2 == 0) {
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    } else {
        return data[n / 2];
    }
}
double Math::meanQuadro(const std::vector<double>& data) {
    double sumOfSquares = 0;
    for (double value : data) {
        sumOfSquares += value * value;
    }
    return data.empty() ? 0 : std::sqrt(sumOfSquares / data.size());
}
double Math::dispercer(const std::vector<double>& data) {
    double mean = Math::mean(data);
    double varianceSum = 0;
    for (double value : data) {
        varianceSum += (value - mean) * (value - mean);
    }
    return data.empty() ? 0 : varianceSum / data.size();
}