#include <iostream>
//#define USE_PRETTY

template <typename T, std::size_t chunk_size = 1> class logging_allocator {
public:
  // Define some basic member types
  // https://en.cppreference.com/w/cpp/memory/allocator
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;

  template <typename U>
  /**
   * @brief The rebind struct
   * Определяем структуру rebind, которая используется,
   * если аллокатору необходимо будет аллоцировать объекты, отличные от типа T
   */
  struct rebind {
    using other = logging_allocator<U, chunk_size>;
  };

  logging_allocator() = default;
  ~logging_allocator() = default;

  template <typename U, size_t copy_chunk_size>
  /**
   * @brief logging_allocator
   * Переопределение конструктора копирования
   * Обчно нужен, если аллокатор имеет внутренние состояния
   */
  logging_allocator(const logging_allocator<U, copy_chunk_size> &) {}

  /**
   * @brief allocate
   * Выделение памяти для создания объекта(ов)
   * @param n - количество элементов
   * Выделение памяти для n элементов типа T
   * @return ссылка на начальный элемент (типа T) выделенного блока памяти
   */
  pointer allocate(std::size_t n) {
    std::cout << "allocate: " << n << std::endl;
    if (!_memory_pool) {
      _memory_pool = reinterpret_cast<pointer>(malloc(chunk_size * sizeof(T)));
    }
    if (!_memory_pool) {
      throw std::bad_alloc();
    }
    pointer chunk_pointer = _memory_pool + _chunks_counter;
    _chunks_counter += n;
    return chunk_pointer;
  }

  size_t max_size() const noexcept { return chunk_size; }

  /**
   * @brief deallocate
   * Освобождение памяти после удаления объекта(ов)
   * @param p - указатель на начало блока памяти, которую нужно высвободить
   * @param n - размер элементов для освобождения. Рекомендовано передавать то
   * же значение, что и в allocate
   */
  void deallocate(pointer p, std::size_t n) {
    if (!p)
      return;
    _chunks_counter -= n;
    if (_chunks_counter != 0) // Wait untill all chunks were gone
      return;
    free(_memory_pool);
    std::cout << "Memory freed" << std::endl;
    _memory_pool = nullptr;
  }

  template <typename U, typename... Args>
  /**
   * @brief construct
   * Создание элемента типа U по ссылке на уже освобожденную память
   * @param p - Ссылка на уже выделенную память для создания объекта
   * @param args - аргументы, передаваемые в конструктор
   */
  void construct(U *p, Args &&... args) {
#ifndef USE_PRETTY
    std::cout << "construct" << std::endl;
#else
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    new (p) U(std::forward<Args>(args)...);
  }

  template <typename U>
  /**
   * @brief destroy
   * Уничтожает объект по переданной ссылке
   * @param p - Ссылка, указывающая на объект для уничтожения
   */
  void destroy(U *p) {
#ifndef USE_PRETTY
    std::cout << "destroy" << std::endl;
#else
    std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
    if (!p) {
      throw std::bad_alloc(); // Double destruction
    }
    p->~U();
  }

private:
  pointer _memory_pool = nullptr;
  size_t _chunks_counter = 0;
};
