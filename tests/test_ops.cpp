#include "harness.hpp"
#include "make_peal.hpp"

#include "rostov/peal.hpp"

using rostov::Peal;
using rostov::PealError;
using rostov::Stroke;

namespace {

const Stroke& readAt(const Peal& peal, int index) {
    return peal[index];
}

void indexReadsAndWrites() {
    Peal peal(2);
    peal[0] = Stroke{1, 2};
    peal[1] = Stroke{3, 4};
    EXPECT_EQ(peal[0].bell, 1);
    EXPECT_EQ(peal[1].beats, 4);
    EXPECT_EQ(static_cast<int>(peal), 6);
}

void badIndexDoesNotChangePeal() {
    Peal peal = makePeal({Stroke{1, 2}, Stroke{3, 4}});
    EXPECT_THROW(peal[2], PealError);
    EXPECT_THROW(peal[-1], PealError);
    EXPECT_THROW((peal[5] = Stroke{9, 9}), PealError);
    EXPECT_EQ(peal.size(), 2);
    EXPECT_EQ(peal[0].bell, 1);
    EXPECT_EQ(peal[0].beats, 2);
    EXPECT_EQ(peal[1].bell, 3);
    EXPECT_EQ(static_cast<int>(peal), 6);

    const Peal empty;
    EXPECT_THROW(empty[0], PealError);
}

void constPealIsReadable() {
    const Peal peal = makePeal({Stroke{6, 1}, Stroke{7, 2}});
    EXPECT_EQ(readAt(peal, 1).bell, 7);
    EXPECT_EQ(readAt(peal, 1).beats, 2);
    EXPECT_THROW(readAt(peal, -1), PealError);
    EXPECT_EQ(peal.size(), 2);
}

void equalityComparesStrokesNotAddresses() {
    const Peal left = makePeal({Stroke{1, 2}, Stroke{3, 4}});
    const Peal right = makePeal({Stroke{1, 2}, Stroke{3, 4}});
    const Peal different_beat = makePeal({Stroke{1, 2}, Stroke{3, 5}});
    const Peal shorter = makePeal({Stroke{1, 2}});
    const Peal empty_left;
    const Peal empty_right;
    EXPECT(left == right);
    EXPECT(!(left != right));
    EXPECT(left != different_beat);
    EXPECT(left != shorter);
    EXPECT(empty_left == empty_right);
    EXPECT(left != empty_left);
    EXPECT(!(shorter == left));
}

void plusDoesNotTouchOperands() {
    const Peal left = makePeal({Stroke{1, 2}});
    const Peal right = makePeal({Stroke{3, 4}, Stroke{5, 6}});
    const Peal empty;
    const Peal sum = left + right;
    EXPECT_EQ(left.size(), 1);
    EXPECT_EQ(right.size(), 2);
    EXPECT_EQ(sum.size(), 3);
    EXPECT_EQ(sum[0].bell, 1);
    EXPECT_EQ(sum[0].beats, 2);
    EXPECT_EQ(sum[1].bell, 3);
    EXPECT_EQ(sum[2].bell, 5);
    EXPECT_EQ(sum[2].beats, 6);
    EXPECT(left + empty == left);
    EXPECT(empty + left == left);
    EXPECT(empty + empty == empty);
    EXPECT_EQ(static_cast<int>(sum), 12);
}

void compoundAssignChains() {
    Peal first = makePeal({Stroke{1, 1}});
    Peal second = makePeal({Stroke{2, 1}});
    Peal third = makePeal({Stroke{3, 1}});
    first += second += third;
    EXPECT_EQ(third.size(), 1);
    EXPECT_EQ(second.size(), 2);
    EXPECT_EQ(second[0].bell, 2);
    EXPECT_EQ(second[1].bell, 3);
    EXPECT_EQ(first.size(), 3);
    EXPECT_EQ(first[0].bell, 1);
    EXPECT_EQ(first[1].bell, 2);
    EXPECT_EQ(first[2].bell, 3);

    const int before = static_cast<int>(first);
    first += Peal();
    EXPECT_EQ(static_cast<int>(first), before);
    EXPECT_EQ(first.size(), 3);
}

void selfAppendDoublesThePeal() {
    Peal peal = makePeal({Stroke{1, 2}, Stroke{3, 4}});
    peal += peal;
    EXPECT_EQ(peal.size(), 4);
    EXPECT_EQ(peal[0].bell, 1);
    EXPECT_EQ(peal[0].beats, 2);
    EXPECT_EQ(peal[1].bell, 3);
    EXPECT_EQ(peal[2].bell, 1);
    EXPECT_EQ(peal[2].beats, 2);
    EXPECT_EQ(peal[3].bell, 3);
    EXPECT_EQ(peal[3].beats, 4);
    EXPECT_EQ(static_cast<int>(peal), 12);

    Peal& same = peal;
    peal += same;
    EXPECT_EQ(peal.size(), 8);
    EXPECT_EQ(peal[4].bell, 1);
    EXPECT_EQ(peal[7].beats, 4);
}

}  // namespace

void registerOpsTests(std::vector<rostov_test::TestCase>& tests) {
    tests.push_back({"ops / индекс читает и пишет удар", indexReadsAndWrites});
    tests.push_back({"ops / плохой индекс не меняет партию", badIndexDoesNotChangePeal});
    tests.push_back({"ops / константный перезвон читается", constPealIsReadable});
    tests.push_back({"ops / равны удары, а не адреса", equalityComparesStrokesNotAddresses});
    tests.push_back({"ops / сложение не портит слагаемые", plusDoesNotTouchOperands});
    tests.push_back({"ops / составное присваивание цепочкой", compoundAssignChains});
    tests.push_back({"ops / партия, дописанная к себе, удваивается", selfAppendDoublesThePeal});
}
