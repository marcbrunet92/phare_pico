#include "Phare.hpp"

Phare::Phare(uint gpio, const std::vector<SignalStep>& pattern, uint64_t offset_us)
    : gpio_(gpio), pattern_(pattern), current_step_(0) {

    gpio_init(gpio_);
    gpio_set_dir(gpio_, GPIO_OUT);

    // Calcul de l'instant de départ logique (décalé)
    uint64_t start_us = time_us_64() - offset_us;

    // Calcul de la durée d’un cycle complet
    uint64_t total_cycle_us = 0;
    for (const auto& step : pattern_) {
        total_cycle_us += step.duration_us;
    }

    // Position dans le cycle
    uint64_t elapsed_in_cycle = start_us % total_cycle_us;

    // Déterminer le step courant
    uint64_t acc = 0;
    for (size_t i = 0; i < pattern_.size(); ++i) {
        acc += pattern_[i].duration_us;
        if (elapsed_in_cycle < acc) {
            current_step_ = i;
            break;
        }
    }

    // Mettre la LED dans le bon état
    gpio_put(gpio_, pattern_[current_step_].led_on);

    // Déterminer quand faire le prochain changement
    uint64_t step_start_us = acc - pattern_[current_step_].duration_us;
    next_change_us_ = time_us_64() + (pattern_[current_step_].duration_us - (elapsed_in_cycle - step_start_us));
}

void Phare::update(uint64_t now) {
    if (now >= next_change_us_) {
        const auto& step = pattern_[current_step_];
        gpio_put(gpio_, step.led_on);
        next_change_us_ = now + step.duration_us;
        current_step_ = (current_step_ + 1) % pattern_.size();
    }
}

std::vector<SignalStep> make_group_flashes(uint8_t count, uint32_t total_period_us) {
    std::vector<SignalStep> pattern;
    const uint32_t flash_us = 300000;
    const uint32_t between_flashes_us = 500000;

    uint32_t used_us = 0;
    for (int i = 0; i < count; ++i) {
        pattern.push_back({flash_us, true});
        used_us += flash_us;
        if (i < count - 1) {
            pattern.push_back({between_flashes_us, false});
            used_us += between_flashes_us;
        }
    }

    // Extinction pour le reste du cycle
    if (used_us < total_period_us) {
        pattern.push_back({total_period_us - used_us, false});
    }
    return pattern;
}

std::vector<SignalStep> make_iso(uint32_t total_period_us) {
    return {
        {total_period_us / 2, true},
        {total_period_us / 2, false}
    };
}
