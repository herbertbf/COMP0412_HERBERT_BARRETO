import pandas as pd
import matplotlib.pyplot as plt
import os

# --- 1. Configuração ---
ARQUIVO_CSV = 'output/resultados.csv'
PASTA_GRAFICOS = 'graficos'

if not os.path.exists(PASTA_GRAFICOS):
    os.makedirs(PASTA_GRAFICOS)

# --- 2. Carregar os Dados do csv ---
try:
    df = pd.read_csv(ARQUIVO_CSV)
except FileNotFoundError:
    print(f"Erro: Arquivo '{ARQUIVO_CSV}' não encontrado.")
    exit()

df['tempo_gasto_ms'] = df['tempo_gasto_s'] * 1000

# --- 3. Loop Principal ---
tipos_vetor = df['tipo_vetor'].unique()
print("Aguarde, gerando gráficos...")

for tipo in tipos_vetor:
    print(f"  - Processando tipo: {tipo}")
    
    df_tipo = df[df['tipo_vetor'] == tipo]
    
    # --- 4. GRÁFICO 1: GERAL (Todos os algoritmos) ---
    plt.figure(figsize=(10, 6))
    
    try:
        df_pivot_geral = df_tipo.pivot(
            index='tamanho_n', 
            columns='algoritmo', 
            values='tempo_gasto_ms'
        )
        
        # Plot e configuração do gráfico GERAL
        df_pivot_geral.plot(kind='line', marker='o', ax=plt.gca())
        plt.title(f'Desempenho GERAL para Vetor {tipo}')
        plt.xlabel('Tamanho da Instância (n)')
        plt.ylabel('Tempo Gasto (ms)')
        plt.legend(title='Algoritmo')
        plt.grid(True, which='both', linestyle='--', linewidth=0.5)
        
        nome_arquivo_geral = f'{PASTA_GRAFICOS}/grafico_{tipo}.png'
        plt.savefig(nome_arquivo_geral)
        
    except Exception as e:
        print(f"    Erro ao plotar gráfico GERAL para '{tipo}': {e}")
    finally:
        plt.close() # Fecha a figura para liberar memória


print(f"Gráficos salvos na pasta '{PASTA_GRAFICOS}'.")