#include "opt_file.h"
#include "ui_opt_file.h"
#include <QDir>

opt_file::opt_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::opt_file)
{
    ui->setupUi(this);
    QString file_path = "/home/root/saved_file";
    QDir dir(file_path);
    QStringList file_list;
    file_list = dir.entryList(QDir::Files);
    ui->comboBox->addItems(file_list);
   // qDebug()<<file_list;
}

opt_file::~opt_file()
{
    delete ui;
}

void opt_file::on_pushButton_clicked()
{
    this->history_name = ui->comboBox->currentText();
}
