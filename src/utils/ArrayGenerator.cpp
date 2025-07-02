#include "ArrayGenerator.h"

namespace Utils {
    std::vector<int> ArrayGenerator::gerarArrayAleatorio(int size) {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, size * 10);
        for (int i = 0; i < size; ++i) {
            arr[i] = distrib(gen);
        }
        return arr;
    }

    std::vector<int> ArrayGenerator::gerarArrayQuaseOrdenado(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = i + 1;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, size - 1);
        for (int i = 0; i < size / 10; ++i) { // troca 10% dos elementos
            int idx1 = distrib(gen);
            int idx2 = distrib(gen);
            std::swap(arr[idx1], arr[idx2]);
        }
        return arr;
    }

    std::vector<int> ArrayGenerator::gerarArrayInversamenteOrdenado(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; ++i) {
            arr[i] = size - i;
        }
        return arr;
    }
}

