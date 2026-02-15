#include <stdint.h>

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Array {
   private:
    std::unique_ptr<T[]> _array{};
    size_t _size_array{}, _current_size{};
    void Init(uint64_t size) {
        _size_array = size;
        _array = std::unique_ptr<T[]>(new T[_size_array]);
    }

   public:
    Array(T* array, uint64_t size) {
        Init(size);
        for (size_t idx{}; idx < size; ++idx) {
            _array[idx] = array[idx];
        }
        _current_size = size;
    }

    Array(std::initializer_list<T> list) {
        Init(list.size());
        uint64_t idx{};
        for (const T& item : list) {
            _array[idx++] = item;
        }
        _current_size = list.size();
    }

    Array(size_t size) {
        Init(size);
        for (size_t idx{}; idx <= _size_array; ++idx) {
            _array[idx] = idx + 1;
        }
        _current_size = _size_array;
    }

    void push(T value) {
        if (_current_size >= _size_array) return;
        _array[_current_size++] = value;
    }

    ~Array() = default;

    void showArray() const {
        for (size_t idx{}; idx < _size_array; ++idx) {
            std::cout << _array[idx] << " ";
        }
    }
};

int main() {
    size_t count_numbers{};
    std::cin >> count_numbers;
    Array<int> array(count_numbers);
    array.showArray();

    return 0;
}