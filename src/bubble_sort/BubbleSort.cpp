#include "BubbleSort.h"

namespace Sort {
    void BubbleSort::sort(std::vector<int>& arr, long long& comparacoes, long long& trocas) {
        comparacoes = 0;
        trocas = 0;
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                comparacoes++;
                if (arr[j] > arr[j+1]) {
                    std::swap(arr[j], arr[j+1]);
                    trocas++;
                }
            }
        }
    }
}

