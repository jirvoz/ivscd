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
    QVERIFY(cdMath.evaluate(QString("3 + 4")) == 7);
}

QTEST_APPLESS_MAIN(CDMathTests)

#include "test_cdmath.moc"
