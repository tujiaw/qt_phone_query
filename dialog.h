#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class QNetworkAccessManager;
class QNetworkReply;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void slotQuery();

private:
    Ui::Dialog *ui;
    QNetworkAccessManager *m_netManager;
};

#endif // DIALOG_H
