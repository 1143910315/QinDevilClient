#include "mainwindow.h"
#include "dialog.h"
#include "logdialog.h"
#include "ui_mainwindow.h"
#include "lesskeyvalidator.h"
#include "windowshook.h"
#include "windowsmethod.h"
#include "doubleclicklineedit.h"
#include "devicecontext.h"
#include "password.h"
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
#include <QTime>
#include <QRandomGenerator>
//#include <winuser.h>
//constexpr auto ipHost = "127.0.0.1";
//constexpr auto ipPort = 12580;
//constexpr auto ipHost = "q1143910315.gicp.net";
constexpr auto ipHost = "a20v933449.imwork.net";
//constexpr auto ipHost = "103.46.128.49";
//constexpr auto ipPort = 11866;
//constexpr auto ipHost ="116.62.125.206";
constexpr int discern_timer_interval = 900;
constexpr int hit_key_timer_interval = 150;
#define const_color1 231,231,231
#define const_color2 221,221,221
#define const_color3 214,213,213
#define const_color_red 231,51,82
#define const_color_green 49,160,0
#define const_gong_light_color 192,80,78
#define const_shang_light_color 156,188,89
#define const_jue_light_color 129,101,162
#define const_zhi_light_color 75,172,197
#define const_yu_light_color 246,150,71
#define const_gong_dark_color 48,20,19
#define const_shang_dark_color 39,47,22
#define const_jue_dark_color 32,25,40
#define const_zhi_dark_color 18,43,49
#define const_yu_dark_color 62,37,18
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
    pMenu->addAction(ui->action6);
    QMenu *pMenu2 = pMenu->addMenu("自动报缺");
    pMenu2->addAction(ui->action4_0);
    pMenu2->addAction(ui->action4_1);
    pMenu2->addAction(ui->action4_2);
    pMenu2->addAction(ui->action4_3);
    pMenu2->addAction(ui->action4_4);
    pMenu2 = pMenu->addMenu("自动弹琴");
    pMenu2->addAction(ui->action5_0);
    pMenu2->addAction(ui->action5_1);
    pMenu2->addAction(ui->action5_2);
    pMenu2->addAction(ui->action5_3);
    pMenu2->addAction(ui->action5_4);
    ui->action4_0->setChecked(true);
    ui->action5_0->setChecked(true);
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
                windowHandle()->setParent(nullptr);
            } else {
                QWindow *w = QWindow::fromWinId(windowsMethod::GetWuXiaProcess());
                windowHandle()->setParent(w);
            }
        } else {
            //QWindow *w = QWindow::fromWinId(0);
            windowHandle()->setParent(nullptr);
            setAttribute(Qt::WA_TranslucentBackground, true);
            setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
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
    connect(ui->action4_0, &QAction::triggered, this, &MainWindow::autoLessKeyControl);
    connect(ui->action4_1, &QAction::triggered, this, &MainWindow::autoLessKeyControl);
    connect(ui->action4_2, &QAction::triggered, this, &MainWindow::autoLessKeyControl);
    connect(ui->action4_3, &QAction::triggered, this, &MainWindow::autoLessKeyControl);
    connect(ui->action4_4, &QAction::triggered, this, &MainWindow::autoLessKeyControl);
    connect(ui->action5_0, &QAction::triggered, this, &MainWindow::autoPlayKeyControl);
    connect(ui->action5_1, &QAction::triggered, this, &MainWindow::autoPlayKeyControl);
    connect(ui->action5_2, &QAction::triggered, this, &MainWindow::autoPlayKeyControl);
    connect(ui->action5_3, &QAction::triggered, this, &MainWindow::autoPlayKeyControl);
    connect(ui->action5_4, &QAction::triggered, this, &MainWindow::autoPlayKeyControl);
    connect(ui->action6, &QAction::triggered, [&]() {
        Password *d = new Password(this);
        d->port = this->ipPort;
        d->exec();
        this->ipPort = d->port;
        delete d;
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
    discernTimer = new QTimer(this);
    discernTimer->setSingleShot(true);
    connect(discernTimer, &QTimer::timeout, this, &MainWindow::discernTimer_Elapsed);
    hitKeyTimer = new QTimer(this);
    hitKeyTimer->setSingleShot(true);
    connect(hitKeyTimer, &QTimer::timeout, this, &MainWindow::hitKeyTimer_Elapsed);
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
            if(hitKeyTimerOnRun == false && !ui->action5_0->isChecked()) {
                hitKeyTimerOnRun = true;
                hitKeyTimer->start(hit_key_timer_interval);
            }
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
            playKeystr = "                  ";
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
            hitKeyIndex = 0;
            hitKeyRole = 0;
            if(!ui->action4_0->isChecked()) {
                discernTimer->start(discern_timer_interval);
            }
            if(!ui->action5_0->isChecked()) {
                hitKeyTimerOnRun = false;
                hitKeyTimer->stop();
            }
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
        case 7: {
            hitKeyRole = 1;
            hitKeyTimer->start(hit_key_timer_interval);
            break;
        }
        case 8: {
            structure_askHitKeyIndex *receiveData = (structure_askHitKeyIndex *)data;
            structure_replyHitKeyIndex sendData;
            hitKeyRole = -1;
            hitKeyTimer->stop();
            sendData.clientId = receiveData->clientId;
            sendData.index = hitKeyIndex;
            sendData.time = receiveData->time;
            Buffer *sendBuff = client->getSendBuffer(8, sizeof(sendData));
            client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
            client->sendBuffer(sendBuff);
            break;
        }
        case 9: {
            structure_hitKeyIndex *receiveData = (structure_hitKeyIndex *)data;
            hitKeyRole = 2;
            hitKeyIndex = receiveData->index;
            int cd = timer.elapsed() - receiveData->time;
            if(cd < 1) {
                cd = 0;
            } else if(cd > 999) {
                cd = 999;
            };
            hitKeyTimer->start(1000 - cd);
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
    //qDebug("error:%d", socketError);
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
    //qDebug("disconnected");
    pingTimer->stop();
    nowConnected = false;
    connectTimer->start(2000);
    addLog("因外部原因，连接服务器的通道被关闭");
    //client->connectToHost(ipHost, ipPort);
}

void MainWindow::sendPing() {
    //findKillingIntentionStrip();
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

void MainWindow::autoLessKeyControl(bool checked) {
    //qDebug("123456");
    (void)checked;
    ui->action4_0->setChecked(false);
    ui->action4_1->setChecked(false);
    ui->action4_2->setChecked(false);
    ui->action4_3->setChecked(false);
    ui->action4_4->setChecked(false);
    QAction *senderObject = (QAction *)sender();
    senderObject->setChecked(true);
    if(!ui->action4_0->isChecked()) {
        discernTimer->start(discern_timer_interval);
    }
}

void MainWindow::autoPlayKeyControl(bool checked) {
    (void)checked;
    hitKeyTimerOnRun = false;
    ui->action5_0->setChecked(false);
    ui->action5_1->setChecked(false);
    ui->action5_2->setChecked(false);
    ui->action5_3->setChecked(false);
    ui->action5_4->setChecked(false);
    QAction *senderObject = (QAction *)sender();
    senderObject->setChecked(true);
    if(!ui->action5_0->isChecked()) {
        hitKeyTimerOnRun = true;
        hitKeyTimer->start(hit_key_timer_interval);
    }
}

void MainWindow::discernTimer_Elapsed() {
    //qDebug("123456789");
    if(precondition()) {
        //qDebug("1234567890");
        char lessKey[5] {};
        char findResult = findLessKey(lessKey);
        //qDebug("%d | %d %d %d %d %d", (int)findResult, (int)lessKey[0], (int)lessKey[1], (int)lessKey[2], (int)lessKey[3], (int)lessKey[4]);
        if(findResult == 1) {
            QString lessStr = "";
            for(int i = 0; i < 5; i++) {
                if(lessKey[i] == -1) {
                    lessStr += '1' + i;
                }
            }
            if(ui->action4_1->isChecked()) {
                ui->lineEdit->setText(lessStr);
            } else if(ui->action4_2->isChecked()) {
                ui->lineEdit_2->setText(lessStr);
            } else if(ui->action4_3->isChecked()) {
                ui->lineEdit_3->setText(lessStr);
            } else if(ui->action4_4->isChecked()) {
                ui->lineEdit_4->setText(lessStr);
            }
            return;
        }
    }
    if(!ui->action4_0->isChecked()) {
        discernTimer->start(discern_timer_interval);
    }
}

void MainWindow::hitKeyTimer_Elapsed() {
    //qDebug("%d %d", hitKeyRole, hitKeyIndex);
    if(hitKeyRole == 2) {
        hitkey();
    } else if(hitKeyRole == -1) {
        return;
        //} else {
    } else if(precondition()) {
        char lessKey[5];
        char findResult = findLessKey(lessKey);
        if(findResult >= 0) {
            //if(true) {
            if(hitKeyRole == 0) {
                structure_hitKeyNumber sendData;
                if(ui->action5_1->isChecked()) {
                    sendData.qinId = 0;
                } else if(ui->action5_2->isChecked()) {
                    sendData.qinId = 1;
                } else if(ui->action5_3->isChecked()) {
                    sendData.qinId = 2;
                } else if(ui->action5_4->isChecked()) {
                    sendData.qinId = 3;
                } else {
                    return;
                }
                sendData.time = timer.elapsed();
                Buffer *sendBuff = client->getSendBuffer(7, sizeof(sendData));
                client->writeBuffer(&sendBuff, (char *)&sendData, sizeof(sendData));
                client->sendBuffer(sendBuff);
                return;
            } else if(hitKeyRole == 1) {
                hitkey();
            }
        }
    }
    if(!ui->action5_0->isChecked()) {
        hitKeyTimer->start(hit_key_timer_interval);
    }
}

void MainWindow::hitkey() {
    if(hitKeyIndex < 9) {
        const QChar c = playKeystr.at(hitKeyIndex * 2);
        hitKeyIndex++;
        int msec = QRandomGenerator::global()->bounded(20, 60);
        if(c == '1') {
            windowsMethod::KeybdEvent(49, 0);
            QTime dieTime = QTime::currentTime().addMSecs(msec);
            while(QTime::currentTime() < dieTime) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, msec);
            }
            windowsMethod::KeybdEvent(49, 2);
        } else if(c == '2') {
            windowsMethod::KeybdEvent(50, 0);
            QTime dieTime = QTime::currentTime().addMSecs(msec);
            while(QTime::currentTime() < dieTime) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, msec);
            }
            windowsMethod::KeybdEvent(50, 2);
        } else if(c == '3') {
            windowsMethod::KeybdEvent(51, 0);
            QTime dieTime = QTime::currentTime().addMSecs(msec);
            while(QTime::currentTime() < dieTime) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, msec);
            }
            windowsMethod::KeybdEvent(51, 2);
        } else if(c == '4') {
            windowsMethod::KeybdEvent(52, 0);
            QTime dieTime = QTime::currentTime().addMSecs(msec);
            while(QTime::currentTime() < dieTime) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, msec);
            }
            windowsMethod::KeybdEvent(52, 2);
        } else if(c == '5') {
            windowsMethod::KeybdEvent(53, 0);
            QTime dieTime = QTime::currentTime().addMSecs(msec);
            while(QTime::currentTime() < dieTime) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, msec);
            }
            windowsMethod::KeybdEvent(53, 2);
        } else {
            hitKeyIndex--;
        }
    } else {
        hitKeyRole = -1;
    }
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

