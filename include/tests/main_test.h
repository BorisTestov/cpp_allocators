#pragma once
#include "factorial.h"
#include "version.h"
#include <QtTest/QtTest>

class TestMain : public QObject {
  Q_OBJECT
private slots:
  void TestVersion();
  void TestFactorial();
};

QTEST_MAIN(TestMain)
