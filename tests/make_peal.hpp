#pragma once

#include "rostov/peal.hpp"

#include <initializer_list>
#include <vector>

inline rostov::Peal makePeal(std::initializer_list<rostov::Stroke> strokes) {
    const std::vector<rostov::Stroke> data(strokes);
    return rostov::Peal(data.data(), static_cast<int>(data.size()));
}
