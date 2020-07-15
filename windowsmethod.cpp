#include "windowsmethod.h"
#include <windows.h>
#include <winuser.h>
#include <QFile>
#include <QTextStream>
windowsMethod::windowsMethod(QObject *parent) : QObject(parent) {
}

long windowsMethod::a() {
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings); //结构大小
    dmScreenSettings.dmPelsHeight = 600; //屏幕的高
    dmScreenSettings.dmPelsWidth = 800; //屏幕的宽
    dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    //DISP_CHANGE_BADDUALVIEW;
    //DISP_CHANGE_BADFLAGS;
    //DISP_CHANGE_BADMODE;
    return ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
}

unsigned int windowsMethod::GetWuXiaProcess() {
    //QFile outFile("shanchu.txt");
    //outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    //QTextStream ts(&outFile);
    //HWND topWindow1 = GetTopWindow(0);
    //while(topWindow1 != 0) {
    //    HWND parent1 = GetParent(topWindow1);
    //    int windowTextLength1 = GetWindowTextLength(topWindow1);
    //    LPTSTR a1 = new TCHAR[windowTextLength1 + 1];
    //    GetWindowText(topWindow1, a1, windowTextLength1 + 1);
    //    QString localFromUtf16 = QString::fromUtf16((char16_t *)a1);
    //    RECT r;
    //    r.top = 0;
    //    r.left = 0;
    //    r.bottom = 0;
    //    r.right = 0;
    //    GetWindowRect(topWindow1, &r);
    //    ts << QString::number((int)topWindow1) << "|" << QString::number((int)parent1) << "|" << localFromUtf16 << "|" << QString::number(r.left) << "|" << QString::number(r.top) << "|" << QString::number(r.right) << "|" << QString::number(r.bottom) << "\n";
    //     delete[] a1;
    //     topWindow1 = GetWindow(topWindow1, GW_HWNDNEXT);
    //}
    //int i = 0;
    HWND topWindow = GetTopWindow(0);
    while(topWindow != 0) {
        //for (int i = 0; i < process.Length; i++) {
        //    if (topWindow.Equals(process[i].MainWindowHandle)) {
        //        return process[i];
        //    }
        //}
        //i++;
        HWND parent = GetParent(topWindow);
        if(parent == 0) {
            int windowTextLength = GetWindowTextLength(topWindow);
            if(windowTextLength == 5) {
                LPTSTR a = new TCHAR[windowTextLength + 1];
                GetWindowText(topWindow, a, windowTextLength + 1);
                QString localFromUtf16 = QString::fromUtf16((char16_t *)a);
                if(localFromUtf16 == "天涯明月刀") {
                    //ts << QString("非超退出") << QString::number(i);
                    //ts.flush();
                    delete[] a;
                    return (unsigned int)topWindow;
                }
                delete[] a;
                //qDebug("%s", localFromUtf16.toStdString().data());
            }
        }
        topWindow = GetWindow(topWindow, GW_HWNDNEXT);
    }
    //ts << QString("超退出！");
    //ts.flush();
    return 0;
}

QRect windowsMethod::GetWinRect(unsigned int windowHandle) {
    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = 0;
    rect.right = 0;
    GetWindowRect((HWND)windowHandle, &rect);
    QRect r;
    r.setX(rect.left);
    r.setY(rect.top);
    r.setRight(rect.right);
    r.setBottom(rect.bottom);
    return r;
}

bool windowsMethod::ClientPointToScreen(unsigned int windowHandle, QPoint &p) {
    POINT point;
    point.x = p.x();
    point.y = p.y();
    if(ClientToScreen((HWND)windowHandle, &point)) {
        p.setX(point.x);
        p.setY(point.y);
        return true;
    } else {
        return false;
    }
}

void windowsMethod::KeybdEvent(unsigned char keyId, int keyState) {
    //Keybd_event(49, MapVirtualKeyA(49, 0), 8, 0);
    keybd_event(keyId, MapVirtualKeyA(keyId, 0), keyState + 8, 0);
}







