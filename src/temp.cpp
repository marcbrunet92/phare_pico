#include "pico/stdlib.h"

int main() {
    // Initialisation du SDK
    stdio_init_all();

    // GPIO 0 à 20 → configuration en sortie
    for (int pin = 0; pin <= 20; ++pin) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
        gpio_put(pin, 1);  // Met la broche à l'état haut (3.3V)
    }

    // Boucle infinie : on laisse les broches allumées
    while (true) {
        tight_loop_contents();  // Optimisation basse consommation
    }

    return 0;
}
