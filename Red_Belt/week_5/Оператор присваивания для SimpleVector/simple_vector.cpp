#include <numeric>
#include <vector>
#include <tuple>

#include "simple_vector.h"
#include "test_runner.h"

void TestCopyAssignment(){
    SimpleVector<int> numbers(10);
    std::iota(numbers.begin(), numbers.end(), 1);

    SimpleVector<int> dest;
    ASSERT_EQUAL(dest.Size(), 0u);

    dest = numbers;
    ASSERT_EQUAL(dest.Size(), numbers.Size());
    ASSERT(dest.Capacity() >= dest.Size());
    ASSERT(std::equal(dest.begin(), dest.end(), numbers.begin()));
}

int main(){
    TestRunner tr;
    RUN_TEST(tr, TestCopyAssignment);
}

