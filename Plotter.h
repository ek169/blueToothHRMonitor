#ifndef PLOTTER_H
#define PLOTTER_H

#include <QDialog>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QValueAxis>
#include <qqueue.h>
#include <QLabel>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
class QXYSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

using namespace QtCharts;

class Plotter : public QDialog
{
    Q_OBJECT
public:
    Plotter(const QString clientName, QDialog *parent = nullptr);

public slots:
    void addToPlot(const QString &, float);
    void updateHeartRate();

private:
    QChart *m_chart;
    QLineSeries *m_raw_series;
    QLineSeries *m_filt_series;
    long m_sample_num;
    float maxY;
    float minY;
    int maxX;
    QValueAxis * m_axisX;
    QValueAxis * m_axisY;

    QQueue<float> m_avgq;
    float q_total;

    QQueue<float> mean_filtq;
    float mean_filt_total;

    const int mean_filt_size;

    int m_largest_prev;
    const int sample_size = 1000;

    QLabel * lbl_hr;
    std::vector<float> m_hr_vect;


};

#endif // PLOTTER_H
