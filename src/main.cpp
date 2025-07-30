#include "pico/stdlib.h"
#include "Phare.hpp"
#include <vector>

void start() {
    sleep_ms(1000);

    for (int pin = 0; pin <= 21; ++pin) {
        gpio_put(pin, 1);  // Met la broche à l'état haut (3.3V)
    }

    sleep_ms(1000);

    for (int pin = 0; pin <= 21; ++pin) {
        gpio_put(pin, 0);  // Met la broche à l'état bas (0V)
    }

    sleep_ms(1000);

    for (int pin = 0; pin <= 21; ++pin) {
        gpio_put(pin, 1);  // Met la broche à l'état haut (3.3V)
        sleep_ms(500);
        gpio_put(pin, 0);  // Met la broche à l'état bas (0V)
    }
}

int main() {
    stdio_init_all();

    // Crée les 17 phares (GPIO 0 à 16)
    std::vector<Phare> phares = {
        Phare(0, make_group_flashes(3, 15000000)), // La Caravelle
        Phare(1, make_group_flashes(1, 5000000)),  // Pointe Venus
        Phare(2, make_group_flashes(3, 15000000)), // Bel Air
        Phare(20, make_group_flashes(1, 5000000)),  // Plateau du Four
        Phare(21, make_group_flashes(4, 15000000)), // Grands Cardinaux
        Phare(5, make_group_flashes(1, 5000000)),  // Eckmühl
        Phare(6, make_iso(4000000)),               // La Vieille
        Phare(7, make_group_flashes(4, 25000000)), // Île de Sein
        Phare(8, make_group_flashes(3, 20000000)), // Ar Men
        Phare(9, make_group_flashes(1, 5000000)),  // Pierres Noires
        Phare(10, make_group_flashes(3, 12000000)),// La Jument
        Phare(11, make_group_flashes(2, 20000000)),// Le Stiff
        Phare(12, make_group_flashes(5, 15000000)),// Le Four
        Phare(13, make_group_flashes(1, 15000000)),// Saint Matthieu
        Phare(14, make_group_flashes(2, 6000000)), // Petit Minou
        Phare(16, make_group_flashes(2, 10000000)),// Cap Fréhel
        Phare(17, make_group_flashes(2, 10000000)) // Grands Jardins
    };

    start();
    
    while (true) {
        uint64_t now = time_us_64();
        for (auto& phare : phares) {
            phare.update(now);
        }
        sleep_us(50); // très léger, permet d’économiser le CPU tout en gardant la précision
    }

    return 0;
}