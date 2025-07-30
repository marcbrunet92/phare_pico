#include "pico/stdlib.h"
#include "Phare.hpp"
#include <vector>

void start() {
    sleep_ms(500);

    for (int pin = 0; pin <= 21; ++pin) {
        gpio_put(pin, 1);  // Met la broche à l'état haut (3.3V)
    }

    sleep_ms(500);

    for (int pin = 0; pin <= 21; ++pin) {
        gpio_put(pin, 0);  // Met la broche à l'état bas (0V)
    }

    sleep_ms(500);

    for (int pin = 0; pin <= 21; ++pin) {
        gpio_put(pin, 1);  // Met la broche à l'état haut (3.3V)
        sleep_ms(100);
        gpio_put(pin, 0);  // Met la broche à l'état bas (0V)
    }
}

int main() {
    stdio_init_all();

    // Crée les 17 phares (GPIO 0 à 16)
    std::vector<Phare> phares = {
        Phare(0, make_group_flashes(3, 15000000), 13413),           // La Caravelle (Fl(3) 15s)
        Phare(1, make_group_flashes(1, 5000000), 1000000),      // Pointe Venus (Fl 5s)
        Phare(2, make_group_flashes(3, 15000000), 2000000),     // Bel Air (Fl(3) 15s)
        Phare(20, make_group_flashes(1, 5000000), 13431),           // Plateau du Four (Fl 5s)
        Phare(21, make_group_flashes(4, 15000000), 3000000),    // Grands Cardinaux (Fl(4) 15s)
        Phare(5, make_group_flashes(1, 5000000), 0),      // Eckmühl (Fl 5s)
        Phare(6, make_iso(4000000), 34143),                         // La Vieille (Iso 4s)
        Phare(7, make_group_flashes(4, 25000000), 34243),           // Île de Sein (Fl(4) 25s)
        Phare(8, make_group_flashes(3, 20000000), 85324),           // Ar Men (Fl(3) 20s)
        Phare(9, make_group_flashes(1, 5000000), 3000000),      // Pierres Noires (Fl 5s)
        Phare(10, make_group_flashes(3, 12000000), 234543),          // La Jument (Fl(3) 12s)
        Phare(11, make_group_flashes(2, 20000000), 247545),          // Le Stiff (Fl(2) 20s)
        Phare(12, make_group_flashes(5, 15000000), 4342),          // Le Four (Fl(5) 15s)
        Phare(13, make_group_flashes(1, 15000000), 0),          // Saint Matthieu (Fl 15s)
        Phare(14, make_group_flashes(2, 6000000), 50000),           // Petit Minou (Fl(2) 6s)
        Phare(16, make_group_flashes(2, 10000000), 0),          // Cap Fréhel (Fl(2) 10s)
        Phare(17, make_group_flashes(2, 10000000), 2000000)     // Grands Jardins (Fl(2) 10s) → déphasé
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