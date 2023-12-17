#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constituency.h"
#include <QMessageBox>
#include <fstream>
#include <QDebug>

using namespace std;

int iQuantity = 0;
int iWritten = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnWidth(0, 50); //встановлюємо початкові розміри таблиці зі списком
    ui->tableWidget->setColumnWidth(1, 200); //виборчих округів
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setColumnWidth(5, 150);

    ui->tableWidget_2->setColumnWidth(0, 50); // встановлюємо початкові розміри таблиці з результатами
    ui->tableWidget_2->setColumnWidth(1, 200);
    ui->tableWidget_2->setColumnWidth(2, 150);
    ui->tableWidget_2->setColumnWidth(3, 150);
    ui->tableWidget_2->setColumnWidth(4, 150);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//додавання нового виборчого округу
void MainWindow::on_add_clicked()
{
    iQuantity++;
    ui->tableWidget->setRowCount(iQuantity);
    QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(iQuantity));
    item0->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(iQuantity - 1, 0, item0);
    QTableWidgetItem *item1 = new QTableWidgetItem(ui->constituency->currentText());
    item1->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(iQuantity - 1, 1, item1);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(ui->education->value()));
    item2->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(iQuantity - 1, 2, item2);
    QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(ui->observants->value()));
    item3->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(iQuantity - 1, 3, item3);
    QTableWidgetItem *item4 = new QTableWidgetItem(ui->members->currentText());
    item4->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(iQuantity - 1, 4, item4);
    QTableWidgetItem *item5 = new QTableWidgetItem();
    item4->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(iQuantity - 1, 5, item5);
}

//визначення середніх витрат на навчання на одну людину (спостерігачі і члени ДВК)
void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
    if (item->column() == 1)
    {
        int currentRow = item->row();
        int expenses = ui->tableWidget->item(currentRow, 2)->text().toInt();
        int observants = ui->tableWidget->item(currentRow, 3)->text().toInt();
        int members = ui->tableWidget->item(currentRow, 4)->text().toInt();
        if (observants == 0 && members == 0)
        {
            int ret = QMessageBox::information(0,"Info", "There are no members and observants in this constitution", QMessageBox::Ok);
            ui->avg->setText("");
        }
        else
        {
            Constituency el(item->text().toStdString(), expenses, observants, members);
            ui->avg->setText(QString::number(el.avgExpenses()));
        }
    }
}

//визначення округів, в яких кількість спостерігачів менше 50% від кількості членів ДВК
void MainWindow::on_lessThanHalf_clicked()
{
    vector<Constituency> list;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        string name = ui->tableWidget->item(i, 1)->text().toStdString();
        int expenses = ui->tableWidget->item(i, 2)->text().toInt();
        int observants = ui->tableWidget->item(i, 3)->text().toInt();
        int members = ui->tableWidget->item(i, 4)->text().toInt();
        Constituency el(name, expenses, observants, members);
        if (observants < 0.5 * members)
        {
            list.push_back(el);
        }
    }
    if (list.size() == 0)
        int ret = QMessageBox::information(0,"Info", "No constituencies were found that satisfy the condition", QMessageBox::Ok);
    else
    {
        ui->tableWidget_2->setRowCount(list.size());
        for (size_t i = 0; i < list.size(); ++i)
        {
            QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(i + 1));
            item0->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i, 0, item0);
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(list[i].getName()));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i, 1, item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(list[i].getEducation()));
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i, 2, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(list[i].getObservants()));
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i, 3, item3);
            QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(list[i].getMembers()));
            item4->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(i, 4, item4);
        }
    }
}

