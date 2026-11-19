#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int rows;
    printf("Введіть кількість рядків трикутника Паскаля: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        fprintf(stderr, "Помилка: некоректна кількість рядків.\n");
        return 1;
    }

    // Виділення масиву покажчиків на рядки
    int **pascal = (int **)malloc((size_t)rows * sizeof(int *));
    if (pascal == NULL) {
        fprintf(stderr, "Помилка виділення пам'яті під масив покажчиків.\n");
        return 1;
    }

    // Виділення пам'яті під кожен рядок (довжина i + 1) та заповнення
    for (int i = 0; i < rows; i++) {
        pascal[i] = (int *)malloc((size_t)(i + 1) * sizeof(int));
        if (pascal[i] == NULL) {
            fprintf(stderr, "Помилка виділення пам'яті для рядка %d.\n", i);
            for (int j = 0; j < i; j++) {
                free(pascal[j]);
                pascal[j] = NULL;
            }
            free(pascal);
            pascal = NULL;
            return 1;
        }

        pascal[i][0] = 1;
        pascal[i][i] = 1;
        for (int j = 1; j < i; j++) {
            pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }

    printf("\nТрикутник Паскаля:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", pascal[i][j]);
        }
        printf("\n");
    }

    // Очищення кожного рядка
    for (int i = 0; i < rows; i++) {
        free(pascal[i]);
        pascal[i] = NULL;
    }

    // Очищення масиву покажчиків
    free(pascal);
    pascal = NULL;

    return 0;
}
