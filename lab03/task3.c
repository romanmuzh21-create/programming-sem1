#include <stdio.h>

#define MAX_LEN 100

int main(void) {
    char str[MAX_LEN + 1];

    printf("Введіть рядок для перевірки на паліндром: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        fprintf(stderr, "Помилка зчитування рядка.\n");
        return 1;
    }

    // Ручний підрахунок довжини рядка до нуль-термінатора '\0'
    // та видалення символу перенесення рядка '\n', який залишає fgets
    int len = 0;
    while (str[len] != '\0') {
        if (str[len] == '\n') {
            str[len] = '\0';
            break;
        }
        len++;
    }

    // Двосторонній прохід (Two Pointers) з ігноруванням пробілів
    int left = 0;
    int right = len - 1;
    int is_palindrome = 1;

    while (left < right) {
        if (str[left] == ' ') {
            left++;
            continue;
        }
        if (str[right] == ' ') {
            right--;
            continue;
        }

        if (str[left] != str[right]) {
            is_palindrome = 0;
            break;
        }
        left++;
        right--;
    }

    if (len == 0) {
        printf("Введено порожній рядок.\n");
    } else if (is_palindrome) {
        printf("Результат: рядок \"%s\" Є паліндромом.\n", str);
    } else {
        printf("Результат: рядок \"%s\" НЕ є паліндромом.\n", str);
    }

    return 0;
}
