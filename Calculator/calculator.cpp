#include "calculator.h"
#include <QtWidgets>
#include <cmath>
Calculator::Calculator(QWidget * pwgt)
    : QWidget(pwgt)
{
    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);

    QChar aButtons[4][4] = {{'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'1', '2', '3', '-'},
                            {'0', '.', '=', '+'}
                           };

    //Layout setup
    QGridLayout * ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(createButton("CE"), 1, 3);
    ptopLayout->addWidget(createButton("cos"), 1, 1);
    ptopLayout->addWidget(createButton("sin"), 1, 0);


    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
        }
    }
    setLayout(ptopLayout);
}

Calculator::~Calculator()
{
}

QPushButton * Calculator::createButton(const QString & str)
{
    QPushButton * pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}

void Calculator::calculate()
{
    double dOperand2 = m_stk.pop().toDouble();
    qDebug() << dOperand2 << "double2";
    QString strOperation = m_stk.pop();
    qDebug() << strOperation << "string";
    double dResult = 0;

    if (strOperation == "cos" || strOperation == "sin")
    {
        if (strOperation == "cos")
        {
            dResult = cos(dOperand2);
            qDebug() << "cos : " << dResult;
        }
        if (strOperation == "sin")
        {
            dResult = sin(dOperand2);
            qDebug() << "sin : " << dResult;
        }
    }
    else
    {
        double dOperand1 = m_stk.pop().toDouble();
        qDebug() << dOperand1 << "double1";


        if (strOperation == "+")
        {
            dResult = dOperand1 + dOperand2;
            qDebug() << "+ : " << dResult;
        }
        if (strOperation == "-")
        {
            dResult = dOperand1 - dOperand2;
            qDebug() << "- : " << dResult;
        }
        if (strOperation == "/")
        {
            dResult = dOperand1 / dOperand2;
            qDebug() << "/ : " << dResult;
        }
        if (strOperation == "*")
        {
            dResult = dOperand1 * dOperand2;
            qDebug() << "* : " << dResult;
        }
    }

    m_plcd->display(dResult);
}

void Calculator::slotButtonClicked()
{
    QString str = ((QPushButton *) sender())->text();
    qDebug() << str;
    if (str == "CE")
    {
        m_stk.clear();
        qDebug() << m_stk.count() << ": 6st";
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if (str.contains(QRegExp("[0-9]")))
    {
        m_strDisplay += str;
        qDebug() << m_strDisplay;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if (str == ".")
    {
        m_strDisplay += str;
        qDebug() << m_strDisplay;
        m_plcd->display(m_strDisplay);
    }
    else
    {
        if (m_stk.count() >= 2)
        {
            m_stk.push(QString().setNum(m_plcd->value()));
            qDebug() << str << ": 2! ! !";
            qDebug() << m_stk.count() << ": 1st";
            calculate();
            m_stk.clear();
            qDebug() << m_stk.count() << ": 2st";
            m_stk.push(QString().setNum(m_plcd->value()));
            //m_stk.push(str);
            qDebug() << m_stk.count() << ": 3st";
            if (str != "=")
            {
                m_stk.push(str);
                qDebug() << str << ": 13!";
                qDebug() << m_stk.count() << ": 4st";
            }
        }
        else
        {
            //m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push(m_strDisplay);
            m_stk.push(str);
            qDebug() << str << ": 1! !";
            qDebug() << m_stk.count() << ": 5st";
            qDebug() << m_strDisplay << ": 5st";
            if (str == "sin" || str == "cos")
                calculate();
            m_strDisplay = "";
            m_plcd->display("0");
        }
    }
}