bool MainWindow::precondition() {
    if(FiveToneReady == false) {
        if(killingIntentionStrip == 0 || preconditionTimes > 5) {
            int localFindKillingIntentionStrip = findKillingIntentionStrip();
            if(localFindKillingIntentionStrip > 0) {
                killingIntentionStrip = localFindKillingIntentionStrip;
            }
            //qDebug("!!%d", localFindKillingIntentionStrip);
            preconditionTimes = 0;
        } else  {
            if(!findKeyPosition()) {
                preconditionTimes++;
            }
        }
    }
    //qDebug("%d!!", FiveToneReady ? 1 : 0);
    return FiveToneReady;
}

bool MainWindow::getWuXiaPosition(int &x, int &y, int &width, int &height) {
    unsigned int i = windowsMethod::GetWuXiaProcess();
    if(i != 0) {
        QRect rect = windowsMethod::GetWinRect(i);
        //qDebug("%d %d %d %d", rect.x(), rect.y(), rect.right(), rect.bottom());
        if(rect.bottom() > 100 && rect.right() > 100) {
            QPoint point;
            point.setX(0);
            point.setY(0);
            if(windowsMethod::ClientPointToScreen(i, point)) {
                x = point.x();
                y = point.y();
                width = rect.right();
                height = rect.bottom();
                return true;
                //qDebug("%d %d %d %d", x, y, width, height);
            }
        }
    }
    return false;
}

