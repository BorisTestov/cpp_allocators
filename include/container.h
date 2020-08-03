#include <iostream>

template <typename T, typename allocator = std::allocator<T>>
class vector_container {
public:
  vector_container() = default;

  template <typename U, typename copy_allocator = std::allocator<T>>
  /**
   * @brief vector_container
   * Переопределение конструктора копирования
   */
  vector_container(const vector_container<U, copy_allocator> &) {}

  void increase_capacity() {
    T *old_container_data = _container_data;
    std::size_t old_container_capacity = _container_capacity;
    if (_container_capacity == 0) {
      _container_capacity = 1;
    } else {
      _container_capacity *= 2;
    }
    _container_data = _container_allocator.allocate(_container_capacity);
    {
      // move olda data to new memory
      T *old_data_pointer = old_container_data;
      T *new_data_pointer = _container_data;
      for (size_t i = 0; i < _container_size; i++) {
        _container_allocator.construct(new_data_pointer, *old_data_pointer);
        new_data_pointer++;
        old_data_pointer++;
      }
    }
    {
      // destruct old data
      T *old_data_pointer = old_container_data;
      for (size_t i = 0; i < _container_size; i++) {
        _container_allocator.destroy(old_data_pointer);
        old_data_pointer++;
      }
    }
    // deallocate old memory
    if (old_container_data != nullptr) {
      _container_allocator.deallocate(old_container_data,
                                      old_container_capacity);
    }
  }

  /**
   * @brief operator []
   * Переопределяем оператор []
   * @param index - индекс элемента
   * @return элемент, находящейся в контейнере по индексу index
   */
  T &operator[](size_t index) { return _container_data[index]; }

  /**
   * @brief push_back
   * Переопределение метода push_back
   * @param item - данные, которые кладудтся в контейнер
   */
  void push_back(T item) {
    if (_container_size == _container_capacity) {
      increase_capacity();
    }
    _container_size++;
    _container_data[_container_size - 1] = item;
  }

  size_t size() { return _container_size; }

  size_t capacity() { return _container_capacity; }

  bool empty() { return _container_size == 0; }

  T *begin() { return _container_data; }

  T *end() { return _container_data + _container_size; }

private:
  T *_container_data = nullptr;
  std::size_t _container_size = 0;
  std::size_t _container_capacity = 0;
  allocator _container_allocator;
};
