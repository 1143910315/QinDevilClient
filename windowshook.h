#ifndef WINDOWSHOOK_H
#define WINDOWSHOOK_H

#include <QObject>

struct KeyboardState {
    unsigned long code;
    bool ctrl;
    bool alt;
    bool shift;
};

class WindowsHook : public QObject {
    Q_OBJECT
public:
    static WindowsHook *getInstance();
    void triggerNote1();
    void triggerNote2();
    void triggerNote3();
    void triggerNote4();
    void triggerNote5();
    void triggerClear();
    void triggerRepairNote1();
    void triggerRepairNote2();
    void triggerRepairNote3();
    void triggerRepairNote4();
    void triggerRepairNote5();
    bool ctrl = false;
    bool alt = false;
    bool shift = false;
    KeyboardState controlNote1;
    KeyboardState controlNote2;
    KeyboardState controlNote3;
    KeyboardState controlNote4;
    KeyboardState controlNote5;
    KeyboardState controlClear;
private:
    explicit WindowsHook(QObject *parent = nullptr);
    static WindowsHook *instance;
signals:
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
};

#endif // WINDOWSHOOK_H
