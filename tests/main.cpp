#include "harness.hpp"

#include <vector>

void registerLifeTests(std::vector<rostov_test::TestCase>& tests);
void registerAssignTests(std::vector<rostov_test::TestCase>& tests);
void registerOpsTests(std::vector<rostov_test::TestCase>& tests);
void registerNightTests(std::vector<rostov_test::TestCase>& tests);

int main() {
    std::vector<rostov_test::TestCase> tests;
    registerLifeTests(tests);
    registerAssignTests(tests);
    registerOpsTests(tests);
    registerNightTests(tests);
    return rostov_test::runAll(tests);
}
