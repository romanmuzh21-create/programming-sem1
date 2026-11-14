#include <stdio.h>
#include <stdint.h>

// Прототипи 4 канонічних операцій та виводу
uint32_t set_bit(uint32_t reg, uint8_t bit);
uint32_t clear_bit(uint32_t reg, uint8_t bit);
uint32_t toggle_bit(uint32_t reg, uint8_t bit);
uint8_t  check_bit(uint32_t reg, uint8_t bit);
void     print_binary(uint32_t reg);

int main(void) {
    // Початковий стан регістра: біт 5 та біт 31 встановлені в 1, щоб наочно показати скидання та перевірку
    uint32_t gpio_reg = (1U << 31) | (1U << 5) | (1U << 4) | (1U << 1);

    printf("Початковий стан регістра (HEX: 0x%08X):\n", gpio_reg);
    print_binary(gpio_reg);

    // 1. Встановити біт 0
    printf("\n[1] Встановлення біта 0 (set_bit, маска 1U << 0):\n");
    gpio_reg = set_bit(gpio_reg, 0);
    print_binary(gpio_reg);

    // 2. Скинути біт 5
    printf("\n[2] Скидання біта 5 (clear_bit, маска ~(1U << 5)):\n");
    gpio_reg = clear_bit(gpio_reg, 5);
    print_binary(gpio_reg);

    // 3. Інвертувати біт 9 (перший раз: 0 -> 1)
    printf("\n[3a] Інвертування біта 9 (toggle_bit, маска 1U << 9):\n");
    gpio_reg = toggle_bit(gpio_reg, 9);
    print_binary(gpio_reg);

    // Інвертувати біт 9 ще раз (1 -> 0)
    printf("\n[3b] Повторне інвертування біта 9 (toggle_bit, маска 1U << 9):\n");
    gpio_reg = toggle_bit(gpio_reg, 9);
    print_binary(gpio_reg);

    // 4. Перевірити стан біта 31
    uint8_t bit31_state = check_bit(gpio_reg, 31);
    printf("\n[4] Перевірка стану біта 31 (check_bit): %u\n", bit31_state);
    printf("Кінцевий стан регістра (HEX: 0x%08X):\n", gpio_reg);
    print_binary(gpio_reg);

    return 0;
}

uint32_t set_bit(uint32_t reg, uint8_t bit) {
    return reg | (1U << bit);
}

uint32_t clear_bit(uint32_t reg, uint8_t bit) {
    return reg & ~(1U << bit);
}

uint32_t toggle_bit(uint32_t reg, uint8_t bit) {
    return reg ^ (1U << bit);
}

uint8_t check_bit(uint32_t reg, uint8_t bit) {
    return (uint8_t)((reg >> bit) & 1U);
}

void print_binary(uint32_t reg) {
    printf("BIN: ");
    for (int i = 31; i >= 0; i--) {
        printf("%u", (reg >> i) & 1U);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}