int MainWindow::findKillingIntentionStrip() {
    int x, y, width, height;
    //qDebug("asdf");
    if(getWuXiaPosition(x, y, width, height)) {
        int startX = x + (width / 2);
        int endX = startX + 1;
        int startY = y;
        int endY = y + height;
        //qDebug("--%d %d %d %d", startX, startY, endX, endY);
        DeviceContext DC;
        if(DC.GetDeviceContext(0)) {
            QRect cacheRect;
            cacheRect.setX(startX);
            cacheRect.setY(startY);
            cacheRect.setRight(endX);
            cacheRect.setBottom(endY);
            DC.CacheRegion(cacheRect);
            //qDebug("--%d %d %d %d", startX, startY, endX, endY);
            QColor color = QColor(254, 184, 0);
            for(int i = endY - 1; i > startY; i--) {
                QColor color2 = DC.GetPointColor(startX, i);
                //addLog(QString::asprintf("%d", i));
                if(GetYUVVariance(color, color2) < 5) {
                    //qDebug("--%d", height - i + y);
                    return height - i + y;
                }
            }
        }
    }
    //addLog(QString::asprintf("%d %d %d %d", winRect.x(), winRect.y(), winRect.right(), winRect.bottom()));
    return 0;
}

int MainWindow::GetYUVVariance(const QColor &c1, const QColor &c2) {
    int a = c1.alpha() - c2.alpha();
    //return AYUVColor.FromAYUV(A, 0.299 * R + 0.587 * G + 0.114 * B, -0.147 * R - 0.289 * G + 0.436 * B, 0.615 * R - 0.515 * G - 0.100 * B);
    double Y1 = 0.299 * c1.red() + 0.587 * c1.green() + 0.114 * c1.blue();
    double Y2 = 0.299 * c2.red() + 0.587 * c2.green() + 0.114 * c2.blue();
    double U1 = -0.147 * c1.red() - 0.289 * c1.green() + 0.436 * c1.blue();
    double U2 = -0.147 * c2.red() - 0.289 * c2.green() + 0.436 * c2.blue();
    double V1 = 0.615 * c1.red() - 0.515 * c1.green() - 0.100 * c1.blue();
    double V2 = 0.615 * c2.red() - 0.515 * c2.green() - 0.100 * c2.blue();
    double y = Y1 - Y2;
    double u = U1 - U2;
    double v = V1 - V2;
    return a * a + y * y + u * u + v * v;
}

