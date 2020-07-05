#include "windowshook.h"
#include <windows.h>
WindowsHook *WindowsHook::instance = nullptr;
HHOOK mouseHook = 0;
LRESULT CALLBACK mouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if(nCode == HC_ACTION) {
        //当nCode等于HC_ACTION时，要求得到处理
        //if(wParam == WM_MOUSEWHEEL //屏蔽滑轮
        //        || wParam == WM_RBUTTONDOWN //屏蔽鼠标右键按下
        //        || wParam == WM_LBUTTONDOWN //屏蔽鼠标左键按下
        //        || wParam == WM_RBUTTONUP //屏蔽鼠标右键弹起的消息
        //        || wParam == WM_LBUTTONUP //屏蔽鼠标左键弹起的消息
        //        || wParam == WM_MOUSEMOVE) { //屏蔽鼠标的移动
        //    return true;//如果是这些事件产生的话，就返回真，即屏蔽掉这些事件，也就是安装有同类型的其他钩子，捕获不到同样的事件
        //}
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam); //否则，如果返回给下一个钩子子程处理
}
HHOOK keyboardHook = 0;
LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if(nCode == HC_ACTION) {
        WindowsHook *localHook = WindowsHook::getInstance();
        LPKBDLLHOOKSTRUCT KeyboardHookStruct = (LPKBDLLHOOKSTRUCT)lParam;
        switch(wParam) {
            case WM_KEYDOWN: {
                if(KeyboardHookStruct->vkCode == VK_LCONTROL) {
                    localHook->ctrl = true;
                } else if(KeyboardHookStruct->vkCode == VK_LMENU) {
                    localHook->alt = true;
                } else if(KeyboardHookStruct->vkCode == VK_LSHIFT) {
                    localHook->shift = true;
                }
                if(localHook->controlNote1.code == KeyboardHookStruct->vkCode && localHook->controlNote1.ctrl == localHook->ctrl && localHook->controlNote1.alt == localHook->alt && localHook->controlNote1.shift == localHook->shift) {
                    localHook->triggerNote1();
                    return 1;
                }
                if(localHook->controlNote2.code == KeyboardHookStruct->vkCode && localHook->controlNote2.ctrl == localHook->ctrl && localHook->controlNote2.alt == localHook->alt && localHook->controlNote2.shift == localHook->shift) {
                    localHook->triggerNote2();
                    return 1;
                }
                if(localHook->controlNote3.code == KeyboardHookStruct->vkCode && localHook->controlNote3.ctrl == localHook->ctrl && localHook->controlNote3.alt == localHook->alt && localHook->controlNote3.shift == localHook->shift) {
                    localHook->triggerNote3();
                    return 1;
                }
                if(localHook->controlNote4.code == KeyboardHookStruct->vkCode && localHook->controlNote4.ctrl == localHook->ctrl && localHook->controlNote4.alt == localHook->alt && localHook->controlNote4.shift == localHook->shift) {
                    localHook->triggerNote4();
                    return 1;
                }
                if(localHook->controlNote5.code == KeyboardHookStruct->vkCode && localHook->controlNote5.ctrl == localHook->ctrl && localHook->controlNote5.alt == localHook->alt && localHook->controlNote5.shift == localHook->shift) {
                    localHook->triggerNote5();
                    return 1;
                }
                if(localHook->controlClear.code == KeyboardHookStruct->vkCode && localHook->controlClear.ctrl == localHook->ctrl && localHook->controlClear.alt == localHook->alt && localHook->controlClear.shift == localHook->shift) {
                    localHook->triggerClear();
                    return 1;
                }
                break;
            }
            case WM_KEYUP: {
                //if(localHook->controlNote1.code == KeyboardHookStruct->vkCode && localHook->controlNote1.ctrl == localHook->ctrl && localHook->controlNote1.alt == localHook->alt && localHook->controlNote1.shift == localHook->shift) {
                //localHook->triggerNote1();
                //    return 1;
                //}
                //if(localHook->controlNote2.code == KeyboardHookStruct->vkCode && localHook->controlNote2.ctrl == localHook->ctrl && localHook->controlNote2.alt == localHook->alt && localHook->controlNote2.shift == localHook->shift) {
                //localHook->triggerNote2();
                //    return 1;
                //}
                //if(localHook->controlNote3.code == KeyboardHookStruct->vkCode && localHook->controlNote3.ctrl == localHook->ctrl && localHook->controlNote3.alt == localHook->alt && localHook->controlNote3.shift == localHook->shift) {
                //localHook->triggerNote3();
                //    return 1;
                //}
                //if(localHook->controlNote4.code == KeyboardHookStruct->vkCode && localHook->controlNote4.ctrl == localHook->ctrl && localHook->controlNote4.alt == localHook->alt && localHook->controlNote4.shift == localHook->shift) {
                //localHook->triggerNote4();
                //    return 1;
                //}
                //if(localHook->controlNote5.code == KeyboardHookStruct->vkCode && localHook->controlNote5.ctrl == localHook->ctrl && localHook->controlNote5.alt == localHook->alt && localHook->controlNote5.shift == localHook->shift) {
                //localHook->triggerNote5();
                //    return 1;
                //}
                //if(localHook->controlClear.code == KeyboardHookStruct->vkCode && localHook->controlClear.ctrl == localHook->ctrl && localHook->controlClear.alt == localHook->alt && localHook->controlClear.shift == localHook->shift) {
                //localHook->triggerClear();
                //    return 1;
                //}
                if(KeyboardHookStruct->vkCode == VK_LCONTROL) {
                    localHook->ctrl = false;
                } else if(KeyboardHookStruct->vkCode == VK_LMENU) {
                    localHook->alt = false;
                } else if(KeyboardHookStruct->vkCode == VK_LSHIFT) {
                    localHook->shift = false;
                }
                break;
            }
            default:
                break;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam); //否则，如果返回给下一个钩子子程处理
}
WindowsHook *WindowsHook::getInstance() {
    if(instance == nullptr) {
        instance = new WindowsHook();
        //mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseProc, GetModuleHandle(NULL), 0);
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, GetModuleHandle(NULL), 0);
    }
    return instance;
}

void WindowsHook::triggerNote1() {
    //qDebug("Note1");
    emit note1();
}

void WindowsHook::triggerNote2() {
    //qDebug("Note2");
    emit note2();
}

void WindowsHook::triggerNote3() {
    //qDebug("Note3");
    emit note3();
}

void WindowsHook::triggerNote4() {
    //qDebug("Note4");
    emit note4();
}

void WindowsHook::triggerNote5() {
    //qDebug("Note5");
    emit note5();
}

void WindowsHook::triggerClear() {
    //qDebug("Clear");
    emit clear();
}

void WindowsHook::triggerRepairNote1() {
    emit repairNote1();
}

void WindowsHook::triggerRepairNote2() {
    emit repairNote2();
}

void WindowsHook::triggerRepairNote3() {
    emit repairNote3();
}

void WindowsHook::triggerRepairNote4() {
    emit repairNote4();
}

void WindowsHook::triggerRepairNote5() {
    emit repairNote5();
}

WindowsHook::WindowsHook(QObject *parent) : QObject(parent) {
    controlNote1.code = controlNote2.code = controlNote3.code = controlNote4.code = controlNote5.code = controlClear.code = 0;
}

