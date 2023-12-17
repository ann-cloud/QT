#include "editor.h"
#include "ui_editor.h"

Editor::Editor(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Editor)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Editor::~Editor()
{
    delete ui;
}


void Editor::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void Editor::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open file");
    QFile file(filename);
    currentFile = filename;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void Editor::on_actionSave_triggered()
{
    QString filename;
    if(currentFile.isEmpty())
    {
        filename = QFileDialog::getSaveFileName(this, "Save");
        currentFile = filename;
    }
    else filename = currentFile;
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Editor::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this,"Warning","Cannot save file: " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Editor::on_openImage_triggered()
{
        QString fileName = QFileDialog::getOpenFileName(this,
                                         tr("Open File"), QDir::currentPath());
        QUrl Uri ( QString ( "file://%1" ).arg ( fileName ) );
        QImage image = QImageReader(fileName).read();
        QTextDocument * textDocument = ui->textEdit->document();
        textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
        QTextCursor cursor = ui->textEdit->textCursor();
        QTextImageFormat imageFormat;
        imageFormat.setWidth( ui->textEdit->width());
        imageFormat.setHeight( ui->textEdit->height());
        imageFormat.setName( Uri.toString() );
        cursor.insertImage(imageFormat);
}

void Editor::on_actionExit_triggered()
{
    QApplication::quit();
}


void Editor::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void Editor::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void Editor::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void Editor::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void Editor::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void Editor::on_actionFont_triggered()
{
    bool fontSet;
    QTextCursor cursor = ui->textEdit->textCursor();
    QFont font = QFontDialog::getFont(&fontSet, this);
    if (fontSet)
    {
        if(cursor.hasSelection())
        {
            QTextCharFormat format;
            format.setFont(font);
            cursor.setCharFormat(format);
            cursor.insertText(cursor.selectedText());
        }
    }
}

//void Editor::on_actionSelect_triggered()
//{
//    QString text = ui->textEdit->toPlainText();
//    QTextCursor cursor = ui->textEdit->textCursor();
//    QStringList wholeText = text.split("\n");
//    QStringList words;

//    for(int i=0;i<wholeText.length();++i)
//    {
//        words=wholeText[i].split(" ");
//        int start1=0;
//        int end1=words[0].length();
//        int start2 = words[0].length()+1+words[1].length()+1;
//        int end2 = start2+words[2].length();
//        cursor.setPosition(start2);
//        cursor.setPosition(end2,QTextCursor::KeepAnchor);
//        ui->textEdit->setTextCursor(cursor);
//        cursor.setPosition(start1);
//        cursor.setPosition(end1,QTextCursor::KeepAnchor);
//        ui->textEdit->setTextCursor(cursor);
//    }
//}

