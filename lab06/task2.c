#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t capacity = 5;
    size_t size = 0;

    double *buffer = (double *)malloc(capacity * sizeof(double));
    if (buffer == NULL) {
        fprintf(stderr, "Критична помилка: не вдалося виділити початковий буфер.\n");
        return 1;
    }

    printf("Вводьте дійсні числа (від'ємне число завершує ввід):\n");
    while (1) {
        double val;
        printf("> ");
        if (scanf("%lf", &val) != 1) {
            fprintf(stderr, "Помилка вводу.\n");
            free(buffer);
            buffer = NULL;
            return 1;
        }

        // Ознака зупинки: від'ємне число
        if (val < 0.0) {
            break;
        }

        // Перевірка заповнення буфера та масштабування на +5 елементів
        if (size == capacity) {
            size_t new_capacity = capacity + 5;
            double *temp = (double *)realloc(buffer, new_capacity * sizeof(double));
            if (temp == NULL) {
                fprintf(stderr, "Помилка дефіциту ресурсів при realloc! Звільнення буфера...\n");
                free(buffer);
                buffer = NULL;
                return 1;
            }
            buffer = temp;
            capacity = new_capacity;
            printf("[INFO] Буфер розширено до %zu елементів.\n", capacity);
        }

        buffer[size++] = val;
    }

    printf("\nНакопичені дані (%zu елементів):\n", size);
    for (size_t i = 0; i < size; i++) {
        printf("%.2f ", buffer[i]);
    }
    printf("\n");

    free(buffer);
    buffer = NULL;

    return 0;
}
