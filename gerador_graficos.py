import matplotlib.pyplot as plt
import pandas as pd
import re

def ler_tabela_markdown(texto):
    linhas = texto.strip().split('\n')
    cabecalho = [coluna.strip() for coluna in linhas[0].split('|') if coluna.strip()]
    dados = []
    for linha in linhas[2:]:
        valores = [valor.strip() for valor in linha.split('|') if valor.strip()]
        if valores:
            dados.append(valores)
    return pd.DataFrame(dados, columns=cabecalho)

def gerar_grafico(dados, titulo, rotulo_y, nome_arquivo, pasta_saida):
    plt.figure(figsize=(12, 7))
    for coluna in dados.columns[1:]:
        dados[coluna] = pd.to_numeric(dados[coluna], errors='coerce')
        plt.plot(dados['Algoritmo'], dados[coluna], marker='o', label=coluna)
    plt.title(titulo)
    plt.xlabel('Algoritmo')
    plt.ylabel(rotulo_y)
    plt.xticks(rotation=45, ha='right')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f'{pasta_saida}/{nome_arquivo}.png')
    plt.close()

with open('Relatorio-tecnico.md', 'r') as arquivo:
    conteudo = arquivo.read()

secoes = re.split(r'### (Tempo de Execução \(ms\)|Comparações|Trocas)', conteudo)

blocos_tempo = re.split(r'#### Tamanho do Array: (\d+)', secoes[2])
dados_tempo = {}
for i in range(1, len(blocos_tempo), 2):
    tamanho = blocos_tempo[i]
    tabela = blocos_tempo[i+1]
    dados_tempo[tamanho] = ler_tabela_markdown(tabela)

blocos_comp = re.split(r'#### Tamanho do Array: (\d+)', secoes[4])
dados_comp = {}
for i in range(1, len(blocos_comp), 2):
    tamanho = blocos_comp[i]
    tabela = blocos_comp[i+1]
    dados_comp[tamanho] = ler_tabela_markdown(tabela)

blocos_trocas = re.split(r'#### Tamanho do Array: (\d+)', secoes[6])
dados_trocas = {}
for i in range(1, len(blocos_trocas), 2):
    tamanho = blocos_trocas[i]
    tabela = blocos_trocas[i+1]
    dados_trocas[tamanho] = ler_tabela_markdown(tabela)

saida = '/graficos'

for tamanho, df in dados_tempo.items():
    gerar_grafico(df, f'Tempo de Execução vs. Algoritmo (Tamanho do Array: {tamanho})', 'Tempo (ms)', f'tempo_array_{tamanho}', saida)

for tamanho, df in dados_comp.items():
    gerar_grafico(df, f'Comparações vs. Algoritmo (Tamanho do Array: {tamanho})', 'Número de Comparações', f'comparacoes_array_{tamanho}', saida)

for tamanho, df in dados_trocas.items():
    gerar_grafico(df, f'Trocas vs. Algoritmo (Tamanho do Array: {tamanho})', 'Número de Trocas', f'trocas_array_{tamanho}', saida)

def preparar_dados_gerais(dicionario, nome_metrica):
    df_geral = pd.DataFrame()
    for tamanho, df in dicionario.items():
        df_melt = df.melt(id_vars=['Algoritmo'], var_name='Tipo de Dado', value_name=nome_metrica)
        df_melt['Tamanho do Array'] = int(tamanho)
        df_geral = pd.concat([df_geral, df_melt], ignore_index=True)
    return df_geral

tempo_geral = preparar_dados_gerais(dados_tempo, 'Tempo (ms)')
comp_geral = preparar_dados_gerais(dados_comp, 'Número de Comparações')
trocas_geral = preparar_dados_gerais(dados_trocas, 'Número de Trocas')

def grafico_tendencia(df, metrica, nome_arquivo, titulo):
    plt.figure(figsize=(14, 8))
    for algoritmo in df['Algoritmo'].unique():
        parcial = df[df['Algoritmo'] == algoritmo]
        for tipo in parcial['Tipo de Dado'].unique():
            parte = parcial[parcial['Tipo de Dado'] == tipo]
            plt.plot(parte['Tamanho do Array'], parte[metrica], marker='o', label=f'{algoritmo} ({tipo})')
    plt.title(titulo)
    plt.xlabel('Tamanho do Vetor')
    plt.ylabel(metrica)
    plt.xscale('log')
    plt.yscale('log')
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f'{saida}/{nome_arquivo}.png')
    plt.close()

grafico_tendencia(tempo_geral, 'Tempo (ms)', 'tendencia_tempo', 'Tempo de Execução vs. Tamanho do Vetor (Todos os Tipos de Dados)')
grafico_tendencia(comp_geral, 'Número de Comparações', 'tendencia_comparacoes', 'Comparações vs. Tamanho do Vetor (Todos os Tipos de Dados)')
grafico_tendencia(trocas_geral, 'Número de Trocas', 'tendencia_trocas', 'Trocas vs. Tamanho do Vetor (Todos os Tipos de Dados)')

print(f'Gráficos gerados e salvos em {saida}')
