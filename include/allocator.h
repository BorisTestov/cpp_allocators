#include <iostream>

template <typename T, std::size_t max_allocated_chunks = 1>
class logging_allocator {
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
    using other = logging_allocator<U, max_allocated_chunks>;
  };

  logging_allocator() = default;
  ~logging_allocator() = default;

  template <typename U, size_t copy_chunk_size>
  /**
   * @brief logging_allocator
   * Переопределение конструктора копирования
   * Обычно нужен, если аллокатор имеет внутренние состояния
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
    if (!_memory_pool) {
      _memory_pool =
          reinterpret_cast<pointer>(malloc(max_allocated_chunks * sizeof(T)));
    }
    if (!_memory_pool) {
      std::cerr << "bad allocation at " << __PRETTY_FUNCTION__ << std::endl;
      throw std::bad_alloc();
    }
    pointer chunk_pointer = _memory_pool + _chunks_counter * sizeof(T) * n;
    _chunks_counter += n;
    return chunk_pointer;
  }

  /**
   * @brief max_size
   * Определяет, какое для какого максимального количества объектов можно
   * аллоцировать память
   * @return Максимально допустимое количество объектов, используемых для
   * аллокации
   */
  size_t max_size() const noexcept { return max_allocated_chunks; }

  /**
   * @brief deallocate
   * Освобождение памяти после удаления объекта(ов)
   * @param p - указатель на начало блока памяти, которую нужно высвободить
   * @param n - размер элементов для освобождения. Рекомендовано передавать то
   * же значение, что и в allocate
   */
  void deallocate(pointer p, std::size_t n) {
    if (!p) {
      return;
    }
    _chunks_counter -= n;
    if (_chunks_counter != 0) {
      return;
    }
    free(_memory_pool);
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
    new (p) U(std::forward<Args>(args)...);
  }

  template <typename U>
  /**
   * @brief destroy
   * Уничтожает объект по переданной ссылке
   * @param p - Ссылка, указывающая на объект для уничтожения
   */
  void destroy(U *p) {
    if (!p) {
      std::cerr << "bad allocation at " << __PRETTY_FUNCTION__ << std::endl;
      throw std::bad_alloc();
    }
    p->~U();
  }

private:
  pointer _memory_pool = nullptr;
  size_t _chunks_counter = 0;
};