bool MainWindow::findKeyPosition() {
    int x, y, width, height;
    if(getWuXiaPosition(x, y, width, height)) {
        QColor qinKeyColor[5];
        qinKeyColor[0] = QColor(const_gong_light_color);
        qinKeyColor[1] = QColor(const_shang_light_color);
        qinKeyColor[2] = QColor(const_jue_light_color);
        qinKeyColor[3] = QColor(const_zhi_light_color);
        qinKeyColor[4] = QColor(const_yu_light_color);
        int startX = x;
        int endX = x + (width / 2);
        int middleY = y + height - (killingIntentionStrip / 2);
        int startY = middleY - 5;
        int endY = startY + 10;
        DeviceContext DC;
        if(DC.GetDeviceContext(0)) {
            QRect cacheRect;
            cacheRect.setX(startX);
            cacheRect.setY(startY);
            cacheRect.setRight(endX);
            cacheRect.setBottom(endY);
            DC.CacheRegion(cacheRect);
            int tempFiveTone[5];
            int i = endX;
            for(int j = 4; j > -1;) {
                for(; i > startX; i--) {
                    QColor color = DC.GetPointColor(i, middleY);
                    if(GetYUVVariance(color, qinKeyColor[j]) < 25) {
                        int matchTime = 1;
                        for(int k = 0; k < 8; k++) {
                            color = DC.GetPointColor(i, middleY - k - 1);
                            if(matchTime < 8 && GetYUVVariance(color, qinKeyColor[j]) < 25) {
                                matchTime += 1;
                            } else {
                                break;
                            }
                        }
                        for(int k = 1; k < 8; k++) {
                            color = DC.GetPointColor(i, middleY + k);
                            if(matchTime < 8 && GetYUVVariance(color, qinKeyColor[j]) < 25) {
                                matchTime += 1;
                            } else {
                                break;
                            }
                        }
                        if(matchTime > 7) {
                            tempFiveTone[j] = i - x;
                            if(j == 0) {
                                FiveTone[0] = tempFiveTone[0];
                                FiveTone[1] = tempFiveTone[1];
                                FiveTone[2] = tempFiveTone[2];
                                FiveTone[3] = tempFiveTone[3];
                                FiveTone[4] = tempFiveTone[4];
                                //addLog(QString::asprintf("%d %d %d %d %d", FiveTone[0], FiveTone[1], FiveTone[2], FiveTone[3], FiveTone[4]));
                                FiveToneReady = true;
                                //gameData.FiveTone = tempFiveTone;
                                //gameData.FiveToneReady = true;
                                //Dispatcher.Invoke(() => {
                                //    combo.IsEnabled = true;
                                //});
                                //lock(sendData) {
                                //    sendData.Clear();
                                //    SerializeTool.IntToByteList(gameData.FiveTone[0], sendData);
                                //    SerializeTool.IntToByteList(gameData.FiveTone[1], sendData);
                                //    SerializeTool.IntToByteList(gameData.FiveTone[2], sendData);
                                //    SerializeTool.IntToByteList(gameData.FiveTone[3], sendData);
                                //    SerializeTool.IntToByteList(gameData.FiveTone[4], sendData);
                                //    client.SendPackage(12, sendData.ToArray());
                                //}
                                return true;
                            }
                            break;
                        }
                    }
                }
                j--;
            }
        }
    }
    return false;
}

