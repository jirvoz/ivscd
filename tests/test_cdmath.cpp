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
    QCOMPARE(cdMath.evaluate(QString("3.5^2")), cdMath.power(3.5, 2));
    QCOMPARE(cdMath.evaluate(QString("3^2.5")), cdMath.power(3, 2.5));
    QCOMPARE(cdMath.evaluate(QString("3.5^4.5")), cdMath.power(3.5, 4.5));
}


QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"
