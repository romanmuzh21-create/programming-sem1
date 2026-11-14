#include <stdio.h>
#include <stdint.h>

// Прототипи функцій роботи з регістром через покажчик
void configure_register(uint32_t *reg);
int  check_status_flag(const uint32_t *reg, uint8_t bit_pos);
void print_binary32(uint32_t reg);

int main(void) {
    // Початковий стан регістра: біти 8 та 12 встановлені в 1 для наочності скидання та перевірки
    uint32_t peripheral_reg = (1U << 12) | (1U << 8) | (1U << 4);

    printf("Стан регістра ДО модифікації (HEX: 0x%08X):\n", peripheral_reg);
    print_binary32(peripheral_reg);

    // Модифікація регістра "на місці" за його фізичною адресою
    configure_register(&peripheral_reg);

    printf("\nСтан регістра ПІСЛЯ модифікації (HEX: 0x%08X):\n", peripheral_reg);
    print_binary32(peripheral_reg);

    // Перевірка статусного біта 12 через const-покажчик
    int flag12 = check_status_flag(&peripheral_reg, 12);
    printf("\nСтан статусного біта 12: %d\n", flag12);

    return 0;
}

void configure_register(uint32_t *reg) {
    // Захист від розіменування NULL-покажчика
    if (reg == NULL) {
        return;
    }

    // 1. Встановити в 1 біт 0 через операцію АБО (|)
    *reg |= (1U << 0);

    // 2. Скинути в 0 біт 8 через операцію І (&) з інверсією маски (~)
    *reg &= ~(1U << 8);

    // 3. Інвертувати біт 16 через операцію XOR (^)
    *reg ^= (1U << 16);
}

int check_status_flag(const uint32_t *reg, uint8_t bit_pos) {
    if (reg == NULL || bit_pos > 31) {
        return -1;
    }

    return (int)(((*reg) >> bit_pos) & 1U);
}

void print_binary32(uint32_t reg) {
    printf("BIN: ");
    for (int i = 31; i >= 0; i--) {
        printf("%u", (reg >> i) & 1U);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}
