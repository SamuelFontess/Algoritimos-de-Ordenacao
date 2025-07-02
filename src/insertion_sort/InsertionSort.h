#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <vector>

namespace Sort {
    class InsertionSort {
    public:
        static void sort(std::vector<int>& arr, long long& comparacoes, long long& trocas);
    };
}

#endif // INSERTION_SORT_H

