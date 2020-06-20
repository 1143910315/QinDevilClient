#include "colorlabelgroup.h"

ColorLabelGroup::ColorLabelGroup(QObject *parent) : QObject(parent) {
}

void ColorLabelGroup::addColorLabel(ColorLabel *label) {
    labelList.append(label);
    label->checked = false;
    label->colors.append(QColor(192, 192, 192));
    label->repaint();
    connect(label, &ColorLabel::singleChecked, this, &ColorLabelGroup::singleChecked);
    connect(label, &ColorLabel::multipleChecked, this, &ColorLabelGroup::multipleChecked);
}

void ColorLabelGroup::resetChecked() {
    foreach(ColorLabel *label, labelList) {
        if(label->checked) {
            label->colors.clear();
            label->colors.append(QColor(192, 192, 192));
            label->checked = false;
            label->repaint();
        }
    }
}

void ColorLabelGroup::singleChecked() {
    ColorLabel *senderObject = (ColorLabel *)sender();
    for(int i = 0; i < labelList.count(); i++) {
        ColorLabel *label = labelList[i];
        if(senderObject == label) {
            if(label->checked) {
                emit repairKey(i, false);
            }
            label->colors.clear();
            label->colors.append(QColor(35, 255, 35));
            label->repaint();
            label->checked = true;
            emit repairKey(i, true);
        } else {
            if(label->checked) {
                label->colors.clear();
                label->colors.append(QColor(192, 192, 192));
                label->repaint();
                label->checked = false;
                emit repairKey(i, false);
            }
        }
    }
}

void ColorLabelGroup::multipleChecked(bool checked) {
    ColorLabel *senderObject = (ColorLabel *)sender();
    for(int i = 0; i < labelList.count(); i++) {
        ColorLabel *label = labelList[i];
        if(senderObject == label) {
            if(checked) {
                if(!label->checked) {
                    label->colors.clear();
                }
                if(label->colors.count() % 2 == 1) {
                    label->colors.append(QColor(35, 35, 255));
                } else {
                    label->colors.append(QColor(35, 255, 35));
                }
                label->checked = true;
            } else {
                label->colors.clear();
                label->colors.append(QColor(192, 192, 192));
                label->checked = false;
            }
            label->repaint();
            emit repairKey(i, checked);
        }
    }
}
