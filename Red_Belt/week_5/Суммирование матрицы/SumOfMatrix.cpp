#include <vector>
#include <future>
#include <numeric>
#include <cstdint>

#include "test_runner.h"


template <typename Iterator>
class IteratorRange
{
public:
    IteratorRange(Iterator begin, Iterator end)
        : first(begin)
        , last(end)
        , size_(distance(first, last))
    {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return size_;
    }

private:
    Iterator first, last;
    size_t size_;
};

template <typename Iterator>
class Paginator
{
private:
    std::vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        for (size_t left = std::distance(begin, end); left > 0; ) {
            size_t current_page_size = std::min(page_size, left);
            Iterator current_page_end = std::next(begin, current_page_size);
            pages.push_back({ begin, current_page_end });

            left -= current_page_size;
            begin = current_page_end;
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

template <typename MatrixConteiner>
int64_t SumMatrix(const MatrixConteiner& matrix) {
    int64_t sum = 0;
    for (const auto& row : matrix) {
        for (const auto item : row) {
            sum += item;
        }
    }

    return sum;
}

int64_t CalculateMatrixSum(const std::vector<std::vector<int>>& matrix) {
    std::vector<std::future<int64_t>> futures;
    for (auto& page : Paginate(matrix, 2000)){
        futures.push_back(
            std::async([=] {return SumMatrix(page);})
        );
    }

    int64_t result = 0;
    for (auto& f : futures){
        result += f.get();
    }

    return result;
}

void TestCalculateMatrixSum() {
    const std::vector<std::vector<int>> matrix = 
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);

    const std::vector<std::vector<int>> second =
    {
        {1}
    };
    ASSERT_EQUAL(CalculateMatrixSum(second), 1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
