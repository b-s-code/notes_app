#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto note_list = ui->listView;

    QString path_lhs = QDir::homePath(), path_rhs = ".notes_app_data";

    if (!QFile::exists(path_lhs + path_rhs))
    {
        // Maybe nicer if this was a static method.
        // We only create a QDir intance here because the mkdir
        // method is not static.
        QDir().mkdir(path_rhs);
    }

    QDir d = QDir(path_lhs + path_rhs);

    std::cout << "Beginning file enumeration." << std::endl;
    for (const auto& dir_entry : d.entryList())
    {
        std::cout << dir_entry.toStdString() << std::endl;

        // TODO : check that directory entry corresponds to:
        // - a text file,
        // - which adheres to custom note format
        //  - i.e. bytes 0-255 encode the title, and
        //  - remaining bytes encode the note contents.
        // - That is, the directory entry should correspond to
        //   a text file greater than 256 bytes long.
        //model.appendRow(...)
    }
    std::cout << "Ending file enumeration." << std::endl;

    // TODO : apply model.
    //note_list->setModel();
}

MainWindow::~MainWindow()
{
    delete ui;
}
