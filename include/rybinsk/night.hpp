#pragma once

#include "rybinsk/peal.hpp"

#include <vector>

namespace rybinsk {

// Собрать ночь из кусков в порядке списка.
// Пустой кусок пропускается и не разрывает соседство.
// Если кусок совпал с последним уже взятым — его не берут второй раз подряд.
// Входной список не меняется. Подробности и примеры — в README.
[[nodiscard]] Peal ringNight(const std::vector<Peal>& parts);

}  // namespace rybinsk
