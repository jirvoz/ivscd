#include <QString>
#include <QtTest>

#include "cdmath.h"

class CDMathTests : public QObject
{
    Q_OBJECT

public:
    CDMathTests();

private Q_SLOTS:
    void testCase1();
};

CDMathTests::CDMathTests()
{
}

void CDMathTests::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"
