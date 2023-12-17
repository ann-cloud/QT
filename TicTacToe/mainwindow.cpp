#include "mainwindow.h"
#include "ui_mainwindow.h"

QString currentSymbol = "x";
QString currPlayer = "Player 1";
int Player1Count = 0;
int Player2Count = 0;
int iRow = 3;
int jCol = 3;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(iRow);
    ui->tableWidget->setColumnCount(jCol);
    for(int i=0;i<ui->tableWidget->rowCount();++i)
    {
        for(int j=0;j<ui->tableWidget->columnCount();++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,j, item);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
    QString text = item->text();
    int nFlag=0;
    if(text.isEmpty())
    {
        item->setText(currentSymbol);
        if(CheckIsWinner())
        {
            if(currentSymbol == "x")
            {
                Player1Count++;
                ui->P1Count->setText(QString::number(Player1Count));
                int ret = QMessageBox::information(0,"Game over", "PLAYER 1 WON!\nWant to replay ?", QMessageBox::Yes  | QMessageBox::No);
                if(ret == QMessageBox::Yes)
                {
                    for(int i=0;i<ui->tableWidget->rowCount();++i)
                    {
                        for(int j=0;j<ui->tableWidget->columnCount();++j)
                        {
                            ui->tableWidget->item(i,j)->setText("");
                        }
                    }
                    currPlayer = "Player 1";
                    currentSymbol = "x";
                    ui->currentSymbolLabel->setText(currPlayer);
                }
                else this->close();
            }
            else
            {
                Player2Count++;
                ui->P2Count->setText(QString::number(Player2Count));
                int ret = QMessageBox::information(0,"Game over", "PLAYER 2 WON!\nWant to replay ?", QMessageBox::Yes  | QMessageBox::No);
                if(ret == QMessageBox::Yes)
                {
                    for(int i=0;i<ui->tableWidget->rowCount();++i)
                    {
                        for(int j=0;j<ui->tableWidget->columnCount();++j)
                        {
                            ui->tableWidget->item(i,j)->setText("");
                        }
                    }
                    currPlayer = "Player 1";
                    currentSymbol = "x";
                    ui->currentSymbolLabel->setText(currPlayer);
                }
                else this->close();
            }
            return;
        }
        for(int i=0;i<ui->tableWidget->rowCount();++i)
        {
            for(int j=0;j<ui->tableWidget->columnCount();++j)
            {
                if(!ui->tableWidget->item(i,j)->text().isEmpty())
                    nFlag++;
            }
        }
        if(nFlag == (ui->tableWidget->rowCount())*(ui->tableWidget->columnCount()))
        {
            int ret = QMessageBox::information(0,"Game over", "TIE!\nWant to replay ?", QMessageBox::Yes  | QMessageBox::No);
            if(ret == QMessageBox::Yes)
            {
                for(int i=0;i<ui->tableWidget->rowCount();++i)
                {
                    for(int j=0;j<ui->tableWidget->columnCount();++j)
                    {
                        ui->tableWidget->item(i,j)->setText("");
                    }
                }
                currPlayer = "Player 1";
                currentSymbol = "x";
                ui->currentSymbolLabel->setText(currPlayer);
            }
            else this->close();
            return;
        }
        if(QString::compare(currentSymbol,"x",Qt::CaseInsensitive) == 0)
        {
            currentSymbol = "o";
            currPlayer = "Player 2";
        }
        else
        {
            currentSymbol = "x";
            currPlayer = "Player 1";
        }
        ui->currentSymbolLabel->setText(currPlayer);
    }
}

bool MainWindow::CheckIsWinner()
{
    int nEqual;
    int nEqual2 = 1;
    for(int j=0;j<ui->tableWidget->rowCount();++j)
    {
        nEqual = 1;
        for(int i=1;i<ui->tableWidget->columnCount();++i)
        {
            if(!ui->tableWidget->item(j,0)->text().isEmpty() && ui->tableWidget->item(j,0)->text() == ui->tableWidget->item(j,i)->text())
            {
                nEqual++;
                if(nEqual == ui->tableWidget->columnCount()) return true;
            }
        }
    }
    for(int j=0;j<ui->tableWidget->columnCount();++j)
    {
        nEqual = 1;
        for(int i=1;i<ui->tableWidget->rowCount();++i)
        {
            if(!ui->tableWidget->item(0,j)->text().isEmpty() && ui->tableWidget->item(0,j)->text() == ui->tableWidget->item(i,j)->text())
            {
                nEqual++;
                if(nEqual == ui->tableWidget->rowCount()) return true;
            }
        }
    }
    nEqual = 1;
    for(int i=1;i<ui->tableWidget->columnCount();++i)
    {
        if(!ui->tableWidget->item(0,0)->text().isEmpty() && ui->tableWidget->item(0,0)->text() == ui->tableWidget->item(i,i)->text())
        {
            nEqual++;
            if(nEqual == ui->tableWidget->rowCount()) return true;
        }
        if(!ui->tableWidget->item(ui->tableWidget->columnCount()-1,0)->text().isEmpty() && ui->tableWidget->item(ui->tableWidget->columnCount()-1,0)->text() == ui->tableWidget->item(ui->tableWidget->columnCount()-1-i,i)->text())
        {
            nEqual2++;
            if(nEqual2 == ui->tableWidget->columnCount()) return true;
        }
    }
    return false;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->tableWidget->setRowCount(value);
    ui->tableWidget->setColumnCount(value);
    int width = ui->tableWidget->width();
    int size = width/value;
    for(int i=0;i<ui->tableWidget->rowCount();++i)
    {
        for(int j=0;j<ui->tableWidget->columnCount();++j)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,j, item);
        }
    }
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(size);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(size);
    currentSymbol = "x";
}

