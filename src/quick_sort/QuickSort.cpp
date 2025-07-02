#include "QuickSort.h"
#include <algorithm>

namespace Sort {
    int QuickSort::medianaDeTres(std::vector<int>& arr, int baixo, int meio, int alto, long long& trocas) {
        if ((arr[baixo] > arr[meio]) != (arr[baixo] > arr[alto])) return baixo;
        else if ((arr[meio] > arr[baixo]) != (arr[meio] > arr[alto])) return meio;
        else return alto;
    }

    int QuickSort::escolherPivo(std::vector<int>& arr, int baixo, int alto, PivotStrategy strategy, long long& trocas) {
        switch (strategy) {
            case PivotStrategy::FirstElement:
                std::swap(arr[baixo], arr[alto]);
                trocas++;
                return alto;

            case PivotStrategy::MedianOfThree: {
                int meio = baixo + (alto - baixo) / 2;
                int med = medianaDeTres(arr, baixo, meio, alto, trocas);
                if (med != alto) {
                    std::swap(arr[med], arr[alto]);
                    trocas++;
                }
                return alto;
            }

            case PivotStrategy::LastElement:
            default:
                return alto;
        }
    }

    int QuickSort::particionar(std::vector<int>& arr, int baixo, int alto, long long& comparacoes, long long& trocas, PivotStrategy strategy) {
        int pivoIndex = escolherPivo(arr, baixo, alto, strategy, trocas);
        int pivo = arr[pivoIndex];
        int i = (baixo - 1);

        for (int j = baixo; j <= alto - 1; ++j) {
            comparacoes++;
            if (arr[j] < pivo) {
                i++;
                std::swap(arr[i], arr[j]);
                trocas++;
            }
        }
        std::swap(arr[i + 1], arr[alto]);
        trocas++;
        return (i + 1);
    }

    void QuickSort::quickSort(std::vector<int>& arr, int baixo, int alto, long long& comparacoes, long long& trocas, PivotStrategy strategy) {
        if (baixo < alto) {
            int pi = particionar(arr, baixo, alto, comparacoes, trocas, strategy);
            quickSort(arr, baixo, pi - 1, comparacoes, trocas, strategy);
            quickSort(arr, pi + 1, alto, comparacoes, trocas, strategy);
        }
    }

    void QuickSort::sort(std::vector<int>& arr, long long& comparacoes, long long& trocas, PivotStrategy strategy) {
        comparacoes = 0;
        trocas = 0;
        if (!arr.empty()) {
            quickSort(arr, 0, (int)arr.size() - 1, comparacoes, trocas, strategy);
        }
    }
}

