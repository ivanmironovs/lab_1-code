#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(500, 200, 500, 500);
    setMinimumSize(500, 500);
    setMaximumSize(500, 500);

    model_1 = new QComboBox;
    model_2 = new QComboBox;
    model_3 = new QComboBox;
    arrow_1 = new QLabel;
    arrow_2 = new QLabel;
    colorButton = new QPushButton;
    coordinateButton = new QPushButton;
    modelLine_1 = new QLineEdit;
    modelLine_2 = new QLineEdit;
    modelLine_3 = new QLineEdit;
    mainLayout = new QVBoxLayout;
    modelsLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    lineEditLayout = new QHBoxLayout;

    modelLine_1->clear();
    modelLine_2->clear();
    modelLine_3->clear();

    arrow_1->setText("<->");
    arrow_2->setText("<->");
    colorButton->setText("Change color");
    coordinateButton->setText("Enter coordinates");

    model_1->addItem("");
    model_1->addItem(QIcon(":/rec/modelicon/RGB.png"), "RGB");
    model_1->addItem(QIcon(":/rec/modelicon/CMYK.png"), "CMYK");
    model_1->addItem(QIcon(":/rec/modelicon/HSV.png"), "HSV");
    model_1->addItem(QIcon(":/rec/modelicon/HLS.png"), "HLS");
    model_1->addItem(QIcon(":/rec/modelicon/XYZ.png"), "XYZ");
    model_1->addItem(QIcon(":/rec/modelicon/LAB.png"), "LAB");

    model_2->addItem("");
    model_2->addItem(QIcon(":/rec/modelicon/RGB.png"), "RGB");
    model_2->addItem(QIcon(":/rec/modelicon/CMYK.png"), "CMYK");
    model_2->addItem(QIcon(":/rec/modelicon/HSV.png"), "HSV");
    model_2->addItem(QIcon(":/rec/modelicon/HLS.png"), "HLS");
    model_2->addItem(QIcon(":/rec/modelicon/XYZ.png"), "XYZ");
    model_2->addItem(QIcon(":/rec/modelicon/LAB.png"), "LAB");

    model_3->addItem("");
    model_3->addItem(QIcon(":/rec/modelicon/RGB.png"), "RGB");
    model_3->addItem(QIcon(":/rec/modelicon/CMYK.png"), "CMYK");
    model_3->addItem(QIcon(":/rec/modelicon/HSV.png"), "HSV");
    model_3->addItem(QIcon(":/rec/modelicon/HLS.png"), "HLS");
    model_3->addItem(QIcon(":/rec/modelicon/XYZ.png"), "XYZ");
    model_3->addItem(QIcon(":/rec/modelicon/LAB.png"), "LAB");

    lineEditLayout->addWidget(modelLine_1);
    lineEditLayout->addWidget(arrow_1);
    lineEditLayout->addWidget(modelLine_2);
    lineEditLayout->addWidget(arrow_2);
    lineEditLayout->addWidget(modelLine_3);

    modelsLayout->addWidget(model_1);
    modelsLayout->addStretch();
    modelsLayout->addWidget(model_2);
    modelsLayout->addStretch();
    modelsLayout->addWidget(model_3);

    buttonLayout->addWidget(coordinateButton);
    buttonLayout->addWidget(colorButton);

    mainLayout->addLayout(lineEditLayout);
    mainLayout->addLayout(modelsLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    modelLine_1->setEnabled(false);
    modelLine_2->setEnabled(false);
    modelLine_3->setEnabled(false);

    connect(model_1, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(comboBox_1_IndexChanged()));
    connect(model_2, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(comboBox_2_IndexChanged()));
    connect(model_3, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(comboBox_3_IndexChanged()));
    connect(colorButton, SIGNAL(clicked()), this, SLOT(setColorPalette()));
    connect(coordinateButton, SIGNAL(clicked()), this, SLOT(enterCoordinate()));
}

void Widget::enterCoordinate()
{
    if(modelLine_1->isModified()) {
        on_modelLine_1_textEdited(modelLine_1->text());
    }
    else if(modelLine_2->isModified()) {
        on_modelLine_2_textEdited(modelLine_2->text());
    }
    else if(modelLine_3->isModified()){
        on_modelLine_3_textEdited(modelLine_3->text());
    }
    model1_coordinateRecording();
    model2_coordinateRecording();
    model3_coordinateRecording();
    repaint();
}

