#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QVector>

class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = nullptr);
    // Plot raw data (assume raw data is an array of unsigned short values)
    void plot(const unsigned short* data, int numPoints);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<double> xData;
    QVector<double> yData;
};

#endif // DISPLAY_H
