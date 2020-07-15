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
    void autoLessKeyControl(bool checked);
    void autoPlayKeyControl(bool checked);
    void discernTimer_Elapsed();
    void hitKeyTimer_Elapsed();
private:
    int ipPort = 18925;
    Ui::MainWindow *ui;
    QPoint lastMousePos;
    bool moving = false;
    char scale = 0;
    QMenu *pMenu;
    QTimer *pingTimer;
    QTimer *connectTimer;
    QTimer *discernTimer;
    QTimer *hitKeyTimer;
    bool nowConnected = false;
    BufferList bufferList;
    TcpSocket *client;
    QByteArray userId;
    QElapsedTimer timer;
    ColorLabelGroup *repairKeyLabelGroup;
    int logLine = 0;
    unsigned short playKey[10] = {0};
    int playKeyIndex = 0;
    QString playKeystr = "                  ";
    bool hitKeyTimerOnRun = false;
    char hitKeyRole = 0;
    int hitKeyIndex = 0;
    void hitkey();
    void showRepairUserName(structure_repairKeyForUserName *repairForUserName);
    void listenTextChange();
    void stopListenTextChange();
    void addLog(QString logMessage);
    bool precondition();
    char preconditionTimes = 0;
    int killingIntentionStrip = 0;
    int FiveTone[5];
    bool FiveToneReady = false;
    //bool AutoLessKey=false;
    bool getWuXiaPosition(int &x, int &y, int &width, int &height);
    int findKillingIntentionStrip();
    int GetYUVVariance(const QColor &c1, const QColor &c2);
    bool findKeyPosition();
    char findLessKey(char (&keyLessState)[5]);
    QVector<QString> log;
};
#endif // MAINWINDOW_H
