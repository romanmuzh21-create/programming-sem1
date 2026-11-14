#include <stdio.h>
#include <math.h>

int main(void) {
    double x_start, x_end, dx;

    printf("Введіть початкове значення X_start: ");
    if (scanf("%lf", &x_start) != 1) {
        fprintf(stderr, "Помилка: некоректний формат X_start.\n");
        return 1;
    }

    printf("Введіть кінцеве значення X_end: ");
    if (scanf("%lf", &x_end) != 1) {
        fprintf(stderr, "Помилка: некоректний формат X_end.\n");
        return 1;
    }

    printf("Введіть крок табулювання dX: ");
    if (scanf("%lf", &dx) != 1) {
        fprintf(stderr, "Помилка: некоректний формат dX.\n");
        return 1;
    }

    // Валідація вхідних меж та кроку
    if (x_start >= x_end || dx <= 0.0) {
        fprintf(stderr, "Помилка: має виконуватись умова X_start < X_end та dX > 0.\n");
        return 1;
    }

    printf("\n+------------+--------------+\n");
    printf("|     X      |     Y(X)     |\n");
    printf("+------------+--------------+\n");

    // Невелика похибка для коректного включення правої межі X_end у числах з плаваючою комою
    double eps = dx * 1e-9;

    for (double x = x_start; x <= x_end + eps; x += dx) {
        // Усунення ефекту "-0.00" при переході через нуль
        if (fabs(x) < 1e-12) {
            x = 0.0;
        }

        if (x < -1.0) {
            if (fabs(x) < 1e-12) {
                printf("| %10.4lf | [Не визначено] |\n", x);
            } else {
                double y = 1.0 / x;
                printf("| %10.4lf | %12.4lf |\n", x, y);
            }
        } else if (x <= 1.0) {
            double under_root = 1.0 - x * x;
            // Захист від мікроскопічних від'ємних значень на межах -1 та 1 через похибку double
            if (under_root < -1e-12) {
                printf("| %10.4lf | [Не визначено] |\n", x);
            } else {
                if (under_root < 0.0) {
                    under_root = 0.0;
                }
                double y = sqrt(under_root);
                printf("| %10.4lf | %12.4lf |\n", x, y);
            }
        } else {
            double y = x - 1.0;
            printf("| %10.4lf | %12.4lf |\n", x, y);
        }
    }

    printf("+------------+--------------+\n");

    return 0;
}
