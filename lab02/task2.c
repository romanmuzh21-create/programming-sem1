#include <stdio.h>
#include <math.h>

#define MAX_ITERATIONS 100000

int main(void) {
    double x, eps;

    printf("Введіть значення аргументу X: ");
    if (scanf("%lf", &x) != 1 || !isfinite(x)) {
        fprintf(stderr, "Помилка: некоректне значення X (очікується скінченне дійсне число).\n");
        return 1;
    }

    printf("Введіть бажану точність epsilon (наприклад, 1e-6): ");
    if (scanf("%lf", &eps) != 1 || eps <= 0.0 || !isfinite(eps)) {
        fprintf(stderr, "Помилка: точність epsilon має бути додатним скінченним числом.\n");
        return 1;
    }

    // Область збіжності ряду для sin(X): (-inf; +inf)
    double term = x;       // Початковий член ряду a_0 = X
    double sum = 0.0;
    int n = 0;
    int diverged = 0;

    while (fabs(term) >= eps) {
        if (n >= MAX_ITERATIONS) {
            diverged = 1;
            break;
        }

        sum += term;
        n++;

        // Рекурентний перехід: a_n = a_{n-1} * (-X^2) / (2n * (2n + 1))
        term = term * (-x * x) / ((2.0 * n) * (2.0 * n + 1.0));
    }

    if (diverged) {
        printf("\n[Увага] Досягнуто ліміт у %d ітерацій! Точність не досягнута (можлива розбіжність або втрата точності при великих X).\n", MAX_ITERATIONS);
    }

    double exact = sin(x);
    double abs_error = fabs(sum - exact);

    printf("\n--- Результати обчислень для sin(%.6lf) ---\n", x);
    printf("Обчислена сума ряду:    %.10lf\n", sum);
    printf("Еталонне sin(X):        %.10lf\n", exact);
    printf("Абсолютна похибка:      %.10e\n", abs_error);
    printf("Витрачено ітерацій:     %d\n", n);

    return 0;
}
