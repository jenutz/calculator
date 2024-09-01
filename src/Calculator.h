#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <qqml.h>

class Calculator : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QString result READ getResult NOTIFY resultChanged)
        Q_PROPERTY(QString calculation READ getCalculation NOTIFY calculationChanged)
        Q_PROPERTY(bool secret READ getSecret WRITE setSecret)
   
    public:
        Q_INVOKABLE void pushSimple(QString);
        Q_INVOKABLE void brackets();
        Q_INVOKABLE void percent();
        Q_INVOKABLE void division();
        Q_INVOKABLE void multiplication();
        Q_INVOKABLE void minus();
        Q_INVOKABLE void plus();
        Q_INVOKABLE void plusMinus();
        Q_INVOKABLE void cancel();
        Q_INVOKABLE void equal();

    public:
        static double calculate(QStringList);
        static QString normalize(QString);
        static int getPriority(QChar operation);
        static QStringList toPostfix(const QString&);
        
        void push(QString val);


    private:
        QString result = "0";
        QString calculation = ""; 
        bool secret = false; 

    public:
        QString getResult() const;
        QString getCalculation() const;
        bool getSecret() const {return secret;};
        void setSecret(bool val){secret = val;};
    signals:
        void resultChanged();
        void calculationChanged();
};

#endif // BACKEND_H
