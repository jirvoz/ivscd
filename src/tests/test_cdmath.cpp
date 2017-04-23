#include <QtTest>
#include <QString>
#include <cmath>

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

    void testSDev();

    void testCmathFunctions();
    void testExceptions();

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
    QCOMPARE(cdMath.evaluate(QString(" 5 / 2 - 3")), -0.5);
    QCOMPARE(cdMath.evaluate(QString("5 % 2 - 3")), -2.0);
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
    QCOMPARE(cdMath.evaluate(QString("-(1)+5")), 4.0);
    QCOMPARE(cdMath.evaluate(QString("- 1 + 5")), 4.0);
    QCOMPARE(cdMath.evaluate(QString("- (1 + 5)")), -6.0);
}

void CDMathTests::testAbs()
{
    QCOMPARE(cdMath.evaluate(QString("abs(4)")), 4.0);
    QCOMPARE(cdMath.evaluate(QString("abs(0)")), 0.0);
    QCOMPARE(cdMath.evaluate(QString("abs(0-4)")), 4.0);
    QCOMPARE(cdMath.evaluate(QString("2 + abs(1-4) - 3")), 2.0);
    QCOMPARE(cdMath.evaluate(QString("2 + abs(1-4) * 3")), 11.0);
}


void CDMathTests::testSDev()
{
    double items[3] = {5.0, 3, 12.0};
    QCOMPARE(cdMath.standardDeviation(3, items), 4.72581562625);

    double items2[6] = {60.654, 3.6, 12.25, 42, 10, -5.2};
    QCOMPARE(cdMath.standardDeviation(6, items2), 25.2942318062);

    double items3[5] = {42, 42, 42, 42, 42};
    QCOMPARE(cdMath.standardDeviation(5, items3), 0.00000000000);

    double items4[5] = {-60, 1, 42, 26, 3.1415926535};
    QCOMPARE(cdMath.standardDeviation(5, items4), 38.7987949232);

    double items5[5] = {12, 13.568, 23, 120, 3.1415926535};
    QCOMPARE(cdMath.standardDeviation(5, items5), 48.399698828);
}

void CDMathTests::testCmathFunctions()
{
    QCOMPARE(cdMath.evaluate(QString("sin(5)")), sin(5));
    QCOMPARE(cdMath.evaluate(QString("cos(5)")), cos(5));
    QCOMPARE(cdMath.evaluate(QString("tan(5)")), tan(5));
    QCOMPARE(cdMath.evaluate(QString("tg(5)")), tan(5));
    QCOMPARE(cdMath.evaluate(QString("ln(5)")), log(5));
    QCOMPARE(cdMath.evaluate(QString("log(5)")), log10(5));
}

void CDMathTests::testExceptions()
{
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("1/0")), MathException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("1%0")), MathException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("ln(0)")), MathException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("log(-1)")), MathException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("1 + 8.9.9")), SyntaxException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("1 + 8 9")), SyntaxException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("1+*8")), SyntaxException);
    QVERIFY_EXCEPTION_THROWN(cdMath.evaluate(QString("")), SyntaxException);

}

QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"

