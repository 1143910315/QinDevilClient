#include "mainwindow.h"
#include "dialog.h"
#include "ui_mainwindow.h"
#include "lesskeyvalidator.h"
#include "windowshook.h"
#include "..\\QinDevilCommonStructure\\ccsysteminfo.h"
#include <QCryptographicHash>
#include <QRegExpValidator>
#include <QSlider>
//constexpr auto ipHost = "127.0.0.1";
//constexpr auto ipPort = 12580;
constexpr auto ipHost = "q1143910315.gicp.net";
constexpr auto ipPort = 11866;
#if Power
#else
    #define PowerLevel 0
    #define Line 0
#endif
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    WindowsHook *instance = WindowsHook::getInstance();
    instance->controlClear.code = 103;
    instance->controlClear.ctrl = true;
    instance->controlClear.alt = false;
    instance->controlClear.shift = false;
    instance->controlNote1.code = 97;
    instance->controlNote1.ctrl = true;
    instance->controlNote1.alt = false;
    instance->controlNote1.shift = false;
    instance->controlNote2.code = 98;
    instance->controlNote2.ctrl = true;
    instance->controlNote2.alt = false;
    instance->controlNote2.shift = false;
    instance->controlNote3.code = 99;
    instance->controlNote3.ctrl = true;
    instance->controlNote3.alt = false;
    instance->controlNote3.shift = false;
    instance->controlNote4.code = 100;
    instance->controlNote4.ctrl = true;
    instance->controlNote4.alt = false;
    instance->controlNote4.shift = false;
    instance->controlNote5.code = 101;
    instance->controlNote5.ctrl = true;
    instance->controlNote5.alt = false;
    instance->controlNote5.shift = false;
    connect(instance, &WindowsHook::note1, this, &MainWindow::note1);
    connect(instance, &WindowsHook::note2, this, &MainWindow::note2);
    connect(instance, &WindowsHook::note3, this, &MainWindow::note3);
    connect(instance, &WindowsHook::note4, this, &MainWindow::note4);
    connect(instance, &WindowsHook::note5, this, &MainWindow::note5);
    connect(instance, &WindowsHook::clear, this, &MainWindow::clear);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::opacity);
    //QRegExpValidator *pRegVld = new QRegExpValidator(this);
    //pRegVld->setRegExp(QRegExp("^(?![1-5]*?([1-5])[1-5]*?\\1)[1-5]{0,3}$"));
    //pRegVld->setRegExp(QRegExp("^[1-5]{0,3}$"));
    //pRegVld->setRegExp(QRegExp("^123$", Qt::CaseSensitivity::CaseSensitive, QRegExp::PatternSyntax::WildcardUnix));
    //pRegVld->setRegExp(QRegExp("^[0-9]{5,10}$"));
    //pRegVld->setRegExp(QRegExp("^[1-5](?=(\\1))$"));
    //int index = 0;
    //QString str = "11";
    //QValidator::State localValidate = pRegVld->validate(str, index);
    //switch(localValidate) {
    //    case QValidator::State::Invalid: {
    //        qDebug("Invalid");
    //    }
    //    break;
    //    case QValidator::State::Acceptable: {
    //        qDebug("Acceptable");
    //    }
    //    break;
    //    case QValidator::State::Intermediate: {
    //        qDebug("Intermediate");
    //    }
    //    break;
    //}
    LessKeyValidator *lessKeyValidator = new LessKeyValidator(this);
    ui->lineEdit->setValidator(lessKeyValidator);
    ui->lineEdit_2->setValidator(lessKeyValidator);
    ui->lineEdit_3->setValidator(lessKeyValidator);
    ui->lineEdit_4->setValidator(lessKeyValidator);
    listenTextChange();
    repairKeyLabelGroup = new ColorLabelGroup(this);
    repairKeyLabelGroup->addColorLabel(ui->label_2);
    repairKeyLabelGroup->addColorLabel(ui->label_3);
    repairKeyLabelGroup->addColorLabel(ui->label_4);
    repairKeyLabelGroup->addColorLabel(ui->label_5);
    repairKeyLabelGroup->addColorLabel(ui->label_6);
    ui->label_2->textColor = QColor(255, 255, 255);
    ui->label_3->textColor = QColor(255, 255, 255);
    ui->label_4->textColor = QColor(255, 255, 255);
    ui->label_5->textColor = QColor(255, 255, 255);
    ui->label_6->textColor = QColor(255, 255, 255);
    ui->label_7->colors.append(QColor(220, 220, 220));
    ui->label_7->colors.append(QColor(200, 200, 200));
    ui->label_7->colors.append(QColor(220, 220, 220));
    ui->label_8->colors.append(QColor(220, 220, 220));
    ui->label_8->colors.append(QColor(200, 200, 200));
    ui->label_8->colors.append(QColor(220, 220, 220));
    ui->label_9->colors.append(QColor(220, 220, 220));
    ui->label_9->colors.append(QColor(200, 200, 200));
    ui->label_9->colors.append(QColor(220, 220, 220));
    ui->label_10->colors.append(QColor(220, 220, 220));
    ui->label_10->colors.append(QColor(200, 200, 200));
    ui->label_10->colors.append(QColor(220, 220, 220));
    connect(repairKeyLabelGroup, &ColorLabelGroup::repairKey, this, &MainWindow::repairKey);
    //connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::sendLessKey);
    //connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::sendLessKey);
    //connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::sendLessKey);
    //connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &MainWindow::sendLessKey);
    timer.start();
    QString macAndCpuId = CCSystemInfo::get_mac_frist() + CCSystemInfo::get_cpuId();
    userId = QCryptographicHash::hash(macAndCpuId.toLocal8Bit(), QCryptographicHash::Md5);
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
    pingTimer = new QTimer(this);
    connect(pingTimer, &QTimer::timeout, this, &MainWindow::sendPing);
    client->connectToHost(ipHost, ipPort);
    /*
    void(SubWidget::*backSignal)() = &SubWidget::backSignal;  // 我是没有参数的backSignal, 叫backSignal1
    connect(&subWin, backSignal, this, &MainWidget::backSlot);

    void(SubWidget::*backSigna2)(QString) = &SubWidget::backSignal;  // 我是带一个QString参数的backSignal, 叫backSignal2
    connect(&subWin, backSigna2, this, &MainWidget::logSlot);
    */
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
            stopListenTextChange();
            ui->lineEdit->setText(QString::fromUtf16(receiveData->qinLessKey, -1));
            ui->lineEdit_2->setText(QString::fromUtf16(receiveData->qinLessKey + 4, -1));
            ui->lineEdit_3->setText(QString::fromUtf16(receiveData->qinLessKey + 8, -1));
            ui->lineEdit_4->setText(QString::fromUtf16(receiveData->qinLessKey + 12, -1));
            listenTextChange();
            QString myName = QString::fromUtf16(receiveData->name, -1);
            pingTimer->start(1000);
            if(myName.length() == 0) {
                Dialog *d = new Dialog(this);
                //d->setAttribute(Qt::WA_DeleteOnClose, true);
                if(d->exec() == 1) {
                    myName = d->getName();
                    structure_repairForUserName sendData;
                    int i = 0;
                    for(; i < myName.length() && i < 15; i++) {
                        sendData.userName[i] = myName[i].unicode();
                    }
                    sendData.userName[i] = 0;
                    Buffer *sendBuff = client->getSendBuffer(4, sizeof(sendData));
                    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
                    client->sendBuffer(sendBuff);
                    delete d;
                } else {
                    delete d;
                    close();
                }
            }
            ui->lineEdit_5->setText(myName);
            showRepairUserName(&receiveData->repairKey);
            break;
        }
        case 1: {
            structure_pingData *receiveData = (structure_pingData *)data;
            //qDebug("%lld %lld", timer.elapsed(), receiveData->time);
            int ping = timer.elapsed() - receiveData->time;
            if(ping > 9999) {
                ping = 9999;
            }
            ui->label->setText(QString::asprintf("Ping:%dms", ping));
            break;
        }
        case 2: {
            structure_LessKey *receiveData = (structure_LessKey *)data;
            switch(receiveData->numberQin) {
                case 0: {
                    stopListenTextChange();
                    qDebug("lineEdit->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
                case 1: {
                    stopListenTextChange();
                    qDebug("lineEdit_2->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit_2->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
                case 2: {
                    stopListenTextChange();
                    qDebug("lineEdit_3->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit_3->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
                case 3: {
                    stopListenTextChange();
                    qDebug("lineEdit_4->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit_4->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
            }
            break;
        }
        case 3: {
            structure_repairKeyForUserName *receiveData = (structure_repairKeyForUserName *)data;
            showRepairUserName(receiveData);
            break;
        }
        case 4: {
            structure_playKey *receiveData = (structure_playKey *)data;
            QString str;
            for(int i = 0; i < 10; i++) {
                QChar c = receiveData->playKey[i];
                if(c != 0) {
                    str.append(receiveData->playKey[i]);
                    str.append(" ");
                } else {
                    break;
                }
            }
            ui->label_13->setText(str);
            break;
        }
        case 5: {
            structure_clearData *receiveData = (structure_clearData *)data;
            client->time = receiveData->time;
            stopListenTextChange();
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            listenTextChange();
            repairKeyLabelGroup->resetChecked();
            ui->label_7->setText("");
            ui->label_8->setText("");
            ui->label_9->setText("");
            ui->label_10->setText("");
            ui->label_13->setText("");
            ui->label_7->colors[0] = ui->label_7->colors[2] = QColor(220, 220, 220);
            ui->label_7->colors[1] = QColor(200, 200, 200);
            ui->label_8->colors[0] = ui->label_8->colors[2] = QColor(220, 220, 220);
            ui->label_8->colors[1] = QColor(200, 200, 200);
            ui->label_9->colors[0] = ui->label_9->colors[2] = QColor(220, 220, 220);
            ui->label_9->colors[1] = QColor(200, 200, 200);
            ui->label_10->colors[0] = ui->label_10->colors[2] = QColor(220, 220, 220);
            ui->label_10->colors[1] = QColor(200, 200, 200);
            ui->label_7->repaint();
            ui->label_8->repaint();
            ui->label_9->repaint();
            ui->label_10->repaint();
            playKeyIndex = 0;
            playKey[playKeyIndex] = 0;
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
    //client->connectToHost(ipHost, ipPort);
    qDebug("disconnected");
}

void MainWindow::sendPing() {
    structure_pingData d;
    d.time = timer.elapsed();
    Buffer *sendBuff = client->getSendBuffer(1, sizeof(d));
    client->writeBuffer(&sendBuff, (char *)&d, sizeof(d));
    client->sendBuffer(sendBuff);
}

void MainWindow::sendLessKey(int qinId, QString lessKey) {
    qDebug("%d %s", qinId, qPrintable(lessKey));
    structure_LessKey sendData;
    sendData.numberQin = qinId;
    int len = lessKey.length();
    int i;
    for(i = 0; i < len; i++) {
        sendData.lessKey[i] = lessKey[i].unicode();
    }
    sendData.lessKey[i] = 0;
    Buffer *sendBuff = client->getSendBuffer(2, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::repairKey(int keyId, bool isChecked) {
    structure_repairKey sendData;
    sendData.keyId = keyId;
    sendData.isChecked = isChecked;
    Buffer *sendBuff = client->getSendBuffer(3, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::opacity(int value) {
    setWindowOpacity(value / 100.0);
}

void MainWindow::note1() {
    if(playKeyIndex < 9) {
        playKey[playKeyIndex] = '1';
        playKeyIndex++;
        playKey[playKeyIndex] = 0;
    }
    structure_playKey sendData;
    for(int i = 0; i < 10; i++) {
        sendData.playKey[i] = playKey[i];
    }
    Buffer *sendBuff = client->getSendBuffer(5, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::note2() {
    if(playKeyIndex < 9) {
        playKey[playKeyIndex] = '2';
        playKeyIndex++;
        playKey[playKeyIndex] = 0;
    }
    structure_playKey sendData;
    for(int i = 0; i < 10; i++) {
        sendData.playKey[i] = playKey[i];
    }
    Buffer *sendBuff = client->getSendBuffer(5, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::note3() {
    if(playKeyIndex < 9) {
        playKey[playKeyIndex] = '3';
        playKeyIndex++;
        playKey[playKeyIndex] = 0;
    }
    structure_playKey sendData;
    for(int i = 0; i < 10; i++) {
        sendData.playKey[i] = playKey[i];
    }
    Buffer *sendBuff = client->getSendBuffer(5, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::note4() {
    if(playKeyIndex < 9) {
        playKey[playKeyIndex] = '4';
        playKeyIndex++;
        playKey[playKeyIndex] = 0;
    }
    structure_playKey sendData;
    for(int i = 0; i < 10; i++) {
        sendData.playKey[i] = playKey[i];
    }
    Buffer *sendBuff = client->getSendBuffer(5, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::note5() {
    if(playKeyIndex < 9) {
        playKey[playKeyIndex] = '5';
        playKeyIndex++;
        playKey[playKeyIndex] = 0;
    }
    structure_playKey sendData;
    for(int i = 0; i < 10; i++) {
        sendData.playKey[i] = playKey[i];
    }
    Buffer *sendBuff = client->getSendBuffer(5, sizeof(sendData));
    client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
    client->sendBuffer(sendBuff);
}

void MainWindow::clear() {
    Buffer *sendBuff = client->getSendBuffer(6, 0);
    client->sendBuffer(sendBuff);
}

void MainWindow::repairNote1() {
}

void MainWindow::repairNote2() {
}

void MainWindow::repairNote3() {
}

void MainWindow::repairNote4() {
}

void MainWindow::repairNote5() {
}

void MainWindow::showRepairUserName(structure_repairKeyForUserName *repairForUserName) {
    QString temp;
    QString str;
    temp = QString::fromUtf16(repairForUserName->qinForUserName[0].userName, -1);
    if(temp.length() == 0) {
        ui->label_7->colors[0] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_7->colors[0] = QColor(35, 255, 35);
        } else {
            ui->label_7->colors[0] = QColor(255, 35, 35);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[1].userName, -1);
    if(temp.length() == 0) {
        ui->label_7->colors[1] = QColor(200, 200, 200);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_7->colors[1] = QColor(35, 255, 35);
        } else {
            ui->label_7->colors[1] = QColor(255, 35, 35);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[2].userName, -1);
    if(temp.length() == 0) {
        ui->label_7->colors[2] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_7->colors[2] = QColor(35, 255, 35);
        } else {
            ui->label_7->colors[2] = QColor(255, 35, 35);
        }
    }
    str += temp;
    ui->label_7->setText(str);
    temp = QString::fromUtf16(repairForUserName->qinForUserName[3].userName, -1);
    if(temp.length() == 0) {
        ui->label_8->colors[0] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_8->colors[0] = QColor(35, 255, 35);
        } else {
            ui->label_8->colors[0] = QColor(255, 35, 35);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[4].userName, -1);
    if(temp.length() == 0) {
        ui->label_8->colors[1] = QColor(200, 200, 200);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_8->colors[1] = QColor(35, 255, 35);
        } else {
            ui->label_8->colors[1] = QColor(255, 35, 35);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[5].userName, -1);
    if(temp.length() == 0) {
        ui->label_8->colors[2] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_8->colors[2] = QColor(35, 255, 35);
        } else {
            ui->label_8->colors[2] = QColor(255, 35, 35);
        }
    }
    str += temp;
    ui->label_8->setText(str);
    temp = QString::fromUtf16(repairForUserName->qinForUserName[6].userName, -1);
    if(temp.length() == 0) {
        ui->label_9->colors[0] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_9->colors[0] = QColor(35, 255, 35);
        } else {
            ui->label_9->colors[0] = QColor(255, 35, 35);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[7].userName, -1);
    if(temp.length() == 0) {
        ui->label_9->colors[1] = QColor(200, 200, 200);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_9->colors[1] = QColor(35, 255, 35);
        } else {
            ui->label_9->colors[1] = QColor(255, 35, 35);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[8].userName, -1);
    if(temp.length() == 0) {
        ui->label_9->colors[2] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_9->colors[2] = QColor(35, 255, 35);
        } else {
            ui->label_9->colors[2] = QColor(255, 35, 35);
        }
    }
    str += temp;
    ui->label_9->setText(str);
    temp = QString::fromUtf16(repairForUserName->qinForUserName[9].userName, -1);
    if(temp.length() == 0) {
        ui->label_10->colors[0] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_10->colors[0] = QColor(35, 255, 35);
        } else {
            ui->label_10->colors[0] = QColor(255, 35, 35);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[10].userName, -1);
    if(temp.length() == 0) {
        ui->label_10->colors[1] = QColor(200, 200, 200);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_10->colors[1] = QColor(35, 255, 35);
        } else {
            ui->label_10->colors[1] = QColor(255, 35, 35);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[11].userName, -1);
    if(temp.length() == 0) {
        ui->label_10->colors[2] = QColor(220, 220, 220);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_10->colors[2] = QColor(35, 255, 35);
        } else {
            ui->label_10->colors[2] = QColor(255, 35, 35);
        }
    }
    str += temp;
    ui->label_10->setText(str);
}

void MainWindow::listenTextChange() {
    connect(ui->lineEdit, &QLineEdit::textChanged, this, [ = ](QString text) {
        qDebug("ui->lineEdit::textChanged");
        sendLessKey(0, text);
    });
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [ = ](QString text) {
        qDebug("ui->lineEdit_2::textChanged");
        sendLessKey(1, text);
    });
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [ = ](QString text) {
        qDebug("ui->lineEdit_3::textChanged");
        sendLessKey(2, text);
    });
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, [ = ](QString text) {
        qDebug("ui->lineEdit_4::textChanged");
        sendLessKey(3, text);
    });
}

void MainWindow::stopListenTextChange() {
    ui->lineEdit->disconnect(this);
    ui->lineEdit_2->disconnect(this);
    ui->lineEdit_3->disconnect(this);
    ui->lineEdit_4->disconnect(this);
}

