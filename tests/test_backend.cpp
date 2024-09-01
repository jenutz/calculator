#include <QtTest>
#include <QStringList>
#include "../src/Calculator.h"

class BackendTest : public QObject {
    Q_OBJECT
private slots:
    void testCalculate();
    void testNormalize();
    void testToPostfix();
    void testEqual();
};


void BackendTest::testNormalize() {
    QCOMPARE(Calculator::normalize("12"), "12");
    QCOMPARE(Calculator::normalize("(12)"), "(12)");
    QCOMPARE(Calculator::normalize("(1)(2)"), "(1)*(2)");
    QCOMPARE(Calculator::normalize("1(2)"), "1*(2)");
    QCOMPARE(Calculator::normalize("(1)2"), "(1)*2");
    QCOMPARE(Calculator::normalize("(1)2(3)"), "(1)*2*(3)");
    QCOMPARE(Calculator::normalize("1(2)3"), "1*(2)*3");

    QCOMPARE(Calculator::normalize("-1"), "0-1");
    QCOMPARE(Calculator::normalize("-1(2)"), "0-1*(2)");
    QCOMPARE(Calculator::normalize("-1(2)"), "0-1*(2)");
    QCOMPARE(Calculator::normalize("2+2(2)"), "2+2*(2)");

    QCOMPARE(Calculator::normalize("(-1)(-1)"), "(0-1)*(0-1)");
    QCOMPARE(Calculator::normalize("10*(-(-1)(-1))"), "10*(0-(0-1)*(0-1))");
}

void BackendTest::testToPostfix() {
    QCOMPARE(Calculator::toPostfix("1+2"), QStringList({"1","2","+"}));
    QCOMPARE(Calculator::toPostfix("1+2+3"), QStringList({"1","2","+","3","+"}));
    QCOMPARE(Calculator::toPostfix("1+2+3+4"), QStringList({"1","2","+","3","+","4","+"}));

    QCOMPARE(Calculator::toPostfix("1-2"), QStringList({"1","2","-"}));
    QCOMPARE(Calculator::toPostfix("1-2-3"), QStringList({"1","2","-","3","-"}));
    QCOMPARE(Calculator::toPostfix("1-2-3-4"), QStringList({"1","2","-","3","-","4","-"}));

    QCOMPARE(Calculator::toPostfix("1*2"), QStringList({"1","2","*"}));
    QCOMPARE(Calculator::toPostfix("1*2*3"), QStringList({"1","2","*","3","*"}));
    QCOMPARE(Calculator::toPostfix("1*2*3*4"), QStringList({"1","2","*","3","*","4","*"}));

    QCOMPARE(Calculator::toPostfix("1/2"), QStringList({"1","2","/"}));
    QCOMPARE(Calculator::toPostfix("1/2/3"), QStringList({"1","2","/","3","/"}));
    QCOMPARE(Calculator::toPostfix("1/2/3/4"), QStringList({"1","2","/","3","/","4","/"}));

    QCOMPARE(Calculator::toPostfix("1-2+3"), QStringList({"1","2","-","3","+"}));
    QCOMPARE(Calculator::toPostfix("1+2-3+4"), QStringList({"1","2","+","3","-","4","+"}));
    QCOMPARE(Calculator::toPostfix("1-2+3-4"), QStringList({"1","2","-","3","+","4","-"}));

    QCOMPARE(Calculator::toPostfix("1/2*3"), QStringList({"1","2","/","3","*"}));
    QCOMPARE(Calculator::toPostfix("1*2/3*4"), QStringList({"1","2","*","3","/","4","*"}));
    QCOMPARE(Calculator::toPostfix("1/2*3/4"), QStringList({"1","2","/","3","*","4","/"}));

    QCOMPARE(Calculator::toPostfix("2+2*2"), QStringList({"2","2","2","*","+"}));
    QCOMPARE(Calculator::toPostfix("2+2*(2)"), QStringList({"2","2","2","*","+"}));
    QCOMPARE(Calculator::toPostfix("(2+2)*2"), QStringList({"2","2","+","2","*"}));

    QCOMPARE(Calculator::toPostfix("1111+2222"), QStringList({"1111","2222","+"}));
    QCOMPARE(Calculator::toPostfix("0-1111+2222"), QStringList({"0","1111","-","2222","+"}));
    QCOMPARE(Calculator::toPostfix("1111-2222"), QStringList({"1111","2222","-"}));
    QCOMPARE(Calculator::toPostfix("1111-(0-1)*2222"), QStringList({"1111","0","1","-", "2222", "*","-"}));
}

void BackendTest::testCalculate(){
}

void BackendTest::testEqual(){
    auto equal = [](const QString &calculation){
        QString expression = Calculator::normalize(calculation);
        QStringList postfix = Calculator::toPostfix(expression);
        double numericResult= Calculator::calculate(postfix);

        QString result = QString::number(numericResult,'G');
        return result;
    };

    QCOMPARE(equal("(1)(1)"),"1");
    QCOMPARE(equal("(1)(1)"),"1");
    QCOMPARE(equal("10-1*10"),"0");
    QCOMPARE(equal("3333333333333333333333"),"3.33333E+21");



}

QTEST_MAIN(BackendTest)
#include "test_backend.moc"

