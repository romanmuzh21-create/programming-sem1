#include <stdio.h>
#include <stdint.h>

// Прототипи функцій пакування та розпакування
uint16_t pack_telemetry(uint16_t adc_value, uint8_t data_ready, uint8_t chip_temp);
void     unpack_telemetry(uint16_t packet, uint16_t *adc_value, uint8_t *data_ready, uint8_t *chip_temp);
void     print_binary16(uint16_t val);

int main(void) {
    unsigned int in_adc, in_ready, in_temp;

    printf("Введіть значення АЦП (0..1023): ");
    if (scanf("%u", &in_adc) != 1 || in_adc > 1023) {
        fprintf(stderr, "Помилка: значення АЦП має бути в межах 0..1023.\n");
        return 1;
    }

    printf("Введіть прапорець готовності даних (0 або 1): ");
    if (scanf("%u", &in_ready) != 1 || in_ready > 1) {
        fprintf(stderr, "Помилка: готовність даних має бути 0 або 1.\n");
        return 1;
    }

    printf("Введіть температуру чіпа (0..31): ");
    if (scanf("%u", &in_temp) != 1 || in_temp > 31) {
        fprintf(stderr, "Помилка: температура чіпа має бути в межах 0..31.\n");
        return 1;
    }

    // Пакування у 16-бітне слово
    uint16_t packet = pack_telemetry((uint16_t)in_adc, (uint8_t)in_ready, (uint8_t)in_temp);

    printf("\n--- Сформований пакет телеметрії ---\n");
    printf("HEX: 0x%04X (DEC: %u)\n", packet, packet);
    print_binary16(packet);

    // Розпакування зі слова назад у змінні
    uint16_t out_adc = 0;
    uint8_t out_ready = 0;
    uint8_t out_temp = 0;

    unpack_telemetry(packet, &out_adc, &out_ready, &out_temp);

    printf("\n--- Відновлені параметри після розпакування ---\n");
    printf("Значення АЦП:      %u (початкове: %u)\n", out_adc, in_adc);
    printf("Готовність даних:  %u (початкове: %u)\n", out_ready, in_ready);
    printf("Температура чіпа:  %u (початкове: %u)\n", out_temp, in_temp);

    return 0;
}

uint16_t pack_telemetry(uint16_t adc_value, uint8_t data_ready, uint8_t chip_temp) {
    uint16_t packet = 0;
    packet |= (adc_value & 0x03FFU);             // Біти 0..9 (10 біт)
    packet |= ((uint16_t)(data_ready & 0x01U) << 10); // Біт 10 (1 біт)
    packet |= ((uint16_t)(chip_temp & 0x1FU) << 11);  // Біти 11..15 (5 біт)
    return packet;
}

void unpack_telemetry(uint16_t packet, uint16_t *adc_value, uint8_t *data_ready, uint8_t *chip_temp) {
    *adc_value  = packet & 0x03FFU;
    *data_ready = (uint8_t)((packet >> 10) & 0x01U);
    *chip_temp  = (uint8_t)((packet >> 11) & 0x1FU);
}

void print_binary16(uint16_t val) {
    printf("BIN: ");
    for (int i = 15; i >= 0; i--) {
        printf("%u", (val >> i) & 1U);
        if (i == 11 || i == 10) {
            printf(" | "); // Візуальне розділення полів пакета: [Temp 5b] | [Ready 1b] | [ADC 10b]
        }
    }
    printf("  ([Temp 15..11] | [Ready 10] | [ADC 9..0])\n");
}
