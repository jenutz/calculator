#include "Calculator.h"
#include <cctype>
#include <algorithm>

void Calculator::percent() {push("%");}
void Calculator::division() {push("÷");}
void Calculator::multiplication() {push("×");}
void Calculator::minus() {push("-");}
void Calculator::plus() {push("+");}

QString Calculator::getResult() const{
    return result;
}

QString Calculator::getCalculation() const{
    return calculation;
}

void Calculator::push(QString val){
    if (calculation.isEmpty() && getPriority(val.back()) > 0)
        return;
    if (getPriority(calculation.back()) && getPriority(val.back()))
        calculation.back() = val.back();
    else
        calculation += val;
    emit calculationChanged();
}

void Calculator::brackets(){
    if (calculation.back()=='('){
        push("(");
        return;
    }
    if (calculation.count('(') > calculation.count(')'))
        push(")");
    else
        push("(");
}

void Calculator::pushSimple(QString val){
    if (val != "."){
        push(val);
        return;
    }
    int lastDot = calculation.lastIndexOf('.');
    if (lastDot == -1){
        push(val);
        return;
    }

    if (!std::all_of(calculation.constBegin() + lastDot + 1,
                    calculation.constEnd(),
                    [](const QChar &e){return e.isDigit();}))
    {
        push(".");
    }
}

void Calculator::plusMinus(){
    if (calculation.isEmpty())
        return;

    auto firstDigit= std::find_if(calculation.crbegin(), 
                              calculation.crend(),
                              [](auto &e){return e.isDigit();});

    if (firstDigit == calculation.crend())
        return;

    auto insertIt= std::find_if(firstDigit, 
                              calculation.crend(),
                              [](auto &e){return !e.isDigit();});

    qsizetype pos = std::distance(insertIt, calculation.crend());
    if (getPriority(*insertIt) == 2)
        calculation.insert(pos, "-");
    else if (getPriority(*insertIt) == 1){
        if (*insertIt == '-')
            calculation.removeAt(pos - 1);
        else
            calculation.replace(pos - 1, 1, "-");
    }
    else{
        calculation.insert(pos, "-");
    }
    emit calculationChanged();
}

void Calculator::cancel(){
    calculation.clear();
    result.clear();
    emit calculationChanged();
    emit resultChanged();
    return;
}

void Calculator::equal(){
    int i = 0;
    if (calculation.isEmpty())
        return;
    if (getPriority(calculation.back()) > 0 and calculation.back() != '%')
        return;

    QString expression = normalize(calculation);
    QStringList postfix = toPostfix(expression);
    double numericResult = calculate(postfix);
    result = QString::number(numericResult);
    emit resultChanged();
}

QString Calculator::normalize(QString expression){
    int i = 0;
    while (i < expression.length() - 1){
        if ((expression[i].isDigit() && expression[i+1] == '(') ||
            (expression[i+1].isDigit() && expression[i] == ')') ||
            (expression[i] == ')' && expression[i+1] == '('))
        {
            expression.insert(i + 1,'*');
        }
        else ++i;
    }
    if (expression[0] == '-')
        expression.insert(0,"0");

    expression.replace("(-","(0-");
    expression.replace("×","*");
    expression.replace("÷","/");
    return expression;
}

int Calculator::getPriority(QChar operation){
    char32_t op = operation.unicode();
    switch (op){
        case '*':
        case '/':
        case '%':
        case u'÷':
        case u'×':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
};

QStringList Calculator::toPostfix(const QString& infix){
    QStringList postfix;
    QStringList opstack;

    bool waiting = false;
    for (int i = 0; i < infix.length(); ++i){
        const QChar current = infix[i];
        if (current.isDigit() || current == '.'){
            if (!postfix.empty() && waiting && 
                (postfix.back().back().isDigit() || 
                postfix.back().back() == '.'))
            {
                postfix.back() += current;
            }
            else
                postfix.push_back(current);
            waiting = true;
            continue;
        }
        waiting = false;
        if (getPriority(current) > 0){
            while (!opstack.empty() && 
                getPriority(opstack.back()[0]) >= getPriority(current))
            {
                postfix.append(opstack.back());
                opstack.pop_back();
            }
            opstack.push_back(current);
        }
        else if (current == '(')
            opstack.push_back(current);
        else if (current == ')'){
            while (opstack.back() != '('){;
                postfix.push_back(opstack.back());
                opstack.pop_back();
            }
            opstack.pop_back();
        }
    }
    while (!opstack.empty()){
        postfix.push_back(opstack.back());
        opstack.pop_back();
    }
    return postfix;
}

double Calculator::calculate(QStringList expression){
    QStringList stack;
    while (!expression.empty()){
        QString op = expression.front();
        expression.pop_front();
        if (getPriority(op[0]) == 0){
            stack.push_back(op);
            continue;
        }

        double operand1 = stack.back().toDouble();
        stack.pop_back();
        double operand2 = 0;
        if (op == "%")
            operand2 = 100;
        else{
            operand2 = stack.back().toDouble();
            stack.pop_back();
        }
        double result = 0;
        switch (op[0].cell()){
            case '+':
                result = operand2 + operand1;
                break;
            case '-':
                result = operand2 - operand1;
                break;
            case '*':
                result = operand2 * operand1;
                break;
            case '/':
                result = operand2 / operand1;
                break;
            case '%':
                result = operand1 / operand2;
                break;
        }
        stack.push_back(QString::number(result));
    }
    return stack.back().toDouble();
}
