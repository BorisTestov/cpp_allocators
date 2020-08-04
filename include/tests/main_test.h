#pragma once
#include "allocator.h"
#include "container.h"
#include "factorial.h"
#include "version.h"
#include <QtTest/QtTest>

class TestMain : public QObject {
  Q_OBJECT
private slots:
  void TestVersion();
  void TestFactorial();
  void TestAllocator();
  void TestContainer();
};

QTEST_MAIN(TestMain)
