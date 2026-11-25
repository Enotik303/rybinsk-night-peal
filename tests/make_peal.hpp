#pragma once

#include "rybinsk/peal.hpp"

#include <initializer_list>
#include <vector>

inline rybinsk::Peal makePeal(std::initializer_list<rybinsk::Stroke> strokes) {
    const std::vector<rybinsk::Stroke> data(strokes);
    return rybinsk::Peal(data.data(), static_cast<int>(data.size()));
}
