#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <vector>

namespace Sort {
    class SelectionSort {
    public:
        static void sort(std::vector<int>& arr, long long& comparacoes, long long& trocas);
    };
}

#endif // SELECTION_SORT_H

