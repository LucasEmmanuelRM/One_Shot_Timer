#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#define BUTTON_A 5
#define LED_G 11
#define LED_B 12
#define LED_R 13

static volatile uint32_t last_time = 0;
static volatile uint8_t aux = 0;
static volatile bool button_block = 0; // Para impedir que o botão acione os LEDs novamente
static volatile uint8_t leds[] = {LED_R, LED_B, LED_G}; // Vetor de LEDs a ser percorrido para apagar um a um

void inicializar_pinos();
static void gpio_irq_handler(uint gpio, uint32_t events);
int64_t turn_off_callback(alarm_id_t id, void *user_data);

int main() {
    stdio_init_all();
    inicializar_pinos();

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        sleep_ms(100);
    }
}


int64_t turn_off_callback(alarm_id_t id, void *user_data) {    
    gpio_put(leds[aux], 0);
    aux++;

    if (aux < 3)
        add_alarm_in_ms(3000, turn_off_callback, NULL, false); // Recursividade para apagar os LEDs um a um
    else
        button_block = 0; // Libera o botão, permitindo que os LEDs se acendam novamente ao ser pressionado

    return 0;
}


void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if ((current_time - last_time > 300000) && !button_block) {  // 300ms debounce
        last_time = current_time;
        button_block = 1; // Realiza o bloqueio do botão até que todo LED se apague

        gpio_put(LED_G, 1); // Verde
        gpio_put(LED_B, 1); // Ciano
        gpio_put(LED_R, 1); // Branco

        aux = 0;
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}


void inicializar_pinos() {
    // Inicializa LEDs
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_put(LED_G, 0);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);
    gpio_put(LED_B, 0);

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_put(LED_R, 0);

    // Inicializa botão
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
}
