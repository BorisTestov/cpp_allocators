#include <iostream>
#include <list>
#include <algorithm>

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

  struct memory_chunk
  {
      pointer _data = static_cast<pointer>(::operator new(max_allocated_chunks * sizeof(value_type)));
      pointer _last_free = _data;
      size_t used = 0;
      memory_chunk()
      {
          if (not _data)
          {
              std::cerr << "bad allocation at " << __PRETTY_FUNCTION__ << std::endl;
              throw std::bad_alloc();
          }
      }
      ~memory_chunk()
      {
          ::operator delete(_data);
      }
  };
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
    if (n > max_allocated_chunks)
    {
        std::cerr << "bad allocation at " << __PRETTY_FUNCTION__ << std::endl;
        throw std::bad_alloc();
    }
    for(memory_chunk& c:_memory_pool)
    {
        if ((unsigned)(c._data + max_allocated_chunks - c._last_free) >= n)
        {
            return add_to_chunk(c, n);
        }
    }
    memory_chunk& c = _memory_pool.emplace_back();
    return add_to_chunk(c, n);
  }

  pointer add_to_chunk(memory_chunk& chunk, std::size_t n)
  {
      pointer result = chunk._last_free;
      chunk._last_free += n;
      chunk.used += n;
      return result;
  }

  /**
   * @brief max_size
   * Определяет, для какого максимального количества объектов можно
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
      auto dealloated_chunk = find_if(_memory_pool.begin(), _memory_pool.end(),
                                   [p](const memory_chunk& c) {
          return (p >= c._data and p <= (c._data + max_allocated_chunks));
      });
      if (dealloated_chunk == _memory_pool.end())
      {
          std::cerr << "bad allocation at " << __PRETTY_FUNCTION__ << std::endl;
          throw std::bad_alloc();
      }
      dealloated_chunk->used -= n;
      if (dealloated_chunk->used == 0)
      {
          _memory_pool.erase(dealloated_chunk);
      }
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
  std::list<memory_chunk> _memory_pool;
};
