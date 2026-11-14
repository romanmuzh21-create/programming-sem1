#include <stdio.h>

// Обов'язкові прототипи функцій
unsigned long long calculate_fibonacci(int n);
int track_max_requested(int n);

int main(void) {
    int n;

    printf("=== Обчислення чисел Фібоначчі (введіть -1 для виходу) ===\n");

    while (1) {
        printf("\nВведіть порядковий номер числа Фібоначчі n (0..93): ");
        if (scanf("%d", &n) != 1) {
            fprintf(stderr, "Помилка: очікується ціле число.\n");
            return 1;
        }

        if (n == -1) {
            printf("Роботу завершено.\n");
            break;
        }

        if (n < 0 || n > 93) {
            printf("Помилка: введіть n у діапазоні від 0 до 93 (щоб уникнути переповнення uint64).\n");
            continue;
        }

        unsigned long long fib_result = calculate_fibonacci(n);
        int max_n_so_far = track_max_requested(n);

        printf("F(%d) = %llu\n", n, fib_result);
        printf("[Аналітика static] Максимальний номер n, який запитувався за сесію: %d\n", max_n_so_far);
    }

    return 0;
}

// Підпрограма обчислення n-го числа Фібоначчі (Pass-by-Value)
unsigned long long calculate_fibonacci(int n) {
    if (n == 0) {
        return 0ULL;
    }
    if (n == 1) {
        return 1ULL;
    }

    unsigned long long prev2 = 0ULL;
    unsigned long long prev1 = 1ULL;
    unsigned long long current = 0ULL;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }

    return current;
}

// Допоміжна функція зі статичною змінною для відстеження максимуму
int track_max_requested(int n) {
    static int max_requested = -1; // Ініціалізується лише один раз при запуску програми

    if (n > max_requested) {
        max_requested = n;
    }

    return max_requested;
}
