#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    double x_start, x_end, dx;

    printf(" Завдання 1: Табулювання кусочної функції (Варіант 3) \n");
    printf("Введіть X_start, X_end та dX: ");
    if (scanf("%lf %lf %lf", &x_start, &x_end, &dx) != 3) {
        printf("Помилка: некоректний ввід даних.\n");
        return 1;
    }

    
    if (x_start >= x_end || dx <= 0) {
        printf("Помилка валідації: має бути X_start < X_end та dX > 0.\n");
        return 1;
    }

    printf("\n+------------+----------------+\n");
    printf("|     X      |      Y(X)      |\n");
    printf("+------------+----------------+\n");

    for (double x = x_start; x <= x_end + dx / 2.0; x += dx) {
        if (x <= 1.0) {
            double y = 2.0 * x + 1.0;
            printf("| %10.2lf | %14.4lf |\n", x, y);
        } else if (x > 1.0 && x <= 3.0) {
            
            if (fabs(x - 2.0) < 1e-7) {
                printf("| %10.2lf | [Не визначено] |\n", x);
            } else {
                double y = x / (x - 2.0);
                printf("| %10.2lf | %14.4lf |\n", x, y);
            }
        } else {
            
            if (x < 0) {
                printf("| %10.2lf | [Не визначено] |\n", x);
            } else {
                double y = sqrt(x);
                printf("| %10.2lf | %14.4lf |\n", x, y);
            }
        }
    }

    printf("+------------+----------------+\n");
    return 0;
}
