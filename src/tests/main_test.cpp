#include "main_test.h"
#include "moc_main_test.cpp"

void TestMain::TestVersion() { QCOMPARE((int)version().find("0.0."), 0); }

void TestMain::TestFactorial() {
  QCOMPARE(factorial(0), 1);
  QCOMPARE(factorial(5), 120);
  QVERIFY_EXCEPTION_THROWN(factorial(-1), std::invalid_argument);
}
