#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int FIXED_COL = 0; // Coluna fixa onde já existe uma rainha
int array[9];      // Array para armazenar a linha de cada rainha
int FIRST_LINE;    // Controle para imprimir o cabeçalho uma vez
int SOL;           // Contador de soluções

// Função para verificar se a rainha fixa entra em conflito com a posição atual
int checkFixedQueen(int c, int k)
{
    if (array[FIXED_COL] == c)
    {
        return 0; // Mesma linha
    }
    if (abs(array[FIXED_COL] - c) == abs(FIXED_COL - k))
    {
        return 0; // Mesma diagonal
    }
    return 1; // Não há conflito
}

// Função para construir os candidatos válidos para a posição atual
void fc(int a[], int k, int candidates[], int *n)
{
    int c, i;
    int passed;
    for (c = 1; c <= 8; c++)
    { // Testar todas as linhas de 1 a 8
        if (!checkFixedQueen(c, k))
            continue; // Verificar se a rainha na posição fixa conflita com a posição atual
        passed = 1;
        for (i = 1; i < k; i++)
        { // Verificar se há conflito com as rainhas já posicionadas
            if (a[i] == c || abs(a[i] - c) == abs(i - k))
            {
                passed = 0; // Mesma linha ou mesma diagonal
                break;
            }
        }
        if (passed)
        { // Se não houver conflito, adicionar como candidato
            candidates[*n] = c;
            (*n)++;
        }
    }
}

// Função para processar e imprimir uma solução válida
void process_Solution(int a[])
{
    if (FIRST_LINE)
    {
        printf("SOLN       COLUMN\n");
        printf(" #      1 2 3 4 5 6 7 8\n\n");
        FIRST_LINE = 0;
    }
    printf("%2d     ", SOL++);
    for (int i = 1; i <= 8; i++)
        printf(" %d", a[i]);
    printf("\n");
}

// Função de backtracking para encontrar as soluções
void bt(int a[], int k, int depth)
{
    if (depth == 8)
    { // Se já colocamos 8 rainhas, temos uma solução
        process_Solution(a);
        return;
    }

    if (k == FIXED_COL)
    { // Se for a coluna da rainha fixa, pula para a próxima
        bt(a, k + 1, depth + 1);
        return;
    }

    int candidates[9], nCandidates = 0;
    memset(candidates, 0, sizeof(candidates));

    // Construir os candidatos válidos para a coluna atual
    fc(a, k, candidates, &nCandidates);

    // Tentar cada candidato
    for (int i = 0; i < nCandidates; i++)
    {
        a[k] = candidates[i];    // Posicionar a rainha na coluna k
        bt(a, k + 1, depth + 1); // Recursão para a próxima coluna
    }
}

int main()
{
    int tests = 0;
    scanf("%d", &tests); // Ler o número de casos de teste

    for (int i = 0; i < tests; i++)
    {
        memset(array, 0, sizeof(array)); // Limpar o array para um novo teste
        int row = 0, col = 0;
        scanf("%d %d", &row, &col); // Ler a posição fixa da rainha

        FIXED_COL = col;        // Atualizar a coluna da rainha fixa
        array[FIXED_COL] = row; // Atualizar a linha da rainha fixa
        SOL = 1;                // Reiniciar o contador de soluções
        FIRST_LINE = 1;         // Marcar que o cabeçalho precisa ser impresso

        bt(array, 1, 0); // Iniciar a busca de soluções
        printf("\n");    // Linha em branco entre os casos de teste
    }

    return 0;
}