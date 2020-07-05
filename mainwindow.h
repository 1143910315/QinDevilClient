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
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
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
    QPoint lastMousePos;
    bool moving = false;
    char scale = 0;
    QMenu *pMenu;
    QTimer *pingTimer;
    QTimer *connectTimer;
    bool nowConnected = false;
    BufferList bufferList;
    TcpSocket *client;
    QByteArray userId;
    QElapsedTimer timer;
    ColorLabelGroup *repairKeyLabelGroup;
    int logLine = 0;
    unsigned short playKey[10] = {0};
    int playKeyIndex = 0;
    void showRepairUserName(structure_repairKeyForUserName *repairForUserName);
    void listenTextChange();
    void stopListenTextChange();
    void addLog(QString logMessage);
    QString playKeystr = "                  ";
    QVector<QString> log;
};
#endif // MAINWINDOW_H
