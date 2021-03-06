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
    void testPower();
    void testUnaryMinus();
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
    QCOMPARE(cdMath.evaluate(QString("(3 - 7.25) * 2")), -8.5);
    QCOMPARE(cdMath.evaluate(QString("(3 -( 7.5 + 8) / 2) * 5")), -23.75);
    QCOMPARE(cdMath.evaluate(QString("3^2^3")), cdMath.power(3, cdMath.power(2, 3)));
}

void CDMathTests::testPower()
{
    QCOMPARE(cdMath.power(3.5, 2), 12.25);
    QCOMPARE(cdMath.power(4, 2.5), 32.0);
    QCOMPARE(cdMath.power(1852, 0), 1.0);
    QCOMPARE(cdMath.power(0.5, 2), 0.25);
    QCOMPARE(cdMath.power(2, cdMath.power(2, 3)), 256.0);
    QCOMPARE(cdMath.power(cdMath.power(2, 2), 3), 64.0);
    QCOMPARE(cdMath.power(2.5, 3.5), 24.70529422006);
    QCOMPARE(cdMath.power(-2, 3), -8.0);
    QCOMPARE(cdMath.power(-2, -3), -0.125);
    QCOMPARE(cdMath.power(2, -3), 0.125);
    QCOMPARE(cdMath.power(2.659, 4.68), 97.2034811748299);
    QCOMPARE(cdMath.power(2.5, -1.5), 0.2529822128134);
    QCOMPARE(cdMath.power(-2.5, -5), -0.01024);
}

void CDMathTests::testUnaryMinus()
{
    QCOMPARE(cdMath.evaluate(QString("-5")), -5.0);
    QCOMPARE(cdMath.evaluate(QString("3 + -5")), -2.0);
    QCOMPARE(cdMath.evaluate(QString("3-(1+1)-5")), -4.0);
    QCOMPARE(cdMath.evaluate(QString("(-1)*5")), -5.0);

    QEXPECT_FAIL("", "Doesn't work for whole parenthesis, only for numbers, \
jirvoz will fix it later", Continue);
    QCOMPARE(cdMath.evaluate(QString("-(1)+5")), 4.0);
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
