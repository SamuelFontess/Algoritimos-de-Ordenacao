
#include "MergeSort.h"
#include <vector>
#include <algorithm>

namespace Sort {
    void MergeSort::merge(std::vector<int>& arr, int esquerda, int meio, int direita, long long& comparacoes, long long& trocas) {
        int n1 = meio - esquerda + 1;
        int n2 = direita - meio;

        std::vector<int> E(n1), D(n2);

        for (int i = 0; i < n1; ++i)
            E[i] = arr[esquerda + i];
        for (int j = 0; j < n2; ++j)
            D[j] = arr[meio + 1 + j];

        int i = 0; 
        int j = 0; 
        int k = esquerda; 

        while (i < n1 && j < n2) {
            comparacoes++;
            if (E[i] <= D[j]) {
                arr[k] = E[i];
                i++;
            } else {
                arr[k] = D[j];
                j++;
            }
            k++;
            trocas++;
        }

        while (i < n1) {
            arr[k] = E[i];
            i++;
            k++;
            trocas++;
        }

        while (j < n2) {
            arr[k] = D[j];
            j++;
            k++;
            trocas++;
        }
    }

    void MergeSort::mergeSort(std::vector<int>& arr, int esquerda, int direita, long long& comparacoes, long long& trocas) {
        if (esquerda < direita) {
            int meio = esquerda + (direita - esquerda) / 2;

            mergeSort(arr, esquerda, meio, comparacoes, trocas);
            mergeSort(arr, meio + 1, direita, comparacoes, trocas);

            merge(arr, esquerda, meio, direita, comparacoes, trocas);
        }
    }

    void MergeSort::sort(std::vector<int>& arr, long long& comparacoes, long long& trocas) {
        comparacoes = 0;
        trocas = 0;
        
        mergeSort(arr, 0, arr.size() - 1, comparacoes, trocas);
    }
}

