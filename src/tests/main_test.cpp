#include "main_test.h"
#include "moc_main_test.cpp"

void TestMain::TestVersion() { QCOMPARE((int)version().find("0.0."), 0); }

void TestMain::TestFactorial()
{
  QCOMPARE(factorial(0), 1);
  QCOMPARE(factorial(5), 120);
  QVERIFY_EXCEPTION_THROWN(factorial(-1), std::invalid_argument);
}

void TestMain::TestAllocator()
{
    std::map<int, std::size_t, std::less<int>, logging_allocator<int, 10>>
            test_map;
    for (int i = 0; i < 10; i++)
    {
        test_map[i] = factorial(i);
    }
  for (int i = 0; i < 10; i++)
  {
    QCOMPARE((int)test_map[i], factorial(i));
  }
  test_map.erase(5);
  test_map[5] = factorial(5);
  for (int i = 0; i < 10; i++)
  {
    QCOMPARE((int)test_map[i], factorial(i));
  }
}

void TestMain::TestContainer()
{
  vector_container<int> container;
  for (int i = 0; i < 10; i++)
  {
    container.push_back(factorial(i));
  }
  for (int i = 0; i < 10; i++)
  {
    QCOMPARE(container[i], factorial(i));
  }
}
