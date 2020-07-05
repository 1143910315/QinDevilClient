#include "mainwindow.h"
#include "dialog.h"
#include "logdialog.h"
#include "ui_mainwindow.h"
#include "lesskeyvalidator.h"
#include "windowshook.h"
#include "windowsmethod.h"
#include "doubleclicklineedit.h"
#include "..\\QinDevilCommonStructure\\ccsysteminfo.h"
#include <QCryptographicHash>
#include <QMenu>
#include <QProcess>
#include <QRegExpValidator>
#include <QSlider>
#include <QMessageBox>
#include <QWindow>
#include <QPainter>
#include <QBrush>
#include <QGraphicsDropShadowEffect>
//#include <winuser.h>
//constexpr auto ipHost = "127.0.0.1";
//constexpr auto ipPort = 12580;
constexpr auto ipHost = "q1143910315.gicp.net";
constexpr auto ipPort = 11866;
//constexpr auto ipHost ="116.62.125.206";
#define const_color1 231,231,231
#define const_color2 221,221,221
#define const_color3 214,213,213
#define const_color_red 231,51,82
#define const_color_green 49,160,0
const int SHADOW_WIDTH = 5;
#if Power
#else
    #define PowerLevel 0
    #define Line 0
#endif
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //this->showFullScreen();
    log.append("程序启动\n");
    pMenu = new QMenu(this);
    pMenu->addAction(ui->action);
    pMenu->addAction(ui->action1);
    pMenu->addAction(ui->action2);
    pMenu->addAction(ui->action3);
    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->action, &QAction::triggered, [&](bool checked) {
        (void)checked;
        LogDialog *dialog = new LogDialog(&log, this);
        dialog->setAttribute(Qt::WA_DeleteOnClose, true);
        //dialog->setModal(false);
        dialog->show();
    });
    connect(ui->action1, &QAction::triggered, [&](bool checked) {
        (void)checked;
        if(checked) {
            unsigned int i = windowsMethod::GetWuXiaProcess();
            if(i == 0) {
                this->windowHandle()->setParent(nullptr);
            } else {
                QWindow *w = QWindow::fromWinId(windowsMethod::GetWuXiaProcess());
                this->windowHandle()->setParent(w);
            }
        } else {
            //QWindow *w = QWindow::fromWinId(0);
            this->windowHandle()->setParent(nullptr);
        }
        //windowsMethod::GetWuXiaProcess();
        //w->fi
        //QWindow::
        //this->setParent(w);
        //QWindow::from
        //int i = windowsMethod::a();
        //QMessageBox::information(NULL, "Title", QString::number(i), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    });
    connect(ui->action2, &QAction::triggered, [&](bool checked) {
        //ui->horizontalLayout_3->widget()->setHidden(checked);
        ui->widget->setHidden(checked);
    });
    connect(ui->action3, &QAction::triggered, [&](bool checked) {
        //ui->horizontalLayout_3->widget()->setHidden(checked);
        ui->widget_2->setHidden(checked);
    });
    //ui->horizontalLayout_2.
    connect(this, &QMainWindow::customContextMenuRequested, [&](const QPoint & pos) {
        (void)pos;
        pMenu->exec(QCursor::pos());
        //pMenu->popup(QCursor::pos());
    });
    connect(ui->lineEdit_5, &DoubleClickLineEdit::mouseDoubleClick, [&]() {
        if(nowConnected) {
            Dialog *d = new Dialog(this);
            //d->setAttribute(Qt::WA_DeleteOnClose, true);
            if(d->exec() == 1024) {
                QString myName;
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
                ui->lineEdit_5->setText(myName);
            }
            delete d;
        }
    });
    //(void)ui->horizontalLayout_2;
    setAttribute(Qt::WA_TranslucentBackground, true);
    //ui->widget->setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //setMouseTracking(true);
    //QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //shadow->setOffset(0, 0);//设置阴影距离
    //shadow->setColor(QColor("#444444"));//设置阴影颜色
    //shadow->setBlurRadius(10);//设置阴影圆角
    //setGraphicsEffect(shadow);//给嵌套QWidget设置阴影
    //setStyleSheet("background-color:rgb(248,255,255)");//给嵌套QWidget添加颜色
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
    //connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::opacity);
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
    ui->label_7->colors.append(QColor(const_color1));
    ui->label_7->colors.append(QColor(const_color2));
    ui->label_7->colors.append(QColor(const_color3));
    ui->label_8->colors.append(QColor(const_color1));
    ui->label_8->colors.append(QColor(const_color2));
    ui->label_8->colors.append(QColor(const_color3));
    ui->label_9->colors.append(QColor(const_color1));
    ui->label_9->colors.append(QColor(const_color2));
    ui->label_9->colors.append(QColor(const_color3));
    ui->label_10->colors.append(QColor(const_color1));
    ui->label_10->colors.append(QColor(const_color2));
    ui->label_10->colors.append(QColor(const_color3));
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
    connectTimer = new QTimer(this);
    connectTimer->setSingleShot(true);
    connect(connectTimer, &QTimer::timeout, [&]() {
        client->connectToHost(ipHost, ipPort);
    });
    client->connectToHost(ipHost, ipPort);
    /*
    void(SubWidget::*backSignal)() = &SubWidget::backSignal;  // 我是没有参数的backSignal, 叫backSignal1
    connect(&subWin, backSignal, this, &MainWidget::backSlot);

    void(SubWidget::*backSigna2)(QString) = &SubWidget::backSignal;  // 我是带一个QString参数的backSignal, 叫backSignal2
    connect(&subWin, backSigna2, this, &MainWidget::logSlot);
    */
    //ui->horizontalLayout->removeWidget(ui->label_4);
    //ui->label_4->setGeometry(10, 100, 24, 27);
    //(void)ui->horizontalLayout;
}

MainWindow::~MainWindow() {
    this->client->disconnect(this);
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    event->accept();
    QPainter painter(this);
    QColor color(68, 68, 68, 20);
    QPen pen = QPen(color);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    for(int i = 0; i < SHADOW_WIDTH; i++) {
        //pen.setWidth(SHADOW_WIDTH - i);
        // 方角阴影边框;
        //   painter.drawRect(SHADOW_WIDTH - i, SHADOW_WIDTH - i, this->width() - (SHADOW_WIDTH - i) * 2, this->height() - (SHADOW_WIDTH - i) * 2);
        // 圆角阴影边框;
        painter.drawRoundedRect(i, i, width() - i * 2, height() - i * 2, 10, 10);
    }
    painter.setBrush(QBrush(QColor(248, 255, 255)));
    const QRect widgetGeometry = geometry();
    const QRect headGeometry = ui->horizontalLayout_7->geometry();
    const QMargins contentsMargins = ui->centralwidget->layout()->contentsMargins();
    int imageHeight = headGeometry.height() - SHADOW_WIDTH + contentsMargins.top();
    int imageWidth = imageHeight * 2203 / 379;
    painter.drawRect(SHADOW_WIDTH, SHADOW_WIDTH + imageHeight, widgetGeometry.width() - SHADOW_WIDTH * 2, widgetGeometry.height() - SHADOW_WIDTH * 2 - imageHeight);
    QImage image(":/new/prefix1/head.png");
    if(imageWidth + SHADOW_WIDTH * 2 > widgetGeometry.width()) {
        painter.drawImage(QRect(SHADOW_WIDTH, SHADOW_WIDTH, widgetGeometry.width() - SHADOW_WIDTH * 2, imageHeight), image, QRect(0, 0, image.width() * (widgetGeometry.width() - SHADOW_WIDTH * 2) / imageWidth, image.height()), Qt::AutoColor);
    } else {
        painter.drawImage(QRect(SHADOW_WIDTH, SHADOW_WIDTH, imageWidth, imageHeight), image, QRect(0, 0, image.width(), image.height()), Qt::AutoColor);
        painter.setBrush(QBrush(QColor(74, 63, 77)));
        painter.drawRect(imageWidth + SHADOW_WIDTH, SHADOW_WIDTH, widgetGeometry.width() - SHADOW_WIDTH * 2 - imageWidth, imageHeight);
    }
    /*
    //QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(248, 255, 255)));
    const QRect widgetGeometry = geometry();
    painter.drawRect(5, 5, widgetGeometry.width() - 10, widgetGeometry.height() - 10);
    QMargins localContentsMargins = ui->centralwidget->layout()->contentsMargins();
    QRect localGeometry = ui->horizontalLayout_7->geometry();
    int height = localGeometry.height() + localContentsMargins.top();
    int width = height * 2203 / 379;
    //int maxWidth = localGeometry.width() + localContentsMargins.left() + localContentsMargins.right();
    //qDebug("%d", ui->horizontalLayout_6->geometry().height());
    QImage image(":/new/prefix1/head.png");
    int minWidth = width < widgetGeometry.width() ? width : widgetGeometry.width();
    painter.drawImage(QRect(5, 5, minWidth - 10, height - 5), image, QRect(0, 0, image.width(), image.height()), Qt::AutoColor);
    //painter.drawImage(QRectF(5, 5, width, height), QImage(":/new/prefix1/head.png"));
    if(widgetGeometry.width() > width) {
        painter.setBrush(QBrush(QColor(74, 63, 77)));
        painter.drawRect(width, 0, widgetGeometry.width() - width, height);
    }*/
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        int localX = event->x();
        int localY = event->y();
        QMargins localContentsMargins = ui->centralwidget->layout()->contentsMargins();
        QRect localGeometry = ui->horizontalLayout_7->geometry();
        int headHeight = localGeometry.height() + localContentsMargins.top();
        if(localY >= SHADOW_WIDTH && localY <= headHeight && localX >= SHADOW_WIDTH && localX <= width() - SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            moving = true;
            event->accept();
        } else if(localY < SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localX < SHADOW_WIDTH * 2) {
                scale = 1;
            } else if(localX > width() - SHADOW_WIDTH * 2) {
                scale = 3;
            } else {
                scale = 2;
            }
        } else if(localY > height() - SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localX < SHADOW_WIDTH * 2) {
                scale = 7;
            } else if(localX > width() - SHADOW_WIDTH * 2) {
                scale = 5;
            } else {
                scale = 6;
            }
        } else if(localX < SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localY < SHADOW_WIDTH * 2) {
                scale = 1;
            } else if(localY > height() - SHADOW_WIDTH * 2) {
                scale = 7;
            } else {
                scale = 8;
            }
        } else if(localX > width() - SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localY < SHADOW_WIDTH * 2) {
                scale = 3;
            } else if(localY > height() - SHADOW_WIDTH * 2) {
                scale = 5;
            } else {
                scale = 4;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    int localX = event->x();
    int localY = event->y();
    if(moving) {
        QPoint localPos = QCursor::pos();
        QPoint nowPos = pos();
        move(nowPos.x() - lastMousePos.x() + localPos.x(), nowPos.y() - lastMousePos.y() + localPos.y());
        lastMousePos = localPos;
        event->accept();
    } else if(scale == 0) {
        //qDebug("%d %d", localX, localY);
        if(localY < SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localX < SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeFDiagCursor);
            } else if(localX > width() - SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeBDiagCursor);
            } else {
                setCursor(Qt::SizeVerCursor);
            }
        } else if(localY > height() - SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localX < SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeBDiagCursor);
            } else if(localX > width() - SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeFDiagCursor);
            } else {
                setCursor(Qt::SizeVerCursor);
            }
        } else if(localX < SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localY < SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeFDiagCursor);
            } else if(localY > height() - SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeBDiagCursor);
            } else {
                setCursor(Qt::SizeHorCursor);
            }
        } else if(localX > width() - SHADOW_WIDTH) {
            lastMousePos = QCursor::pos();
            if(localY < SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeBDiagCursor);
            } else if(localY > height() - SHADOW_WIDTH * 2) {
                setCursor(Qt::SizeFDiagCursor);
            } else {
                setCursor(Qt::SizeHorCursor);
            }
        } else {
            setCursor(Qt::ArrowCursor);
        }
    } else {
        QRect localGeometry = geometry();
        int minWidth = minimumWidth();
        int minHeight = minimumHeight();
        switch(scale) {
            case 1: {
                localGeometry.setTopLeft(QCursor::pos());
                if(localGeometry.width() < minWidth || localGeometry.height() < minHeight) {
                    localGeometry.setLeft(localGeometry.x() - minWidth + localGeometry.width());
                    localGeometry.setTop(localGeometry.y() - minHeight + localGeometry.height());
                }
                break;
            }
            case 2: {
                localGeometry.setTop(QCursor::pos().y());
                if(localGeometry.height() < minHeight) {
                    localGeometry.setTop(localGeometry.y() - minHeight + localGeometry.height());
                }
                break;
            }
            case 3: {
                localGeometry.setTopRight(QCursor::pos());
                if(localGeometry.height() < minHeight) {
                    localGeometry.setTop(localGeometry.y() - minHeight + localGeometry.height());
                }
                break;
            }
            case 4: {
                localGeometry.setRight(QCursor::pos().x());
                break;
            }
            case 5: {
                localGeometry.setBottomRight(QCursor::pos());
                break;
            }
            case 6: {
                localGeometry.setBottom(QCursor::pos().y());
                break;
            }
            case 7: {
                localGeometry.setBottomLeft(QCursor::pos());
                if(localGeometry.width() < minWidth) {
                    localGeometry.setLeft(localGeometry.x() - minWidth + localGeometry.width());
                }
                break;
            }
            case 8: {
                localGeometry.setLeft(QCursor::pos().x());
                if(localGeometry.width() < minWidth) {
                    localGeometry.setLeft(localGeometry.x() - minWidth + localGeometry.width());
                }
                break;
            }
        }
        this->setGeometry(localGeometry);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        scale = 0;
        moving = false;
        setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::connected() {
    nowConnected = true;
}

void MainWindow::receive(int signal, char *data, int count) {
    (void)count;
    //qDebug("%d",ui->centralwidget.);
    //qDebug("%d %d %d %d", ui->centralwidget->minimumSize().width(), ui->centralwidget->minimumSize().height(), ui->centralwidget->minimumSize().rwidth(), ui->centralwidget->minimumSize().rheight());
    //const QRect localGeometry = ui->label_4->geometry();
    //qDebug("%d %d %d %d", localGeometry.x(), localGeometry.y(), localGeometry.width(), localGeometry.height());
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
                if(d->exec() == 1024) {
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
                    //qDebug("lineEdit->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
                case 1: {
                    stopListenTextChange();
                    //qDebug("lineEdit_2->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit_2->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
                case 2: {
                    stopListenTextChange();
                    //qDebug("lineEdit_3->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
                    ui->lineEdit_3->setText(QString::fromUtf16(receiveData->lessKey, -1));
                    listenTextChange();
                    break;
                }
                case 3: {
                    stopListenTextChange();
                    //qDebug("lineEdit_4->setText %s", qPrintable(QString::fromUtf16(receiveData->lessKey, -1)));
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
            for(int i = 0; i < 10; i++) {
                QChar c = receiveData->playKey[i];
                if(c != 0) {
                    playKeystr[i * 2] = c;
                    //str.append(receiveData->playKey[i]);
                    //str.append(" ");
                } else {
                    break;
                }
            }
            ui->label_13->setText(playKeystr);
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
            ui->label_7->setText("\n\n");
            ui->label_8->setText("\n\n");
            ui->label_9->setText("\n\n");
            ui->label_10->setText("\n\n");
            playKeystr = "                 ";
            ui->label_13->setText("");
            ui->label_7->colors[0] = ui->label_8->colors[0] = ui->label_9->colors[0] = ui->label_10->colors[0] = QColor(const_color1);
            ui->label_7->colors[1] = ui->label_8->colors[1] = ui->label_9->colors[1] = ui->label_10->colors[1] = QColor(const_color2);
            ui->label_7->colors[2] = ui->label_8->colors[2] = ui->label_9->colors[2] = ui->label_10->colors[2] = QColor(const_color3);
            QPalette pe;
            pe.setColor(QPalette::WindowText, QColor(0, 0, 0));
            ui->label_22->setPalette(pe);
            ui->label_23->setPalette(pe);
            ui->label_24->setPalette(pe);
            ui->label_25->setPalette(pe);
            ui->label_22->setText("一号琴");
            ui->label_23->setText("二号琴");
            ui->label_24->setText("三号琴");
            ui->label_25->setText("四号琴");
            ui->label_7->repaint();
            ui->label_8->repaint();
            ui->label_9->repaint();
            ui->label_10->repaint();
            playKeyIndex = 0;
            playKey[playKeyIndex] = 0;
            break;
        }
        case 6: {
            structure_logMessage *receiveData = (structure_logMessage *)data;
            logLine++;
            if(logLine > 50) {
                logLine = 0;
                log.append("");
            }
            int index = log.count() - 1;
            //qDebug("%s", qPrintable(QString::fromUtf16(receiveData->log, -1)));
            log[index] += QString::fromUtf16(receiveData->log, -1) + "\n";
            break;
        }
    }
}

void MainWindow::version(int v) {
    if(v != Version) {
        //QProcess::startDetached("update.exe");
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
    //(void)socketError;
    //client->connectToHost(ipHost, ipPort);
    qDebug("error:%d", socketError);
    if(nowConnected == false) {
        connectTimer->start(2000);
    }
    if(socketError == QAbstractSocket::ConnectionRefusedError) {
        addLog("连接遭到服务器拒绝");
    } else {
        addLog("发生了一个网络错误，但是我不告诉你");
    }
}

void MainWindow::disconnected() {
    qDebug("disconnected");
    pingTimer->stop();
    nowConnected = false;
    connectTimer->start(2000);
    addLog("因外部原因，连接服务器的通道被关闭");
    //client->connectToHost(ipHost, ipPort);
}

void MainWindow::sendPing() {
    structure_pingData d;
    d.time = timer.elapsed();
    Buffer *sendBuff = client->getSendBuffer(1, sizeof(d));
    client->writeBuffer(&sendBuff, (char *)&d, sizeof(d));
    client->sendBuffer(sendBuff);
}

void MainWindow::sendLessKey(int qinId, QString lessKey) {
    //qDebug("%d %s", qinId, qPrintable(lessKey));
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
    QPalette pe;
    pe.setColor(QPalette::WindowText, QColor(0, 0, 0));
    ui->label_22->setPalette(pe);
    ui->label_23->setPalette(pe);
    ui->label_24->setPalette(pe);
    ui->label_25->setPalette(pe);
    pe.setColor(QPalette::WindowText, QColor(const_color_green));
    if(temp.length() == 0) {
        ui->label_7->colors[0] = QColor(const_color1);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_7->colors[0] = QColor(const_color_green);
            ui->label_22->setPalette(pe);
            ui->label_22->setText("== 一号琴 ==");
        } else {
            ui->label_7->colors[0] = QColor(const_color_red);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[1].userName, -1);
    if(temp.length() == 0) {
        ui->label_7->colors[1] = QColor(const_color2);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_7->colors[1] = QColor(const_color_green);
            ui->label_22->setPalette(pe);
            ui->label_22->setText("== 一号琴 ==");
        } else {
            ui->label_7->colors[1] = QColor(const_color_red);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[2].userName, -1);
    if(temp.length() == 0) {
        ui->label_7->colors[2] = QColor(const_color3);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_7->colors[2] = QColor(const_color_green);
            ui->label_22->setPalette(pe);
            ui->label_22->setText("== 一号琴 ==");
        } else {
            ui->label_7->colors[2] = QColor(const_color_red);
        }
    }
    str += temp;
    ui->label_7->setText(str);
    temp = QString::fromUtf16(repairForUserName->qinForUserName[3].userName, -1);
    if(temp.length() == 0) {
        ui->label_8->colors[0] = QColor(const_color1);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_8->colors[0] = QColor(const_color_green);
            ui->label_23->setPalette(pe);
            ui->label_23->setText("== 二号琴 ==");
        } else {
            ui->label_8->colors[0] = QColor(const_color_red);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[4].userName, -1);
    if(temp.length() == 0) {
        ui->label_8->colors[1] = QColor(const_color2);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_8->colors[1] = QColor(const_color_green);
            ui->label_23->setPalette(pe);
            ui->label_23->setText("== 二号琴 ==");
        } else {
            ui->label_8->colors[1] = QColor(const_color_red);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[5].userName, -1);
    if(temp.length() == 0) {
        ui->label_8->colors[2] = QColor(const_color3);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_8->colors[2] = QColor(const_color_green);
            ui->label_23->setPalette(pe);
            ui->label_23->setText("== 二号琴 ==");
        } else {
            ui->label_8->colors[2] = QColor(const_color_red);
        }
    }
    str += temp;
    ui->label_8->setText(str);
    temp = QString::fromUtf16(repairForUserName->qinForUserName[6].userName, -1);
    if(temp.length() == 0) {
        ui->label_9->colors[0] = QColor(const_color1);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_9->colors[0] = QColor(const_color_green);
            ui->label_24->setPalette(pe);
            ui->label_24->setText("== 三号琴 ==");
        } else {
            ui->label_9->colors[0] = QColor(const_color_red);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[7].userName, -1);
    if(temp.length() == 0) {
        ui->label_9->colors[1] = QColor(const_color2);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_9->colors[1] = QColor(const_color_green);
            ui->label_24->setPalette(pe);
            ui->label_24->setText("== 三号琴 ==");
        } else {
            ui->label_9->colors[1] = QColor(const_color_red);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[8].userName, -1);
    if(temp.length() == 0) {
        ui->label_9->colors[2] = QColor(const_color3);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_9->colors[2] = QColor(const_color_green);
            ui->label_24->setPalette(pe);
            ui->label_24->setText("== 三号琴 ==");
        } else {
            ui->label_9->colors[2] = QColor(const_color_red);
        }
    }
    str += temp;
    ui->label_9->setText(str);
    temp = QString::fromUtf16(repairForUserName->qinForUserName[9].userName, -1);
    if(temp.length() == 0) {
        ui->label_10->colors[0] = QColor(const_color1);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_10->colors[0] = QColor(const_color_green);
            ui->label_25->setPalette(pe);
            ui->label_25->setText("== 四号琴 ==");
        } else {
            ui->label_10->colors[0] = QColor(const_color_red);
        }
    }
    str = temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[10].userName, -1);
    if(temp.length() == 0) {
        ui->label_10->colors[1] = QColor(const_color2);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_10->colors[1] = QColor(const_color_green);
            ui->label_25->setPalette(pe);
            ui->label_25->setText("== 四号琴 ==");
        } else {
            ui->label_10->colors[1] = QColor(const_color_red);
        }
    }
    str += temp;
    str += "\n";
    temp = QString::fromUtf16(repairForUserName->qinForUserName[11].userName, -1);
    if(temp.length() == 0) {
        ui->label_10->colors[2] = QColor(const_color3);
    } else {
        if(temp == ui->lineEdit_5->text()) {
            ui->label_10->colors[2] = QColor(const_color_green);
            ui->label_25->setPalette(pe);
            ui->label_25->setText("== 四号琴 ==");
        } else {
            ui->label_10->colors[2] = QColor(const_color_red);
        }
    }
    str += temp;
    ui->label_10->setText(str);
}

void MainWindow::listenTextChange() {
    connect(ui->lineEdit, &QLineEdit::textChanged, this, [ = ](QString text) {
        //qDebug("ui->lineEdit::textChanged");
        sendLessKey(0, text);
    });
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [ = ](QString text) {
        //qDebug("ui->lineEdit_2::textChanged");
        sendLessKey(1, text);
    });
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, [ = ](QString text) {
        //qDebug("ui->lineEdit_3::textChanged");
        sendLessKey(2, text);
    });
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, [ = ](QString text) {
        //qDebug("ui->lineEdit_4::textChanged");
        sendLessKey(3, text);
    });
}

void MainWindow::stopListenTextChange() {
    ui->lineEdit->disconnect(this);
    ui->lineEdit_2->disconnect(this);
    ui->lineEdit_3->disconnect(this);
    ui->lineEdit_4->disconnect(this);
}

void MainWindow::addLog(QString logMessage) {
    logLine++;
    if(logLine > 50) {
        logLine = 0;
        log.append("");
    }
    int index = log.count() - 1;
    log[index] += logMessage + "\n";
}

