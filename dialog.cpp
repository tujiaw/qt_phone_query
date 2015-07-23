#include "dialog.h"
#include "ui_dialog.h"
#include <QtWidgets>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <qjsonobject.h>
#include "json.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_netManager = new QNetworkAccessManager(this);

    connect(ui->pbQuery, &QPushButton::clicked, this, &Dialog::slotQuery);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slotQuery()
{
    ui->teResult->clear();

    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString("yyyyMMddHHmmss");
    QString phoneNumber = ui->lePhoneNumber->text().trimmed();
    QString appId = "4150";
    QString secret = "6a619d14ba434e82b121ce7fa137faf8";

    QStringList argvList;
    argvList << "showapi_appid=" + appId;
    argvList << "showapi_timestamp=" + dateTimeString;
    argvList << "num=" + phoneNumber;
    qSort(argvList);

    // 生成MD5规则：https://www.showapi.com/api/lookPoint/6
    QString argvStr = argvList.join("");
    argvStr = argvStr.replace("=", "") + secret;
    QString md5 = QCryptographicHash::hash(argvStr.toLocal8Bit(), QCryptographicHash::Md5).toHex();

    QUrl url("http://route.showapi.com/6-1?" + argvList.join("&") + "&showapi_sign=" + md5);
    QNetworkReply *reply = m_netManager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, [this] () {
        qDebug() << "finished";
    });

    connect(reply, &QNetworkReply::readyRead, [this, reply] () {
        QVariantMap data = json::toMap(reply->readAll());
        if (data["showapi_res_code"].toInt() == 0) {
            QVariantMap body = data["showapi_res_body"].toMap();
            ui->teResult->append("prov:" + body["prov"].toString());
            ui->teResult->append("city:" + body["city"].toString());
            ui->teResult->append("name:" + body["name"].toString());
        }
    });

    connect(reply, &QNetworkReply::downloadProgress, [this] (qint64 recv, qint64 total) {
        qDebug() << "progress:" << recv << "," << total;
    });
}
