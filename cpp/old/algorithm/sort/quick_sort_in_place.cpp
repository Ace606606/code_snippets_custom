#include <algorithm>
#include <vector>

static size_t partition(std::vector<long long>& vector, size_t begin,
                        size_t end) {
    long long pivot = vector[end];

    size_t i = begin - 1;

    for (size_t j = begin; j <= (end - 1); ++j) {
        if (vector[j] <= pivot) {
            ++i;

            std::swap(vector[i], vector[j]);
        }
    }

    std::swap(vector[i + 1], vector[end]);

    return (i + 1);
}

static void quick_sort_in_place(std::vector<long long>& vector, size_t begin,

                                size_t end) {
    if (begin < end) {
        size_t pivot = partition(vector, begin, end);

        quick_sort_in_place(vector, begin, pivot - 1);

        quick_sort_in_place(vector, pivot + 1, end);
    }
}

void quick_sort_wrapper(std::vector<long long>& vector) {
    quick_sort_in_place(vector, 0, vector.size() - 1);
}
