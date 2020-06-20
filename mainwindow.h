#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include "tcpsocket.h"
#include "colorlabelgroup.h"
#include "..\\QinDevilCommonStructure\\commonstructure.h"
QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected slots:
    void connected();
    void receive(int signal, char *data, int count);
    void version(int v);
    void error(QAbstractSocket::SocketError socketError);
    void disconnected();
    void sendPing();
    void sendLessKey(int qinId, QString lessKey);
    void repairKey(int keyId, bool isChecked);
    void opacity(int value);
    void note1();
    void note2();
    void note3();
    void note4();
    void note5();
    void clear();
    void repairNote1();
    void repairNote2();
    void repairNote3();
    void repairNote4();
    void repairNote5();
private:
    Ui::MainWindow *ui;
    QTimer *pingTimer;
    BufferList bufferList;
    TcpSocket *client;
    QByteArray userId;
    QElapsedTimer timer;
    ColorLabelGroup *repairKeyLabelGroup;
    unsigned short playKey[10] = {0};
    int playKeyIndex = 0;
    void showRepairUserName(structure_repairKeyForUserName *repairForUserName);
    void listenTextChange();
    void stopListenTextChange();
};
#endif // MAINWINDOW_H
