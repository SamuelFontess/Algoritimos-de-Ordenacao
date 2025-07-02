#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <vector>

namespace Sort {
    class BubbleSort {
    public:
        static void sort(std::vector<int>& arr, long long& comparacoes, long long& trocas);
    };
}

#endif // BUBBLE_SORT_H

