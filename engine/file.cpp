#include "file.h"
#include "ui_file.h"

file::file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::file)
{
    ui->setupUi(this);
}

file::~file()
{
    delete ui;
}

QString file::get_name(){
    QString name;
    name = ui->lineEdit->text();
    return name;
}
