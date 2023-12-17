#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QPixmap>
#include <QScrollArea>
#include <QStandardPaths>
#include <QImageWriter>
#include <QImageReader>
#include <QScrollBar>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Editor; }
QT_END_NAMESPACE

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    Editor(QWidget *parent = nullptr);
    bool loadFile(const QString &);
    ~Editor();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionSave_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionFont_triggered();

    void on_openImage_triggered();

private:
    Ui::Editor *ui;
    QString currentFile = "";
    double scaleFactor;

    QLabel*imageLabel;
    QScrollArea*scrollArea;
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
};
#endif // EDITOR_H
