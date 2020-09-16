#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QStack>

class QLCDNumber;
class QPushButton;

// =========================================================
class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber * m_plcd;
    QStack<QString> m_stk;
    QString m_strDisplay;

public:
    Calculator(QWidget * pwgt = nullptr);
    QPushButton * createButton(const QString & str);
    void calculate();
    ~Calculator();

public slots:
    void slotButtonClicked();
};
#endif // CALCULATOR_H
