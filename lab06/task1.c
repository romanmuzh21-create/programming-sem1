#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("Введіть розмір масиву N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Помилка: некоректний розмір масиву.\n");
        return 1;
    }

    // Виділення пам'яті через calloc з обнуленням
    int *arr = (int *)calloc((size_t)n, sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Критична помилка: дефіцит RAM (calloc повернув NULL).\n");
        return 1;
    }

    printf("Введіть %d цілих чисел:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Помилка вводу даних.\n");
            free(arr);
            arr = NULL;
            return 1;
        }
    }

    if (arr[0] == 0) {
        printf("Перший елемент дорівнює 0 — ділення на нуль неможливе.\n");
    } else {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] % arr[0] == 0) {
                count++;
            }
        }
        printf("Кількість елементів, що діляться на перший елемент (%d) без залишку: %d\n", arr[0], count);
    }

    // Звільнення пам'яті та занулення покажчика
    free(arr);
    arr = NULL;

    return 0;
}
