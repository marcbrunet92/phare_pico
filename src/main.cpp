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
        // --- Période 5s (4 phares) : déphasage de 1 250 000 µs entre chacun ---
        Phare(1, make_group_flashes(1, 5000000), 0),          // Pointe Venus     (Fl 5s)
        Phare(20, make_group_flashes(1, 5000000), 1250000),   // Plateau du Four  (Fl 5s)
        Phare(5, make_group_flashes(1, 5000000), 2500000),    // Eckmühl          (Fl 5s)
        Phare(9, make_group_flashes(1, 5000000), 3750000),    // Pierres Noires   (Fl 5s)

        // --- Période 15s (5 phares) : déphasage de 3 000 000 µs entre chacun ---
        Phare(0, make_group_flashes(3, 15000000), 0),         // La Caravelle     (Fl(3) 15s)
        Phare(2, make_group_flashes(3, 15000000), 3000000),   // Bel Air          (Fl(3) 15s)
        Phare(21, make_group_flashes(4, 15000000), 6000000),  // Grands Cardinaux (Fl(4) 15s)
        Phare(12, make_group_flashes(5, 15000000), 9000000),  // Le Four          (Fl(5) 15s)
        Phare(13, make_group_flashes(1, 15000000), 12000000), // Saint Matthieu   (Fl 15s)

        // --- Période 10s (2 phares) : déphasage de 5 000 000 µs ---
        Phare(16, make_group_flashes(2, 10000000), 0),        // Cap Fréhel       (Fl(2) 10s)
        Phare(17, make_group_flashes(2, 10000000), 5000000),  // Grands Jardins   (Fl(2) 10s)

        // --- Période 20s (2 phares) : déphasage de 10 000 000 µs ---
        Phare(8, make_group_flashes(3, 20000000), 0),         // Ar Men           (Fl(3) 20s)
        Phare(11, make_group_flashes(2, 20000000), 10000000), // Le Stiff         (Fl(2) 20s)

        // --- Phares uniques ---
        Phare(6, make_iso(4000000), 0),                       // La Vieille       (Iso 4s)
        Phare(7, make_group_flashes(4, 25000000), 0),         // Île de Sein      (Fl(4) 25s)
        Phare(10, make_group_flashes(3, 12000000), 0),        // La Jument        (Fl(3) 12s)
        Phare(14, make_group_flashes(2, 6000000), 0),         // Petit Minou      (Fl(2) 6s)
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