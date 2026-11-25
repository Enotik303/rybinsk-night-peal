#include "harness.hpp"
#include "make_peal.hpp"

#include "rostov/night.hpp"
#include "rostov/peal.hpp"

#include <vector>

using rostov::Peal;
using rostov::Stroke;
using rostov::ringNight;

namespace {

void emptyPartDoesNotBreakARepeat() {
    const Peal first = makePeal({Stroke{1, 2}});
    const Peal second = makePeal({Stroke{3, 4}, Stroke{5, 6}});
    const Peal empty;
    const std::vector<Peal> parts{first, empty, makePeal({Stroke{1, 2}}), second, makePeal({Stroke{3, 4}, Stroke{5, 6}}), first};
    const Peal night = ringNight(parts);
    EXPECT(night == first + second + first);
    EXPECT_EQ(night.size(), 4);
    EXPECT_EQ(night[0].bell, 1);
    EXPECT_EQ(night[1].bell, 3);
    EXPECT_EQ(night[2].bell, 5);
    EXPECT_EQ(night[3].bell, 1);
    EXPECT_EQ(static_cast<int>(night), 14);
}

void repeatIsThePreviousPartNotTheWholeNight() {
    const Peal one = makePeal({Stroke{1, 1}});
    const Peal doubled = one + one;
    const std::vector<Peal> growing{one, doubled};
    const Peal grown = ringNight(growing);
    EXPECT_EQ(grown.size(), 3);
    EXPECT_EQ(grown[0].bell, 1);
    EXPECT_EQ(grown[1].bell, 1);
    EXPECT_EQ(grown[2].bell, 1);

    const Peal other = makePeal({Stroke{2, 3}});
    const std::vector<Peal> separated{one, other, one};
    const Peal night = ringNight(separated);
    EXPECT(night == one + other + one);
    EXPECT_EQ(night.size(), 3);

    const std::vector<Peal> triple{one, one, one};
    EXPECT(ringNight(triple) == one);
    EXPECT_EQ(ringNight(triple).size(), 1);
}

void nightDoesNotChangeTheInput() {
    const Peal first = makePeal({Stroke{1, 2}});
    const Peal second = makePeal({Stroke{3, 4}});
    std::vector<Peal> parts{first, Peal(), second, second};
    const Peal night = ringNight(parts);
    EXPECT(night == first + second);
    EXPECT(parts.size() == 4);
    EXPECT(parts[0] == first);
    EXPECT_EQ(parts[1].size(), 0);
    EXPECT(parts[2] == second);
    EXPECT(parts[3] == second);
    EXPECT_EQ(static_cast<int>(parts[0]), 2);
}

void nightOfEmptiesIsEmpty() {
    const std::vector<Peal> parts(3);
    const Peal night = ringNight(parts);
    EXPECT_EQ(night.size(), 0);
    EXPECT_EQ(static_cast<int>(night), 0);

    const std::vector<Peal> nothing;
    EXPECT_EQ(ringNight(nothing).size(), 0);

    const Peal only = makePeal({Stroke{8, 5}, Stroke{1, 1}});
    const std::vector<Peal> single{Peal(), only, Peal()};
    EXPECT(ringNight(single) == only);
}

}  // namespace

void registerNightTests(std::vector<rostov_test::TestCase>& tests) {
    tests.push_back({"night / пустая партия не разрывает повтор", emptyPartDoesNotBreakARepeat});
    tests.push_back({"night / повтор — это соседняя партия, не весь перезвон", repeatIsThePreviousPartNotTheWholeNight});
    tests.push_back({"night / ночь не портит входной список", nightDoesNotChangeTheInput});
    tests.push_back({"night / ночь из пустых кусков пустая", nightOfEmptiesIsEmpty});
}
