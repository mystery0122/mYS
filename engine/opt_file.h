#ifndef OPT_FILE_H
#define OPT_FILE_H

#include <QDialog>

namespace Ui {
class opt_file;
}

class opt_file : public QDialog
{
    Q_OBJECT

public:
    explicit opt_file(QWidget *parent = 0);
    ~opt_file();
    QString history_name;

private slots:
    void on_pushButton_clicked();

private:
    Ui::opt_file *ui;
};

#endif // OPT_FILE_H
