#ifndef ARRAY_GENERATOR_H
#define ARRAY_GENERATOR_H

#include <vector>
#include <random>
#include <algorithm>

namespace Utils {
    class ArrayGenerator {
    public:
        static std::vector<int> gerarArrayAleatorio(int size);
        static std::vector<int> gerarArrayQuaseOrdenado(int size);
        static std::vector<int> gerarArrayInversamenteOrdenado(int size);
    };
}

#endif // ARRAY_GENERATOR_H

