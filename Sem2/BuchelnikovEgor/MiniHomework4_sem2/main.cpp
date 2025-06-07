#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> words = { "Plus", "ad#$asda@d8", "lambda", "cpp" };
    std::vector<int> lengths;

    for (const auto& word : words) {
        lengths.push_back(static_cast<int>(word.length()));
    }

    for (int len : lengths) {
        std::cout << len << " ";
    }

    return 0;
}