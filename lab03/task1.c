#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 15

int main(void) {
    int arr[SIZE];

    srand((unsigned int)time(NULL));

    // Заповнення масиву випадковими числами в діапазоні [-50; 50]
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 101 - 50;
    }

    printf("Вихідний масив (%d елементів):\n", SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n\n");

    // 1. Пошук максимального елемента (ініціалізація нульовим елементом)
    int max_val = arr[0];
    int max_idx = 0;
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_idx = i;
        }
    }
    printf("Максимальний елемент: %d (індекс %d)\n", max_val, max_idx);

    // 2. Пошук першого та останнього нульових елементів
    int first_zero = -1;
    int last_zero = -1;

    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == 0) {
            if (first_zero == -1) {
                first_zero = i;
            }
            last_zero = i;
        }
    }

    if (first_zero == -1 || first_zero == last_zero) {
        printf("Добуток між нулями: у масиві менше двох нульових елементів.\n");
    } else if (last_zero - first_zero == 1) {
        printf("Добуток між нулями: нульові елементи стоять поруч (індекси %d та %d), елементів між ними немає.\n", first_zero, last_zero);
    } else {
        long long product = 1;
        for (int i = first_zero + 1; i < last_zero; i++) {
            product *= arr[i];
        }
        printf("Перший нуль на індексі %d, останній — на індексі %d.\n", first_zero, last_zero);
        printf("Добуток елементів між ними: %lld\n", product);
    }

    return 0;
}
