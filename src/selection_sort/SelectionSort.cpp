#include "SelectionSort.h"

namespace Sort {
    void SelectionSort::sort(std::vector<int>& arr, long long& comparacoes, long long& trocas) {
        comparacoes = 0;
        trocas = 0;
        
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j) {
                comparacoes++;
                if (arr[j] < arr[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                std::swap(arr[min_idx], arr[i]);
                trocas++;
            }
        }
    }
}

