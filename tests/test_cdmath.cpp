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
}

QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"
