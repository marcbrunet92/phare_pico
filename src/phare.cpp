#include "Phare.hpp"

Phare::Phare(uint gpio, const std::vector<SignalStep>& pattern)
    : gpio_(gpio), pattern_(pattern), current_step_(0), next_change_us_(time_us_64()) {
    gpio_init(gpio_);
    gpio_set_dir(gpio_, GPIO_OUT);
    gpio_put(gpio_, false);
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
