#include "InsertionSort.h"

namespace Sort {
    void InsertionSort::sort(std::vector<int>& arr, long long& comparacoes, long long& trocas) {
        comparacoes = 0;
        trocas = 0;
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                comparacoes++;
                arr[j + 1] = arr[j];
                trocas++;
                j--;
            }
            if (j >= 0) comparacoes++;
            arr[j + 1] = key;
        }
    }
}
