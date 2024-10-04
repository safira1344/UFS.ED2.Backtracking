#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int ENDED = 0;
int FIXED_COL = 0;
int array[9];
int FIRST_LINE;
int SOL;

int checkFixedQueen(int c, int k)
{
    if (array[FIXED_COL] == c)
    {
        return 0;
    }
    if (abs(array[FIXED_COL] - c) == abs(FIXED_COL - k))
    {
        return 0;
    }
    return 1;
}

void fc(int a[], int k, int candidates[], int *n)
{
    int c;
    int i;
    int passed = 1;
    for (c = 1; c <= 8; c++)
    {
        if (!checkFixedQueen(c, k))
            continue;
        passed = 1;
        for (i = 1; i < k; i++)
        {
            if (a[i] == c)
            {
                // mesma linha
                passed = 0;
                break;
            }
            if (abs(a[i] - c) == abs(i - k))
            {
                // mesma diagonal
                passed = 0;
                break;
            }
        }
        if (passed)
        {
            candidates[*n] = c;
            *n += 1;
        }
    }
    return;
}

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

void bt(int a[], int k, int depth)
{
    if (depth == 8)
    {
        process_Solution(a);
        return;
    }

    if (k == FIXED_COL)
    {
        bt(a, k + 1, depth + 1);
        return;
    }

    int candidates[9], nCandidates = 0;
    memset(candidates, 0, sizeof(candidates));

    fc(a, k, candidates, &nCandidates);

    for (int i = 0; i < nCandidates; i++)
    {
        a[k] = candidates[i];
        bt(a, k + 1, depth + 1);
    }
}

int main()
{
    int tests = 0;
    char c;
    scanf("%d", &tests);

    for (int i = 0; i < tests; i++)
    {
        memset(array, 0, sizeof(array));
        // ENDED = 0;
        int row = 0, col = 0;
        scanf("%d %d", &row, &col);
        FIXED_COL = col;
        array[FIXED_COL] = row;
        SOL = 1;
        FIRST_LINE = 1;
        bt(array, 1, 0);
        printf("\n");
    }

    return 0;
}
