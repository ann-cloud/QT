#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QRegularExpression>
#include <math.h>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButton();
    void SignButtonPressed();
    void RadButtonPressed();
    void PerButtonPressed();
    void HyperButtonPressed();
    void LnButtonPressed();
    void LgButtonPressed();
    void DecButtonPressed();
    void BackButtonPressed();
    void ClearButtonPressed();
};
#endif // CALCULATOR_H