void Widget::setColorPalette()
{
    brush.setColor(color->getColor());
    model1_coordinateRecording();
    model2_coordinateRecording();
    model3_coordinateRecording();
    repaint();

}

void Widget::comboBox_1_IndexChanged()
{
    if(model_1->currentIndex() == 0) {
        modelLine_1->setEnabled(false);
        modelLine_1->clear();
    }
    else {
        modelLine_1->setEnabled(true);
    }
    model1_coordinateRecording();
}

void Widget::comboBox_2_IndexChanged()
{
    if(model_2->currentIndex() == 0) {
        modelLine_2->setEnabled(false);
        modelLine_2->clear();
    }
    else {
        modelLine_2->setEnabled(true);
    }
    model2_coordinateRecording();
}

void Widget::comboBox_3_IndexChanged()
{
    if(model_3->currentIndex() == 0) {
        modelLine_3->setEnabled(false);
        modelLine_3->clear();
    }
    else {
        modelLine_3->setEnabled(true);
    }
    model3_coordinateRecording();
}

QVector<double> Widget::getRGB()
{
    QVector<double> resultRGB;
    double r = brush.color().red();
    double g = brush.color().green();
    double b = brush.color().blue();
    resultRGB.push_back(r);
    resultRGB.push_back(g);
    resultRGB.push_back(b);
    return resultRGB;
}

QVector<double> Widget::getCMYK()
{
    QVector<double> resultCMYK;
    double r = 1 - getRGB()[0]/255;
    double g = 1 - getRGB()[1]/255;
    double b = 1 - getRGB()[2]/255;
    double k = qMin(r, qMin(g, b));
    double c = (r - k) / (1 - k);
    double m = (g - k) / (1 - k);
    double y = (b - k) / (1 - k);
    if(c != c) {
        c = 0;
    }
    if(m != m) {
        m = 0;
    }
    if(y != y) {
        y = 0;
    }
    resultCMYK.push_back(c);
    resultCMYK.push_back(m);
    resultCMYK.push_back(y);
    resultCMYK.push_back(k);
    return resultCMYK;
}

QVector<double> Widget::getHSV()
{
    QVector<double> resultHSV;
    double r = getRGB()[0]/255;
    double g = getRGB()[1]/255;
    double b = getRGB()[2]/255;
    double min = qMin(r, qMin(g, b));
    double max = qMax(r, qMax(g, b));
    double delta = max - min;
    double h;
    if(delta == 0) {
        h = 0;
    }
    else if(max == r && g >= b) {
        h = 60 * (g - b) / delta;
    }
    else if(max == r && g < b) {
        h = 60 * (g - b) / delta + 360;
    }
    else if(max == g) {
        h = 60 * (b - r) / delta + 120;
    }
    else if(max == b) {
        h = 60 * (r - g) / delta + 240;
    }
    double s;
    if(max == 0){
        s = 0;
    }
    else {
        s = delta / max;
    }
    double v = max;
    resultHSV.push_back(h);
    resultHSV.push_back(s*100);
    resultHSV.push_back(v*100);
    return resultHSV;
}

QVector<double> Widget::getHLS()
{
    QVector<double> resultHLS;
    double r = getRGB()[0]/255;
    double g = getRGB()[1]/255;
    double b = getRGB()[2]/255;
    double min = qMin(r, qMin(g, b));
    double max = qMax(r, qMax(g, b));
    double delta = max - min;
    double h;
    if(delta == 0) {
        h = 0;
    }
    else if(max == r && g >= b) {
        h = 60 * (g - b) / delta;
    }
    else if(max == r && g < b) {
        h = 60 * (g - b) / delta + 360;
    }
    else if(max == g) {
        h = 60 * (b - r) / delta + 120;
    }
    else if(max == b) {
        h = 60 * (r - g) / delta + 240;
    }
    double l = (max + min) / 2;
    double s;
    if(delta == 0) {
        s = 0;
    }
    else {
        s = delta / (1 - qAbs(2 * l - 1));
    }
    resultHLS.push_back(h);
    resultHLS.push_back(l*100);
    resultHLS.push_back(s*100);
    return resultHLS;
}

double Widget::Fx(double x)
{
    if(x >= 0.04045) {
        return qPow((x + 0.055) / 1.055, 2.4);
    }
    else {
        return x / 12.92;
    }
}

