#include <stdio.h>

// Прототип функції з захищеними const вхідними покажчиками та двома Out-параметрами
int integer_division_analysis(const int *a, const int *b, int *quotient, int *remainder);

int main(void) {
    int num_a, num_b;
    int quot = 0;
    int rem = 0;

    printf("Введіть ділене A (ціле число): ");
    if (scanf("%d", &num_a) != 1) {
        fprintf(stderr, "Помилка: очікується ціле число.\n");
        return 1;
    }

    printf("Введіть дільник B (ціле число, не нуль): ");
    if (scanf("%d", &num_b) != 1) {
        fprintf(stderr, "Помилка: очікується ціле число.\n");
        return 1;
    }

    int status = integer_division_analysis(&num_a, &num_b, &quot, &rem);

    if (status != 0) {
        fprintf(stderr, "Помилка виконання (код %d): передано NULL або дільник B дорівнює 0.\n", status);
        return 1;
    }

    printf("\n--- Результати цілочисельного ділення (%d / %d) ---\n", num_a, num_b);
    printf("Частка (quotient):   %d\n", quot);
    printf("Залишок (remainder): %d\n", rem);

    return 0;
}

int integer_division_analysis(const int *a, const int *b, int *quotient, int *remainder) {
    // Обов'язкова валідація покажчиків та математичної коректності дільника
    if (a == NULL || b == NULL || quotient == NULL || remainder == NULL) {
        return 1;
    }
    if (*b == 0) {
        return 1;
    }

    // Розіменування Out-параметрів ліворуч від знака присвоєння
    *quotient = (*a) / (*b);
    *remainder = (*a) % (*b);

    return 0;
}
