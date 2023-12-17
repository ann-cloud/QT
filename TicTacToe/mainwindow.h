#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QMessageBox>

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
    void on_tableWidget_itemPressed(QTableWidgetItem *item);

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    bool CheckIsWinner();
};
#endif // MAINWINDOW_H
