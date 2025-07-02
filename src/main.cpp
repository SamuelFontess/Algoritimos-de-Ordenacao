#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <map>
#include <functional>

#include "utils/ArrayGenerator.h"
#include "bubble_sort/BubbleSort.h"
#include "insertion_sort/InsertionSort.h"
#include "selection_sort/SelectionSort.h"
#include "merge_sort/MergeSort.h"
#include "quick_sort/QuickSort.h"

using namespace Sort;
using namespace Utils;

struct ResultadosExecucao {
    double tempo_ms;
    long long comparacoes;
    long long trocas;
};

ResultadosExecucao TempoExecucao(
    std::function<void(std::vector<int>&, long long&, long long&)> sortFunc,
    std::vector<int>& dados
) {
    long long comparacoes = 0;
    long long trocas = 0;

    auto inicio = std::chrono::high_resolution_clock::now();
    sortFunc(dados, comparacoes, trocas);
    auto fim = std::chrono::high_resolution_clock::now();

    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);

    return {duracao.count() / 1000.0, comparacoes, trocas};
}

// Wrapper para QuickSort com estratégia
ResultadosExecucao TempoExecucaoQuickSort(
    std::vector<int>& dados,
    QuickSort::PivotStrategy strategy
) {
    long long comparacoes = 0, trocas = 0;
    auto inicio = std::chrono::high_resolution_clock::now();
    QuickSort::sort(dados, comparacoes, trocas, strategy);
    auto fim = std::chrono::high_resolution_clock::now();

    auto duracao = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);
    return {duracao.count() / 1000.0, comparacoes, trocas};
}

int main() {
    std::vector<int> tamanho_array = {100, 1000, 5000, 10000, 20000, 50000};

    std::map<std::string, std::function<void(std::vector<int>&, long long&, long long&)>> sortAlgorithms = {
        {"Bubble Sort", BubbleSort::sort},
        {"Insertion Sort", InsertionSort::sort},
        {"Selection Sort", SelectionSort::sort},
        {"Merge Sort", MergeSort::sort}
        // QuickSort removido daqui para testar as variações abaixo
    };

    std::vector<std::string> tipos_dados = {"Aleatorio", "Quase_Ordenado", "Inversamente_Ordenado"};

    ArrayGenerator gerador;

    std::cout << "Executando testes de algoritmos de ordenacao...\n\n";

    for (int tamanho : tamanho_array) {
        std::cout << "Tamanho do Array: " << tamanho << "\n";

        for (const std::string& tipo : tipos_dados) {
            std::vector<int> dados_originais;

            if (tipo == "Aleatorio") {
                dados_originais = gerador.gerarArrayAleatorio(tamanho);
            } else if (tipo == "Quase_Ordenado") {
                dados_originais = gerador.gerarArrayQuaseOrdenado(tamanho);
            } else if (tipo == "Inversamente_Ordenado") {
                dados_originais = gerador.gerarArrayInversamenteOrdenado(tamanho);
            }

            std::cout << "  Tipo de Dado: " << tipo << "\n";

            // Outros algoritmos
            for (const auto& [nome_algo, func_algo] : sortAlgorithms) {
                std::vector<int> dados_copia = dados_originais;
                ResultadosExecucao resultados = TempoExecucao(func_algo, dados_copia);

                std::cout << "    " << nome_algo << ":\n";
                std::cout << "      Tempo: " << resultados.tempo_ms << " ms\n";
                std::cout << "      Comparacoes: " << resultados.comparacoes << "\n";
                std::cout << "      Trocas: " << resultados.trocas << "\n";
            }

            // QuickSort LastElement (pivô final)
            {
                std::vector<int> dados_copia = dados_originais;
                auto res = TempoExecucaoQuickSort(dados_copia, QuickSort::PivotStrategy::LastElement);
                std::cout << "    Quick Sort (Pivo Final):\n";
                std::cout << "      Tempo: " << res.tempo_ms << " ms\n";
                std::cout << "      Comparacoes: " << res.comparacoes << "\n";
                std::cout << "      Trocas: " << res.trocas << "\n";
            }

            // QuickSort FirstElement (pivô início)
            {
                std::vector<int> dados_copia = dados_originais;
                auto res = TempoExecucaoQuickSort(dados_copia, QuickSort::PivotStrategy::FirstElement);
                std::cout << "    Quick Sort (Pivo Inicial):\n";
                std::cout << "      Tempo: " << res.tempo_ms << " ms\n";
                std::cout << "      Comparacoes: " << res.comparacoes << "\n";
                std::cout << "      Trocas: " << res.trocas << "\n";
            }

            // QuickSort MedianOfThree
            {
                std::vector<int> dados_copia = dados_originais;
                auto res = TempoExecucaoQuickSort(dados_copia, QuickSort::PivotStrategy::MedianOfThree);
                std::cout << "    Quick Sort (Mediana de Tres):\n";
                std::cout << "      Tempo: " << res.tempo_ms << " ms\n";
                std::cout << "      Comparacoes: " << res.comparacoes << "\n";
                std::cout << "      Trocas: " << res.trocas << "\n";
            }

            std::cout << "\n";
        }

        std::cout << "----------------------------------------\n\n";
    }

    return 0;
}
