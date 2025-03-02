#pragma once
#include <vector>

namespace Math {
    double mean(const std::vector<double>& data);
    double median(std::vector<double> data);
    double meanQuadro(const std::vector<double>& data);
    double dispercer(const std::vector<double>& data);
}