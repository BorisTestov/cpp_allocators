#pragma once
#include <QtTest/QtTest>
#include "version.h"

class TestMain : public QObject
{
    Q_OBJECT
    private slots:
    void TestVersion();
};

QTEST_MAIN(TestMain)
