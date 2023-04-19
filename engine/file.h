#ifndef FILE_H
#define FILE_H

#include <QDialog>

namespace Ui {
class file;
}

class file : public QDialog
{
    Q_OBJECT

public:
    explicit file(QWidget *parent = 0);
    QString get_name();
    ~file();

private:
    Ui::file *ui;
};

#endif // FILE_H
