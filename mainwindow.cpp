#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "..\\QinDevilCommonStructure\\commonstructure.h"
#include "..\\QinDevilCommonStructure\\ccsysteminfo.h"
#include <QCryptographicHash>
constexpr auto ipHost = "127.0.0.1";
constexpr auto ipPort = 12580;
//constexpr auto ipHost = "q1143910315.gicp.net";
//constexpr auto ipPort = 11866;
#if Power
#else
    #define PowerLevel 0
    #define Line 0
#endif
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    timer.start();
    QString macAndCpuId = CCSystemInfo::get_mac_frist() + CCSystemInfo::get_cpuId();
    userId = QCryptographicHash::hash(macAndCpuId.toLocal8Bit(), QCryptographicHash::Md5);
    pingTimer = new QTimer(this);
    connect(pingTimer, &QTimer::timeout, this, &MainWindow::sendPing);
    //QByteArray bb = QCryptographicHash::hash((CCSystemInfo::get_mac_frist() + CCSystemInfo::get_cpuId()).toLocal8Bit(), QCryptographicHash::Md5);
    //QString userId = bb.toHex();
    //qDebug("%s", qPrintable(userId));
    //fc768d4b0382c4bf9c50fa678566fb49
    client = new TcpSocket(&bufferList, this);
    connect(client, &TcpSocket::connected, this, &MainWindow::connected);
    connect(client, &TcpSocket::receive, this, &MainWindow::receive);
    connect(client, &TcpSocket::version, this, &MainWindow::version);
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    connect(client, &TcpSocket::disconnected, this, &MainWindow::disconnected);
    client->connectToHost(ipHost, ipPort);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connected() {
}

void MainWindow::receive(int signal, char *data, int count) {
    (void)count;
    switch(signal) {
        case 0: {
            structure_allGameData *receiveData = (structure_allGameData *)data;
            client->time = receiveData->time;
            pingTimer->start(1000);
            break;
        }
        case 1: {
            structure_pingData *receiveData = (structure_pingData *)data;
            int ping = timer.elapsed() - receiveData->time;
            if(ping > 9999) {
                ping = 9999;
            }
            ui->label->setText(QString::asprintf("Ping:%dms", ping));
            break;
        }
    }
}

void MainWindow::version(int v) {
    if(v != Version) {
        close();
    } else {
        structure_initData d;
        d.powerLevel = PowerLevel;
        d.line = Line;
        for(int i = 0; i < 16; i++) {
            d.userId[i] = userId[i];
        }
        Buffer *sendBuff = client->getSendBuffer(0, sizeof(d));
        client->writeBuffer(&sendBuff, (char *)&d, sizeof(d));
        client->sendBuffer(sendBuff);
    }
}

void MainWindow::error(QAbstractSocket::SocketError socketError) {
    (void)socketError;
    //client->connectToHost(ipHost, ipPort);
    qDebug("error:%d", socketError);
}

void MainWindow::disconnected() {
    pingTimer->stop();
    client->connectToHost(ipHost, ipPort);
    qDebug("disconnected");
}

void MainWindow::sendPing() {
    structure_pingData d;
    d.time = timer.elapsed();
    Buffer *sendBuff = client->getSendBuffer(1, sizeof(d));
    client->writeBuffer(&sendBuff, (char *)&d, sizeof(d));
    client->sendBuffer(sendBuff);
}

