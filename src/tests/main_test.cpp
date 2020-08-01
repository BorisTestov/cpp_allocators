#include "main_test.h"
#include "moc_main_test.cpp"

void TestMain::TestVersion()
{
    QCOMPARE((int)version().find("0.0."), 0);
}
