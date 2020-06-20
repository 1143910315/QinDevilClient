#ifndef COLORLABEL_H
#define COLORLABEL_H
#include <QLabel>
#include <QVector>
class ColorLabel : public QLabel {
    Q_OBJECT
public:
    explicit ColorLabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit ColorLabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    QVector<QColor> colors;
    bool checked;
    QColor textColor;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    bool leftClick = false;
    bool rightClick = false;
    bool cancel = false;
signals:
    void singleChecked();
    void multipleChecked(bool checked);
};

#endif // COLORLABEL_H