QVector<double> Widget::getXYZ()
{
    QVector<double> resultXYZ;
    double r = Fx(getRGB()[0]/255) * 100;
    double g = Fx(getRGB()[1]/255) * 100;
    double b = Fx(getRGB()[2]/255) * 100;
    double x = 0.412453 * r + 0.357580 * g + 0.180423 * b;
    double y = 0.212671 * r + 0.715160 * g + 0.072169 * b;
    double z = 0.019334 * r + 0.119193 * g + 0.950227 * b;
    resultXYZ.push_back(x);
    resultXYZ.push_back(y);
    resultXYZ.push_back(z);
    return resultXYZ;
}

double Widget::Fl(double l)
{
    double a = 16;
    double b = 116;
    double y = 1 / 3;
    if(l >= 0.008856) {
        return qPow(l , y);
    }
    else {
        return 7.787 * l + a / b;
    }
}

QVector<double> Widget::getLAB()
{
    QVector<double> resultLAB;
    double Xw = 95.047;
    double Yw = 100;
    double Zw = 108.883;
    double x = Fl(getXYZ()[0] / Xw);
    double y = Fl(getXYZ()[1] / Yw);
    double z = Fl(getXYZ()[2] / Zw);
    double l = 116 * y - 16;                    //неправильно
    double a = 500 * (x - y);
    double b = 200 * (y - z);
    resultLAB.push_back(l);
    resultLAB.push_back(a);
    resultLAB.push_back(b);
    return resultLAB;
}

QColor Widget::fromCMYKtoRGB(double c, double m, double y, double k)
{
    double R = 255 * (1 - c) * (1 - k);
    double G = 255 * (1 - m) * (1 - k);
    double B = 255 * (1 - y) * (1 - k);
    QColor retColor = QColor::fromRgb(R, G, B);
    return retColor;
}

QColor Widget::fromHSVtoRGB(double h, double s, double v)
{
    int i = int(h) / 60;
    s = s / 100;
    v = v / 100;
    double c = v * s;
    double x = c * ( 1 - abs(int(h / 60) % 2 - 1));
    double m = v - c;
    double r, g, b;
    switch (i) {
        case 0: r = c; g = x; b = 0; break;
        case 1: r = x; g = c; b = 0; break;
        case 2: r = 0; g = c; b = x; break;
        case 3: r = 0; g = x; b = c; break;
        case 4: r = x; g = 0; b = c; break;
        case 5: r = c; g = 0; b = x; break;
    }
    double R = 255 * (r + m);
    double G = 255 * (g + m);
    double B = 255 * (b + m);
    QColor retColor = QColor::fromRgb(R, G, B);
    return retColor;
}

double Widget::Hue2RGB(double v1, double v2, double vH)
{
    if (vH < 0) vH += 1;
    if (vH > 1) vH -= 1;
    if (6.0 * vH < 1) return v1 + (v2 - v1) * 6.0 * vH;
    if (2.0 * vH < 1) return v2;
    if (3.0 * vH < 2) return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
    return (v1);
}

QColor Widget::fromHLStoRGB(double h, double l, double s)
{
    double H = h / 360, L = l /100, S = s / 100;
    double R, G, B;
    double var_1, var_2;
    if (S == 0)
    {
        R = L * 255.0;
        G = L * 255.0;
        B = L * 255.0;
    }
    else
    {
        if (L < 0.5) var_2 = L * (1 + S);
        else         var_2 = (L + S) - (S * L);

        var_1 = 2.0 * L - var_2;

        R = 255.0 * Hue2RGB(var_1, var_2, H + (1.0 / 3.0));
        G = 255.0 * Hue2RGB(var_1, var_2, H);
        B = 255.0 * Hue2RGB(var_1, var_2, H - (1.0 / 3.0));
    }
    QColor retColor = QColor::fromRgb(R, G, B);
    return retColor;
}

double Widget::Fr(double x)
{
    double r = 1 / 2.4;
    if(x >= 0.003130) {
        return qPow(1.055 * x, r) - 0.055;
    }
    else {
        return x * 12.92;
    }
}

QColor Widget::fromXYZtoRGB(double x, double y, double z)
{
    double r = 3.2406 * (x / 100) - 1.5372 * (y / 100) - 0.4986 * (z / 100);
    double g = 1.8758 * (y / 100) - 0.9689 * (x / 100) + 0.0415 * (z / 100);
    double b = 0.0557 * (x / 100) - 0.2040 * (y / 100) + 1.0570 * (z / 100);
    double R = Fr(r) * 255;
    double G = Fr(g) * 255;
    double B = Fr(b) * 255;
    QColor retColor = QColor::fromRgb(R, G, B);
    return retColor;
}

