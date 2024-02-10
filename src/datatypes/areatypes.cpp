#include "areatypes.h"

#include <QDebug>

AreaTypes::RGB AreaTypes::RGB::fromString(const QString &value)
{
    QStringList l_rgb = value.split(",");
    if (l_rgb.size() < 3) {
        qDebug() << "Unable to parse color. Not enough fields.";
        return *this;
    }
    c_red = l_rgb[0].toInt();
    c_green = l_rgb[1].toInt();
    c_blue = l_rgb[2].toInt();

    return *this;
}

QString AreaTypes::RGB::toString() const
{
    QStringList l_rgb;
    l_rgb << QString::number(red());
    l_rgb << QString::number(green());
    l_rgb << QString::number(blue());
    return l_rgb.join(",");
}

int AreaTypes::RGB::red() const
{
    return c_red;
}

void AreaTypes::RGB::setRed(const int &value)
{
    c_red = value;
};

int AreaTypes::RGB::green() const
{
    return c_green;
};

void AreaTypes::RGB::setGreen(const int &value)
{
    c_green = value;
}

int AreaTypes::RGB::blue() const
{
    return c_blue;
}

void AreaTypes::RGB::setBlue(const int &value)
{
    c_blue = value;
}
