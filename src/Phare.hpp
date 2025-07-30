#ifndef PHARE_HPP
#define PHARE_HPP

#include "pico/stdlib.h"
#include <vector>

struct SignalStep {
    uint32_t duration_us;
    bool led_on;
};

class Phare {
public:
    Phare(uint gpio, const std::vector<SignalStep>& pattern, uint64_t offset_us = 0);
    void update(uint64_t now);

private:
    uint gpio_;
    std::vector<SignalStep> pattern_;
    size_t current_step_;
    uint64_t next_change_us_;
};


std::vector<SignalStep> make_group_flashes(uint8_t count, uint32_t total_period_us);
std::vector<SignalStep> make_iso(uint32_t total_period_us);

#endif // PHARE_HPP