//сортування записів за кількістю членів ДВК в округах
void MainWindow::on_sort_clicked()
{
    if (!ui->tableWidget->rowCount())
    {
        int ret = QMessageBox::information(0,"Info", "There is no information to sort", QMessageBox::Ok);
        return;
    }
    vector<Constituency> list;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        string name = ui->tableWidget->item(i, 1)->text().toStdString();
        int expenses = ui->tableWidget->item(i, 2)->text().toInt();
        int observants = ui->tableWidget->item(i, 3)->text().toInt();
        int members = ui->tableWidget->item(i, 4)->text().toInt();
        Constituency el(name, expenses, observants, members);
        list.push_back(el);
    }
    Constituency::SortByMembers(list);
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        ui->tableWidget->item(i, 1)->setText(QString::fromStdString(list[i].getName()));
        ui->tableWidget->item(i, 2)->setText(QString::number(list[i].getEducation()));
        ui->tableWidget->item(i, 3)->setText(QString::number(list[i].getObservants()));
        ui->tableWidget->item(i, 4)->setText(QString::number(list[i].getMembers()));
    }
}

//визначення округів, в яких витрати на членів ДВК менші за середні
void MainWindow::on_memLessThanAvg_clicked()
{
    QString info = "";
    vector<Constituency> list;
    int ret;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        string name = ui->tableWidget->item(i, 1)->text().toStdString();
        int expenses = ui->tableWidget->item(i, 2)->text().toInt();
        int observants = ui->tableWidget->item(i, 3)->text().toInt();
        int members = ui->tableWidget->item(i, 4)->text().toInt();
        if (members == 0)
        {
            info += "Constituency " + QString::number(i + 1) + " has no DVK members.\n";
            break;
        }
        Constituency el(name, expenses, observants, members);
        list.push_back(el);
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(el.memberExpenses()));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 5, item);
    }
    if ((int)list.size() < ui->tableWidget->rowCount())
        ret = QMessageBox::critical(0,"Info", info, QMessageBox::Ok);
    else
    {
        ui->avgDVK->setText(QString::number(Constituency::avgMemberExpenses(list)));
        Constituency::memberExpensesLessThanAvg(list);
        if (list.size() == 0)
            ret = QMessageBox::information(0,"Info", "No constituencies were found that satisfy the condition", QMessageBox::Ok);
        else
        {
            ui->tableWidget_2->setRowCount(list.size());
            for (size_t i = 0; i < list.size(); ++i)
            {
                QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(i + 1));
                item0->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 0, item0);
                QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(list[i].getName()));
                item1->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 1, item1);
                QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(list[i].getEducation()));
                item2->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 2, item2);
                QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(list[i].getObservants()));
                item3->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 3, item3);
                QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(list[i].getMembers()));
                item4->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 4, item4);
            }
        }
    }
}

//визначення 5-ти округів, в яких кількість спостерігачів більша середньої,
//проте витрати на навчання одного спостерігача менші середніх
void MainWindow::on_fiveByCondition_clicked()
{
    QString info = "";
    vector<Constituency> list;
    int ret;
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
    {
        string name = ui->tableWidget->item(i, 1)->text().toStdString();
        int expenses = ui->tableWidget->item(i, 2)->text().toInt();
        int observants = ui->tableWidget->item(i, 3)->text().toInt();
        int members = ui->tableWidget->item(i, 4)->text().toInt();
        if (observants == 0)
        {
            info += "Constituency " + QString::number(i + 1) + " has no observants.\n";
            break;
        }
        Constituency el(name, expenses, observants, members);
        list.push_back(el);
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(el.observantExpenses()));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(i, 5, item);
    }
    if ((int)list.size() < ui->tableWidget->rowCount())
        ret = QMessageBox::critical(0,"Info", info, QMessageBox::Ok);
    else
    {
        ui->avgObsv->setText(QString::number(Constituency::avgObservantExpenses(list)));
        ui->avgObsvCount->setText(QString::number(Constituency::avgObservantCount(list)));
        Constituency::fiveByCondition(list);
        size_t tempSize = list.size();
        if (list.size() == 0)
            ret = QMessageBox::information(0,"Info", "No constituencies were found that satisfy the condition", QMessageBox::Ok);
        else
        {
            if (list.size() > 5)
            {
                ret = QMessageBox::information(0,"Info", "More than 5 constituencies were found that satisfy the condition", QMessageBox::Ok);
                tempSize = 5;
            }
            else if (list.size() < 5)
                ret = QMessageBox::information(0,"Info", "Less than 5 constituencies were found that satisfy the condition", QMessageBox::Ok);
            ui->tableWidget_2->setRowCount(tempSize);
            for (size_t i = 0; i < tempSize; ++i)
            {
                QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(i + 1));
                item0->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 0, item0);
                QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(list[i].getName()));
                item1->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 1, item1);
                QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(list[i].getEducation()));
                item2->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 2, item2);
                QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(list[i].getObservants()));
                item3->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 3, item3);
                QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(list[i].getMembers()));
                item4->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget_2->setItem(i, 4, item4);
            }
        }
    }
}

