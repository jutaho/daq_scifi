#include "display.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

Display::Display(QWidget *parent)
    : QWidget(parent)
{
}

void Display::plot(const unsigned short* data, int numPoints)
{
    xData.resize(numPoints);
    yData.resize(numPoints);
    for (int i = 0; i < numPoints; i++) {
        xData[i] = i;
        yData[i] = data[i];
    }
    update();
}

void Display::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if (xData.isEmpty() || yData.isEmpty())
        return;

    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::green);

    // Simple scaling: assume raw data ranges from 0 to maxVal
    double maxVal = 0;
    for (double v : yData)
        if (v > maxVal) maxVal = v;
    if (maxVal == 0) maxVal = 1;

    int w = width();
    int h = height();
    double xScale = (double)w / (xData.size() - 1);
    double yScale = (double)h / maxVal;

    QPainterPath path;
    path.moveTo(0, h - yData[0]*yScale);
    for (int i = 1; i < xData.size(); i++) {
        path.lineTo(i * xScale, h - yData[i]*yScale);
    }
    painter.drawPath(path);
}
