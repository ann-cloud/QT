#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
bool addClicked = false;
bool subClicked = false;
bool multClicked = false;
bool divClicked = false;
bool powClicked = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0;i<10;++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] =  Calculator::findChild<QPushButton*>(butName);
        connect(numButtons[i], SIGNAL(released()),this,SLOT(NumPressed()));
    }
    connect(ui->Addition, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Subtraction, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiplication, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Division, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Pow, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equal, SIGNAL(released()),this,SLOT(EqualButton()));
    connect(ui->Sign, SIGNAL(released()),this,SLOT(SignButtonPressed()));
    connect(ui->Radical, SIGNAL(released()),this,SLOT(RadButtonPressed()));
    connect(ui->Percent, SIGNAL(released()),this,SLOT(PerButtonPressed()));
    connect(ui->Hyper, SIGNAL(released()),this,SLOT(HyperButtonPressed()));
    connect(ui->Lg, SIGNAL(released()),this,SLOT(LgButtonPressed()));
    connect(ui->Ln, SIGNAL(released()),this,SLOT(LnButtonPressed()));
    connect(ui->Decimal, SIGNAL(released()),this,SLOT(DecButtonPressed()));
    connect(ui->Backspace, SIGNAL(released()),this,SLOT(BackButtonPressed()));
    connect(ui->Clear, SIGNAL(released()),this,SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString display = ui->Display->text();
    if(!display.contains("."))
    {
       QString Val = display + butval;
       double dblVal = Val.toDouble();
       ui->Display->setText(QString::number(dblVal,'g',15));
    }
    else
    {
        QString Val = display + butval;
        ui->Display->setText(Val);
    }
}

void Calculator::MathButtonPressed()
{
    addClicked = false;
    subClicked = false;
    multClicked = false;
    divClicked = false;
    powClicked = false;
    QString display = ui->Display->text();
    calcVal = display.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString symbol = button->text();
    if(QString::compare(symbol,"+",Qt::CaseInsensitive) == 0)
    {
        addClicked = true;
    }
    else if(QString::compare(symbol,"-",Qt::CaseInsensitive) == 0)
    {
        subClicked = true;
    }
    else if(QString::compare(symbol,"x",Qt::CaseInsensitive) == 0)
    {
        multClicked = true;
    }
    else if(QString::compare(symbol,"/",Qt::CaseInsensitive) == 0)
    {
        divClicked = true;
    }
    else if(QString::compare(symbol,"^",Qt::CaseInsensitive) == 0)
    {
        powClicked = true;
    }
    ui->Vikno->setText(display);
    ui->Display->setText("");
}

void Calculator::EqualButton()
{
    double result = 0.0;
    QString display = ui->Display->text();
    double dblDisplay = display.toDouble();
    if(addClicked || subClicked || multClicked || divClicked || powClicked)
    {
         if(addClicked)
         {
             result = calcVal + dblDisplay;
         }
         else if(subClicked)
         {
             result = calcVal - dblDisplay;
         }
         else if(multClicked)
         {
             result = calcVal * dblDisplay;
         }
         else if(divClicked)
         {
             if(0 == dblDisplay)
             {
                 QMessageBox::critical(this,"Error", "Can't be calculated");
                 ui->Display->setText("0");
             }
             else result = calcVal / dblDisplay;
         }
         else if(powClicked)
         {
             if(calcVal < 0)
             {
                 QMessageBox::critical(this,"Error", "Can't be calculated");
                 ui->Display->setText("0");
             }
             else result = pow(calcVal, dblDisplay);
         }
    }
    ui->Display->setText(QString::number(result));
    ui->Vikno->setText("");
}

void Calculator::SignButtonPressed()
{
    QString display = ui->Display->text();
    QRegularExpression regExp("[-]?[0-9.]*");
    QRegularExpressionMatch match = regExp.match(display);
    if(match.hasMatch())
    {
        double dblDisplay = display.toDouble();
        double dblDisplayNew = -1 * dblDisplay;
        ui->Display->setText(QString::number(dblDisplayNew));
    }
}

void Calculator::RadButtonPressed()
{
    QString display = ui->Display->text();
    double dblDisplay = display.toDouble();
    if(dblDisplay < 0)
    {
        QMessageBox::critical(this,"Error", "Can't be calculated");
        ui->Display->setText("0");
    }
    else
    {
        double dblDisplayNew = sqrt(dblDisplay);
        ui->Display->setText(QString::number(dblDisplayNew));
    }
}

void Calculator::PerButtonPressed()
{
    QString display = ui->Display->text();
    double dblDisplay = display.toDouble();
    double dblDisplayNew = dblDisplay / 100;
    ui->Display->setText(QString::number(dblDisplayNew));
}

void Calculator::HyperButtonPressed()
{
    QString display = ui->Display->text();
    double dblDisplay = display.toDouble();
    if(0 == dblDisplay)
    {
        QMessageBox::critical(this,"Error", "Can't be calculated");
        ui->Display->setText("0");
    }

    else
    {
        double dblDisplayNew = 1 / dblDisplay;
        ui->Display->setText(QString::number(dblDisplayNew));
    }
}

void Calculator::LgButtonPressed()
{
    QString display = ui->Display->text();
    double dblDisplay = display.toDouble();
    if(dblDisplay <= 0)
    {
        QMessageBox::critical(this,"Error", "Can't be calculated");
        ui->Display->setText("0");
    }
    else
    {
        double dblDisplayNew = log10(dblDisplay);
        ui->Display->setText(QString::number(dblDisplayNew));
    }
}

void Calculator::LnButtonPressed()
{
    QString display = ui->Display->text();
    double dblDisplay = display.toDouble();
    if(dblDisplay <= 0)
    {
        QMessageBox::critical(this,"Error", "Can't be calculated");
        ui->Display->setText("0");
    }
    else
    {
        double dblDisplayNew = log(dblDisplay);
        ui->Display->setText(QString::number(dblDisplayNew));
    }
}

void Calculator::DecButtonPressed()
{
    QString display = ui->Display->text();
    if(! display.contains("."))
    {
    QString Display = display + ".";
    ui->Display->setText(Display);
    }
}

void Calculator::BackButtonPressed()
{
    QString display = ui->Display->text();
    display.chop(1);
    if(display.isEmpty())
    {
        display = "0";
    }
    ui->Display->setText(display);
}

void Calculator::ClearButtonPressed()
{
    ui->Display->setText("0");
    ui->Vikno->setText("");
}



