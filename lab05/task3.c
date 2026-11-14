#include <stdio.h>
#include <stddef.h>

#define BUFFER_SIZE 10

// Прототипи функцій без використання оператора []
void print_buffer(const int *start_ptr, size_t count);
void reverse_buffer_in_place(int *start_ptr, size_t count);

int main(void) {
    int buffer[BUFFER_SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("Вихідний буфер у пам'яті:\n");
    print_buffer(buffer, BUFFER_SIZE);

    reverse_buffer_in_place(buffer, BUFFER_SIZE);

    printf("\nБуфер після реверсу «на місці» (In-Place):\n");
    print_buffer(buffer, BUFFER_SIZE);

    return 0;
}

void print_buffer(const int *start_ptr, size_t count) {
    if (start_ptr == NULL || count == 0) {
        return;
    }

    const int *end_ptr = start_ptr + count;

    for (const int *ptr = start_ptr; ptr < end_ptr; ptr++) {
        ptrdiff_t offset = ptr - start_ptr;
        printf("Індекс [%td] (адреса %p): %d\n", offset, (void *)ptr, *(start_ptr + offset));
    }
}

void reverse_buffer_in_place(int *start_ptr, size_t count) {
    if (start_ptr == NULL || count < 2) {
        return;
    }

    int *left_ptr = start_ptr;
    int *right_ptr = start_ptr + (count - 1);

    printf("\n--- Трасування руху зустрічних покажчиків ---\n");
    while (left_ptr < right_ptr) {
        ptrdiff_t left_idx = left_ptr - start_ptr;
        ptrdiff_t right_idx = right_ptr - start_ptr;
        printf("Обмін елементів на позиціях %td (%d) <-> %td (%d)\n",
               left_idx, *left_ptr, right_idx, *right_ptr);

        int temp = *left_ptr;
        *left_ptr = *right_ptr;
        *right_ptr = temp;

        left_ptr++;
        right_ptr--;
    }
}
