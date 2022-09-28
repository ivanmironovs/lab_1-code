#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>
#include <QColorDialog>
#include <QBrush>
#include <QColor>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QIcon>
#include <QtGlobal>
#include <QtCore/qmath.h>
#include <QSlider>
#include <QMessageBox>

class Widget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *arrow_1;
    QLabel *arrow_2;
    QComboBox *model_1;
    QComboBox *model_2;
    QComboBox *model_3;
    QPushButton *colorButton;
    QPushButton *coordinateButton;
    QLineEdit *modelLine_1;
    QLineEdit *modelLine_2;
    QLineEdit *modelLine_3;
    QBrush brush;
    QColorDialog *color;

    QHBoxLayout *lineEditLayout;
    QHBoxLayout *modelsLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *mainLayout;


private slots:
    void setColorPalette();
    void comboBox_1_IndexChanged();
    void comboBox_2_IndexChanged();
    void comboBox_3_IndexChanged();
    QVector<double> getRGB();
    QVector<double> getCMYK();
    QVector<double> getHSV();
    QVector<double> getHLS();
    QVector<double> getXYZ();
    QVector<double> getLAB();
    void model1_coordinateRecording();
    void model2_coordinateRecording();
    void model3_coordinateRecording();
    double Fx(double x);
    double Fl(double l);
    double Hue2RGB(double v1, double v2, double vH);
    QColor fromCMYKtoRGB(double c, double m, double y, double k);
    QColor fromHSVtoRGB(double h, double s, double v);
    QColor fromHLStoRGB(double h, double l, double s);
    QColor fromXYZtoRGB(double x, double y, double z);
    QColor fromLABtoRGB(double l, double a, double b);
    double Fr(double x);
    double Fg(double l);
    void enterCoordinate();
    void on_modelLine_1_textEdited(const QString &arg1);
    void on_modelLine_2_textEdited(const QString &arg2);
    void on_modelLine_3_textEdited(const QString &arg3);
};
#endif // WIDGET_H