char MainWindow::findLessKey(char (&keyLessState)[5]) {
    int x, y, width, height;
    if(getWuXiaPosition(x, y, width, height)) {
        QColor qinKeyColor [10];
        qinKeyColor[0] = QColor(const_gong_light_color);
        qinKeyColor[1] = QColor(const_shang_light_color);
        qinKeyColor[2] = QColor(const_jue_light_color);
        qinKeyColor[3] = QColor(const_zhi_light_color);
        qinKeyColor[4] = QColor(const_yu_light_color);
        qinKeyColor[5] = QColor(const_gong_dark_color);
        qinKeyColor[6] = QColor(const_shang_dark_color);
        qinKeyColor[7] = QColor(const_jue_dark_color);
        qinKeyColor[8] = QColor(const_zhi_dark_color);
        qinKeyColor[9] = QColor(const_yu_dark_color);
        DeviceContext DC ;
        if(DC.GetDeviceContext(0)) {
            QRect cacheRect;
            cacheRect.setX(x + FiveTone[0] - 5);
            cacheRect.setY(y + height - (killingIntentionStrip / 2));
            cacheRect.setRight(x + FiveTone[4] + 1);
            cacheRect.setBottom(y + height - (killingIntentionStrip / 2) + 1);
            DC.CacheRegion(cacheRect);
            //_ = DC.CacheRegion(new DeviceContext.Rect { left = point.x + gameData.FiveTone[0] - 5, right = point.x + gameData.FiveTone[4] + 1, top = point.y + rect.bottom - (gameData.KillingIntentionStrip / 2), bottom = point.y + rect.bottom - (gameData.KillingIntentionStrip / 2) + 1 });
            int success = 0;
            int fail = 0;
            //string lessKey = "";
            for(int i = 0; i < 5; i++) {
                //qDebug("12");
                QColor color = DC.GetPointColor(x + FiveTone[i], y + height - (killingIntentionStrip / 2));
                //qDebug("%d %d", x + FiveTone[i], y + height - (killingIntentionStrip / 2));
                //qDebug("%d %d %d", color.red(), color.green(), color.blue());
                //qDebug("%d %d %d", qinKeyColor[i].red(), qinKeyColor[i].green(), qinKeyColor[i].blue());
                if(GetYUVVariance(color, qinKeyColor[i]) < 25) {
                    success++;
                    keyLessState[i] = 1;
                } else if(GetYUVVariance(color, qinKeyColor[i + 5]) < 25) {
                    fail++;
                    keyLessState[i] = -1;
                    //lessKey += (i + 1).ToString();
                } else {
                    for(int m = 1; m < 5; m++) {
                        color = DC.GetPointColor(x + FiveTone[i] - m, y + height - (killingIntentionStrip / 2));
                        if(GetYUVVariance(color, qinKeyColor[i]) < 25) {
                            success++;
                            keyLessState[i] = 1;
                            break;
                        } else if(GetYUVVariance(color, qinKeyColor[i + 5]) < 25) {
                            fail++;
                            keyLessState[i] = -1;
                            //lessKey += (i + 1).ToString();
                            break;
                        }
                    }
                }
            }
            if(success + fail == 5) {
                if(fail > 0 && fail < 4) {
                    return 1;
                    //if (AutoLessKey) {
                    //    //Dispatcher.Invoke(() => {
                    //    //    switch (combo.SelectedIndex) {
                    //    //        case 0:
                    //    //            gameData.No1Qin = lessKey;
                    //    //            client.SendPackage(1, SerializeTool.StringToByte(gameData.No1Qin));
                    //    //            break;
                    //    //        case 1:
                    //    //            gameData.No2Qin = lessKey;
                    //    //            client.SendPackage(2, SerializeTool.StringToByte(gameData.No2Qin));
                    //    //            break;
                    //    //        case 2:
                    //    //            gameData.No3Qin = lessKey;
                    //    //            client.SendPackage(3, SerializeTool.StringToByte(gameData.No3Qin));
                    //    //            break;
                    //    //        case 3:
                    //    //            gameData.No4Qin = lessKey;
                    //    //            client.SendPackage(4, SerializeTool.StringToByte(gameData.No4Qin));
                    //    //            break;
                    //    //        default:
                    //    //            break;
                    //    //    }
                    //    //});
                    //}
                    //client.SendPackage(13, SerializeTool.StringToByte(lessKey));
                    //return;
                }
                return 0;
            } else if(success + fail > 3) {
                return 2;
                //if (discernTimers++ < 5) {
                //    lock (sendData) {
                //        sendData.Clear();
                //        SerializeTool.IntToByteList(success, sendData);
                //        SerializeTool.IntToByteList(fail, sendData);
                //        for (int i = 0; i < 5; i++) {
                //            ARGBColor color = ARGBColor.FromInt(DC.GetPointColor(point.x + gameData.FiveTone[i], point.y + rect.bottom - (gameData.KillingIntentionStrip / 2)));
                //            SerializeTool.IntToByteList(color.R, sendData);
                //            SerializeTool.IntToByteList(color.G, sendData);
                //            SerializeTool.IntToByteList(color.B, sendData);
                //        }
                //        client.SendPackage(16, sendData.ToArray());
                //    }
                //}
            }
        }
    }
    return -1;
}

