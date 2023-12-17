#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();

    void on_tableWidget_itemPressed(QTableWidgetItem *item);

    void on_lessThanHalf_clicked();

    void on_sort_clicked();

    void on_memLessThanAvg_clicked();

    void on_fiveByCondition_clicked();

    void on_writeToFile_clicked();

    void on_readFromFile_clicked();

    void on_delete_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
