#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
#include <vector>

namespace Sort {
    class QuickSort {
    public:
        enum class PivotStrategy {
            LastElement,
            FirstElement,
            MedianOfThree
        };

        static void sort(std::vector<int>& arr, long long& comparacoes, long long& trocas, PivotStrategy strategy = PivotStrategy::LastElement);

    private:
        static int particionar(std::vector<int>& arr, int baixo, int alto, long long& comparacoes, long long& trocas, PivotStrategy strategy);
        static void quickSort(std::vector<int>& arr, int baixo, int alto, long long& comparacoes, long long& trocas, PivotStrategy strategy);

        static int escolherPivo(std::vector<int>& arr, int baixo, int alto, PivotStrategy strategy, long long& trocas);
        static int medianaDeTres(std::vector<int>& arr, int baixo, int meio, int alto, long long& trocas);
    };
}

#endif // QUICK_SORT_H

