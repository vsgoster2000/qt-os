#ifndef CLIENTTESTDIALOG_H
#define CLIENTTESTDIALOG_H

#include <os/localconnection.h>
#include <os/localmessage.h>

#include <QDialog>

using namespace moon;

namespace Ui {
class ClientTestDialog;
}

class ChattingThread;

class ClientTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientTestDialog(QWidget *parent = 0);
    ~ClientTestDialog();

private slots:
    void onConnectService();
    void onDisconnectService();
    void onSendData();
    void onReceivingData(const QByteArray &data);
    void onMessage(const LocalMessage &msg);

    void showStatus(const QString &text);
    void showStatus(const char *format);
    void showRecvData(const QByteArray &data);

private:
    Ui::ClientTestDialog *ui;
    LocalConnectionPtr mConnection;
   // ChattingThread *mChattingThread;
};

#endif // CLIENTTESTDIALOG_H
