#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

namespace Sort {
    class MergeSort {
    public:
        static void sort(std::vector<int>& arr, long long& comparacoes, long long& trocas);

    private:
        static void merge(std::vector<int>& arr, int esquerda, int meio, int direita, long long& comparacoes, long long& trocas);
        static void mergeSort(std::vector<int>& arr, int esquerda, int direita, long long& comparacoes, long long& trocas);
    };
}

#endif // MERGE_SORT_H

