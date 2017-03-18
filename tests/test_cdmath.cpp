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
    void testAdd();
    void testEvaluate();
};

CDMathTests::CDMathTests()
{
    cdMath = CDMath();
}

void CDMathTests::testEvaluate()
{
    QVERIFY(cdMath.Evaluate(QString("3 + 4")) == 7);
}

void CDMathTests::testAdd()
{
    QVERIFY(CDMath::Add(1, 2) == 3);
    QVERIFY(CDMath::Add(-3, 2) == -1);
    QVERIFY(CDMath::Add(-3.5, 2.5) == -1);
}

QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"
