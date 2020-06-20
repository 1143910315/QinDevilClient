#ifndef COLORLABELGROUP_H
#define COLORLABELGROUP_H
#include "colorlabel.h"
class ColorLabelGroup : public QObject {
    Q_OBJECT
public:
    explicit ColorLabelGroup(QObject *parent = nullptr);
    void addColorLabel(ColorLabel *label);
    void resetChecked();
protected slots:
    void singleChecked();
    void multipleChecked(bool checked);
private:
    QVector<ColorLabel *>labelList;
signals:
    void repairKey(int keyId, bool isChecked);
};

#endif // COLORLABELGROUP_H
