#include <QtTest>
#include <QString>

#include "cdmath.h"

class CDMathTests : public QObject
{
    Q_OBJECT

    CDMath cdMath;

public:
    CDMathTests();

private Q_SLOTS:
    void testEvaluate();
    void testAbs();
};

CDMathTests::CDMathTests()
{
    cdMath = CDMath();
}

void CDMathTests::testEvaluate()
{
    QCOMPARE(cdMath.evaluate(QString("3 + 4")), 7.0);
    QCOMPARE(cdMath.evaluate(QString("3 + 4 * 2")), 11.0);
    QCOMPARE(cdMath.evaluate(QString("3 - 5 / 2")), 0.5);
    QCOMPARE(cdMath.evaluate(QString("3^2^3")), 6561.0);
    QCOMPARE(cdMath.evaluate(QString("(3 - 7.25) * 2")), -8.5);
    QCOMPARE(cdMath.evaluate(QString("(3 -( 7.5 + 8) / 2) * 5")), -23.75);
}

void CDMathTests::testAbs()
{
    QCOMPARE(cdMath.evaluate(QString("abs(4)")), 4.0);
    QCOMPARE(cdMath.evaluate(QString("abs(0)")), 0.0);
    QCOMPARE(cdMath.evaluate(QString("abs(0-4)")), 4.0);
    QCOMPARE(cdMath.evaluate(QString("2 + abs(1-4) - 3")), 2.0);
    QCOMPARE(cdMath.evaluate(QString("2 + abs(1-4) * 3")), 11.0);
}

QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"