double Widget::Fg(double l)
{
    double a = 16;
    double b = 116;
    if(l >= 0.008856) {
        return qPow(l , 3);
    }
    else {
        return 7.787 * (l - a / b);
    }
}

QColor Widget::fromLABtoRGB(double l, double a, double b)
{
    double Xw = 95.047;
    double Yw = 100;
    double Zw = 108.883;
    double X = Fg(a / 500.0 + (l + 16.0)/116.0) * Yw;
    double Y = Fg((l + 16.0) / 116.0) * Xw;                                           //неправильно
    double Z = Fg((l+16.0)/116.0 - b / 200.0)* Zw;
    QColor retColor = fromXYZtoRGB(X, Y, Z);
    return retColor;
}

void Widget::on_modelLine_1_textEdited(const QString &arg1)
{
    QStringList list = arg1.split(", ");
    if(list.size() > 3 || list.size() < 3) {
        QMessageBox::warning(this, "Attention", "Incorrect data entered!");
    }
    else {
        if(model_1->currentText() == "RGB") {
            double R = list.at(0).toDouble();
            double G = list.at(1).toDouble();
            double B = list.at(2).toDouble();
            if(R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(QColor(R, G, B));
        }
        else if(model_1->currentText() == "CMYK") {
            double C = list.at(0).toDouble();
            double M = list.at(1).toDouble();
            double Y = list.at(2).toDouble();
            double K = list.at(3).toDouble();
            if(C > 1 || C < 0 || M > 1 || M < 0 || Y > 1 || Y < 0 || K > 1 || K < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromCMYKtoRGB(C, M, Y, K));
        }
        else if(model_1->currentText() == "HSV") {
            double H = list.at(0).toDouble();
            double S = list.at(1).toDouble();
            double V = list.at(2).toDouble();
            if(H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromHSVtoRGB(H, S, V));
        }
        else if(model_1->currentText() == "HLS") {
            double H = list.at(0).toDouble();
            double L = list.at(1).toDouble();
            double S = list.at(2).toDouble();
            if(H > 360 || H < 0 || L > 100 || L < 0 || S > 100 || S < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromHLStoRGB(H, L, S));
        }
        else if(model_1->currentText() == "XYZ") {
            double X = list.at(0).toDouble();
            double Y = list.at(1).toDouble();
            double Z = list.at(2).toDouble();
            if(X > 100 || X < 0 || Y > 100 || Y < 0 || Z > 100 || Z < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromXYZtoRGB(X, Y, Z));
        }
        else if(model_1->currentText() == "LAB") {
            double L = list.at(0).toDouble();
            double A = list.at(1).toDouble();
            double B = list.at(2).toDouble();
//            if(C > 1 || C < 0 || M > 1 || M < 0 || Y > 1 || Y < 0 || K > 1 || K < 0) {
//                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
//            }
            brush.setColor(fromLABtoRGB(L, A, B));
        }
    }
}

void Widget::on_modelLine_2_textEdited(const QString &arg2)
{
    QStringList list = arg2.split(", ");
    if(list.size() > 3 || list.size() < 3) {
        QMessageBox::warning(this, "Attention", "Incorrect data entered!");
    }
    else {
        if(model_2->currentText() == "RGB") {
            double R = list.at(0).toDouble();
            double G = list.at(1).toDouble();
            double B = list.at(2).toDouble();
            if(R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(QColor(R, G, B));
        }
        else if(model_2->currentText() == "CMYK") {
            double C = list.at(0).toDouble();
            double M = list.at(1).toDouble();
            double Y = list.at(2).toDouble();
            double K = list.at(3).toDouble();
            if(C > 1 || C < 0 || M > 1 || M < 0 || Y > 1 || Y < 0 || K > 1 || K < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromCMYKtoRGB(C, M, Y, K));
        }
        else if(model_2->currentText() == "HSV") {
            double H = list.at(0).toDouble();
            double S = list.at(1).toDouble();
            double V = list.at(2).toDouble();
            if(H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromHSVtoRGB(H, S, V));
        }
        else if(model_2->currentText() == "HLS") {
            double H = list.at(0).toDouble();
            double L = list.at(1).toDouble();
            double S = list.at(2).toDouble();
            if(H > 360 || H < 0 || L > 100 || L < 0 || S > 100 || S < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromHLStoRGB(H, L, S));
        }
        else if(model_2->currentText() == "XYZ") {
            double X = list.at(0).toDouble();
            double Y = list.at(1).toDouble();
            double Z = list.at(2).toDouble();
            if(X > 100 || X < 0 || Y > 100 || Y < 0 || Z > 100 || Z < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromXYZtoRGB(X, Y, Z));
        }
        else if(model_2->currentText() == "LAB") {
            double L = list.at(0).toDouble();
            double A = list.at(1).toDouble();
            double B = list.at(2).toDouble();
//            if(C > 1 || C < 0 || M > 1 || M < 0 || Y > 1 || Y < 0 || K > 1 || K < 0) {
//                QMessageBox::warning(this,"Attention", "Incorrect data entered!");
//            }
            brush.setColor(fromLABtoRGB(L, A, B));
        }
    }
}

void Widget::on_modelLine_3_textEdited(const QString &arg3)
{
    QStringList list = arg3.split(", ");
    if(list.size() > 3 || list.size() < 3) {
        QMessageBox::warning(this, "Attention", "Incorrect data entered!");
    }
    else {
        if(model_3->currentText() == "RGB") {
            double R = list.at(0).toDouble();
            double G = list.at(1).toDouble();
            double B = list.at(2).toDouble();
            if(R > 255 || R < 0 || G > 255 || G < 0 || B > 255 || B < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(QColor(R, G, B));
        }
        else if(model_3->currentText() == "CMYK") {
            double C = list.at(0).toDouble();
            double M = list.at(1).toDouble();
            double Y = list.at(2).toDouble();
            double K = list.at(3).toDouble();
            if(C > 1 || C < 0 || M > 1 || M < 0 || Y > 1 || Y < 0 || K > 1 || K < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromCMYKtoRGB(C, M, Y, K));
        }
        else if(model_3->currentText() == "HSV") {
            double H = list.at(0).toDouble();
            double S = list.at(1).toDouble();
            double V = list.at(2).toDouble();
            if(H > 360 || H < 0 || S > 100 || S < 0 || V > 100 || V < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromHSVtoRGB(H, S, V));
        }
        else if(model_3->currentText() == "HLS") {
            double H = list.at(0).toDouble();
            double L = list.at(1).toDouble();
            double S = list.at(2).toDouble();
            if(H > 360 || H < 0 || L > 100 || L < 0 || S > 100 || S < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromHLStoRGB(H, L, S));
        }
        else if(model_3->currentText() == "XYZ") {
            double X = list.at(0).toDouble();
            double Y = list.at(1).toDouble();
            double Z = list.at(2).toDouble();
            if(X > 100 || X < 0 || Y > 100 || Y < 0 || Z > 100 || Z < 0) {
                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
            }
            brush.setColor(fromXYZtoRGB(X, Y, Z));
        }
        else if(model_3->currentText() == "LAB") {
            double L = list.at(0).toDouble();
            double A = list.at(1).toDouble();
            double B = list.at(2).toDouble();
//            if(C > 1 || C < 0 || M > 1 || M < 0 || Y > 1 || Y < 0 || K > 1 || K < 0) {
//                QMessageBox::warning(this, "Attention", "Incorrect data entered!");
//            }
            brush.setColor(fromLABtoRGB(L, A, B));
        }
    }
}

void Widget::model1_coordinateRecording()
{
    if(model_1->currentIndex() == 1) {
        QString enter = QString::number(getRGB()[0]) + ", " + QString::number(getRGB()[1]) + ", " + QString::number(getRGB()[2]);
        modelLine_1->setText(enter);
    }
    else if(model_1->currentIndex() == 2) {
        QString enter = QString::number(getCMYK()[0], 'f', 2) + ", " + QString::number(getCMYK()[1], 'f', 2) + ", " + QString::number(getCMYK()[2], 'f', 2) + ", " + QString::number(getCMYK()[3], 'f', 2);
        modelLine_1->setText(enter);
    }
    else if(model_1->currentIndex() == 3) {
        QString enter = QString::number(getHSV()[0], 'f', 0) + ", " + QString::number(getHSV()[1], 'f', 0) + ", " + QString::number(getHSV()[2], 'f', 0);
        modelLine_1->setText(enter);
    }
    else if(model_1->currentIndex() == 4) {
        QString enter = QString::number(getHLS()[0], 'f', 0) + ", " + QString::number(getHLS()[1], 'f', 0) + ", " + QString::number(getHLS()[2], 'f', 0);
        modelLine_1->setText(enter);
    }
    else if(model_1->currentIndex() == 5) {
        QString enter = QString::number(getXYZ()[0], 'f', 2) + ", " + QString::number(getXYZ()[1], 'f', 2) + ", " + QString::number(getXYZ()[2], 'f', 2);
        modelLine_1->setText(enter);
    }
    else if(model_1->currentIndex() == 6) {
        QString enter = QString::number(getLAB()[0], 'f', 2) + ", " + QString::number(getLAB()[1], 'f', 2) + ", " + QString::number(getLAB()[2], 'f', 2);
        modelLine_1->setText(enter);
    }
}

void Widget::model2_coordinateRecording()
{
    if(model_2->currentIndex() == 1) {
        QString enter = QString::number(getRGB()[0]) + ", " + QString::number(getRGB()[1]) + ", " + QString::number(getRGB()[2]);
        modelLine_2->setText(enter);
    }
    else if(model_2->currentIndex() == 2) {
        QString enter = QString::number(getCMYK()[0], 'f', 2) + ", " + QString::number(getCMYK()[1], 'f', 2) + ", " + QString::number(getCMYK()[2], 'f', 2) + ", " + QString::number(getCMYK()[3], 'f', 2);
        modelLine_2->setText(enter);
    }
    else if(model_2->currentIndex() == 3) {
        QString enter = QString::number(getHSV()[0], 'f', 0) + ", " + QString::number(getHSV()[1], 'f', 0) + ", " + QString::number(getHSV()[2], 'f', 0);
        modelLine_2->setText(enter);
    }
    else if(model_2->currentIndex() == 4) {
        QString enter = QString::number(getHLS()[0], 'f', 0) + ", " + QString::number(getHLS()[1], 'f', 0) + ", " + QString::number(getHLS()[2], 'f', 0);
        modelLine_2->setText(enter);
    }
    else if(model_2->currentIndex() == 5) {
        QString enter = QString::number(getXYZ()[0], 'f', 2) + ", " + QString::number(getXYZ()[1], 'f', 2) + ", " + QString::number(getXYZ()[2], 'f', 2);
        modelLine_2->setText(enter);
    }
    else if(model_2->currentIndex() == 6) {
        QString enter = QString::number(getLAB()[0], 'f', 2) + ", " + QString::number(getLAB()[1], 'f', 2) + ", " + QString::number(getLAB()[2], 'f', 2);
        modelLine_2->setText(enter);
    }
}

void Widget::model3_coordinateRecording()
{
    if(model_3->currentIndex() == 1) {
        QString enter = QString::number(getRGB()[0]) + ", " + QString::number(getRGB()[1]) + ", " + QString::number(getRGB()[2]);
        modelLine_3->setText(enter);
    }
    else if(model_3->currentIndex() == 2) {
        QString enter = QString::number(getCMYK()[0], 'f', 2) + ", " + QString::number(getCMYK()[1], 'f', 2) + ", " + QString::number(getCMYK()[2], 'f', 2) + ", " + QString::number(getCMYK()[3], 'f', 2);
        modelLine_3->setText(enter);
    }
    else if(model_3->currentIndex() == 3) {
        QString enter = QString::number(getHSV()[0], 'f', 0) + ", " + QString::number(getHSV()[1], 'f', 0) + ", " + QString::number(getHSV()[2], 'f', 0);
        modelLine_3->setText(enter);
    }
    else if(model_3->currentIndex() == 4) {
        QString enter = QString::number(getHLS()[0], 'f', 0) + ", " + QString::number(getHLS()[1], 'f', 0) + ", " + QString::number(getHLS()[2], 'f', 0);
        modelLine_3->setText(enter);
    }
    else if(model_3->currentIndex() == 5) {
        QString enter = QString::number(getXYZ()[0], 'f', 2) + ", " + QString::number(getXYZ()[1], 'f', 2) + ", " + QString::number(getXYZ()[2], 'f', 2);
        modelLine_3->setText(enter);
    }
    else if(model_3->currentIndex() == 6) {
        QString enter = QString::number(getLAB()[0], 'f', 2) + ", " + QString::number(getLAB()[1], 'f', 2) + ", " + QString::number(getLAB()[2], 'f', 2);
        modelLine_3->setText(enter);
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawEllipse(QRect(60, 75, 380, 380));
}

Widget::~Widget()
{
}