//записування результатів у файл
void MainWindow::on_writeToFile_clicked()
{
    ofstream file;
    file.open("/Users/annasuslova/Desktop/courseWork/output.txt", ios::app);
    if (ui->tableWidget->rowCount() == 0 && ui->tableWidget_2->rowCount() == 0)
    {
        int ret = QMessageBox::information(0,"Info", "There is no information to write to file", QMessageBox::Ok);
        return;
    }
    if (iWritten)
    {
        iWritten--;
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            string name = ui->tableWidget->item(i, 1)->text().toStdString();
            int expenses = ui->tableWidget->item(i, 2)->text().toInt();
            int observants = ui->tableWidget->item(i, 3)->text().toInt();
            int members = ui->tableWidget->item(i, 4)->text().toInt();
            Constituency el(name, expenses, observants, members);
            file << el;
        }
        file << endl;
    }
    for (int i = 0; i < ui->tableWidget_2->rowCount(); ++i)
    {
        string name = ui->tableWidget_2->item(i, 1)->text().toStdString();
        int expenses = ui->tableWidget_2->item(i, 2)->text().toInt();
        int observants = ui->tableWidget_2->item(i, 3)->text().toInt();
        int members = ui->tableWidget_2->item(i, 4)->text().toInt();
        Constituency el(name, expenses, observants, members);
        file << el;
    }
    file << endl;
}

//зчитування даних з файлу
void MainWindow::on_readFromFile_clicked()
{
    vector<Constituency> list;
    ifstream file, file1;
    string line;
    int rowCount = 0;
    const string fileName = "/Users/annasuslova/Desktop/courseWork/input.txt";
    ifstream f(fileName);
    if (!f.good())
    {
        int ret = QMessageBox::critical(0,"Info", "File doesn't exist", QMessageBox::Ok);
        return;
    }
    file.open(fileName);
    if (file.peek() == std::ifstream::traits_type::eof())
        int ret = QMessageBox::warning(0,"Info", "File is empty", QMessageBox::Ok);
    else
    {
        while (getline(file, line))
        {
            rowCount++;
        }
        file.close();
        file1.open(fileName);
        for (int i = 0; i < rowCount; ++i)
        {
            Constituency el;
            file1 >> el;
            list.push_back(el);
        }
        file1.close();
        iQuantity = list.size();
        ui->tableWidget->setRowCount(list.size());
        for (size_t i = 0; i < list.size(); ++i)
        {
            QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(i + 1));
            item0->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 0, item0);
            QTableWidgetItem *item1 = new QTableWidgetItem(QString::fromStdString(list[i].getName()));
            item1->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 1, item1);
            QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(list[i].getEducation()));
            item2->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 2, item2);
            QTableWidgetItem *item3 = new QTableWidgetItem(QString::number(list[i].getObservants()));
            item3->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 3, item3);
            QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(list[i].getMembers()));
            item4->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 4, item4);
        }
    }
}


void MainWindow::on_delete_2_clicked()
{
    if (ui->tableWidget->rowCount() || ui->tableWidget_2->rowCount())
    {
        for (int i = 0; i < ui->tableWidget->rowCount(); ++i)
        {
            ui->tableWidget->removeRow(i);
            i--;
        }
        for (int i = 0; i < ui->tableWidget_2->rowCount(); ++i)
        {
            ui->tableWidget_2->removeRow(i);
            i--;
        }
        iQuantity = 0;
    }
    else
    {
        int ret = QMessageBox::information(0,"Info", "There is no information to clear", QMessageBox::Ok);
        return;
    }
}

