#include "devicecontext.h"
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
DeviceContext::DeviceContext(QObject *parent) : QObject(parent) {
}

DeviceContext::~DeviceContext() {
    if(handleDeviceContext != 0) {
        ReleaseDC((HWND)handleWindow, (HDC)handleDeviceContext);
    }
}

bool DeviceContext::GetDeviceContext(unsigned int hwnd) {
    if(handleDeviceContext != 0) {
        ReleaseDC((HWND)hwnd, (HDC)handleDeviceContext);
    }
    handleWindow = hwnd;
    handleDeviceContext = (unsigned int)GetDC((HWND)handleWindow);
    if(handleDeviceContext == 0) {
        //qDebug("handleDeviceContext == 0");
        return false;
    }
    //qDebug("%d %d", hwnd, handleDeviceContext);
    return true;
}

bool DeviceContext::CacheRegion(const QRect &rect) {
    //qDebug("1");
    cacheRect.setRight(cacheRect.left() - 1);
    cacheRect.setBottom(cacheRect.top() - 1);
    if(rect.isNull()) {
        return false;
    }
    handleCompatibleDeviceContext = (unsigned int)CreateCompatibleDC((HDC)handleDeviceContext);
    if(handleCompatibleDeviceContext == 0) {
        return false;
    }
    int width = rect.right() - rect.left(), height = rect.bottom() - rect.top();
    //qDebug("%d %d", width, height);
    BITMAPINFO pbmi;
    pbmi.bmiHeader.biSize = 40;
    pbmi.bmiHeader.biWidth = width;
    pbmi.bmiHeader.biHeight = -height;
    pbmi.bmiHeader.biPlanes = 1;
    pbmi.bmiHeader.biBitCount = 24;
    pbmi.bmiHeader.biCompression = 0;
    pbmi.bmiHeader.biSizeImage = width * height * 3;
    unsigned char *g_pBits;
    HBITMAP g_hBmp = CreateDIBSection((HDC)handleCompatibleDeviceContext, &pbmi, DIB_RGB_COLORS, (void **)(&g_pBits), 0, 0);
    if(!g_hBmp) {
        //qDebug("byg");
        DeleteDC((HDC)handleCompatibleDeviceContext);
        return false;
    }
    void *g_hOldBmp = SelectObject((HDC)handleCompatibleDeviceContext, g_hBmp);
    BitBlt((HDC)handleCompatibleDeviceContext, 0, 0, width, height, (HDC)handleDeviceContext, rect.left(), rect.top(), SRCCOPY);
    colors.clear();
    int fill = (4 - (width * 3 % 4)) % 4;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            //qDebug("%d %d", x, y);
            byte R = g_pBits[(y * width * 3) + (x * 3) + 2 + fill * y];
            byte G = g_pBits[(y * width * 3) + (x * 3) + 1 + fill * y];
            byte B = g_pBits[(y * width * 3) + (x * 3) + fill * y];
            colors.append(QColor(R, G, B));
        }
    }
    SelectObject((HDC)handleCompatibleDeviceContext, g_hOldBmp);
    DeleteObject(g_hBmp);
    DeleteDC((HDC)handleCompatibleDeviceContext);
    cacheRect = rect;
    return true;
}

QColor DeviceContext::GetPointColor(int x, int y) {
    if(!cacheRect.isNull() && x >= cacheRect.left() && x < cacheRect.right() && y >= cacheRect.top() && y < cacheRect.bottom()) {
        return colors[x - cacheRect.left() + ((y - cacheRect.top()) * (cacheRect.right() - cacheRect.left()))];
    } else {
        return QColor(GetPixel((HDC)handleDeviceContext, x, y));
    }
}
