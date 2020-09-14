#include "Plotter.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <iostream>
#include <QTimer>
#include "peakdetection.h"
QT_CHARTS_USE_NAMESPACE


//-------------------------------------------------------------------------------------------------------------//
// CONSTRUCTOR: Plotter
//
//
//
//-------------------------------------------------------------------------------------------------------------//
Plotter::Plotter(const QString clientName, QDialog * parent) :
    QDialog(parent),
    m_chart(new QChart),
    m_raw_series(new QLineSeries()),
    m_filt_series(new QLineSeries()),
    m_sample_num(0),
    maxY(0),
    minY(0),
    maxX(1000),
    m_axisX(nullptr),
    m_axisY(nullptr),
    mean_filt_size(30),
    m_largest_prev(0)
{
    QtCharts::QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(800, 600);
    m_chart->addSeries(m_raw_series);
    m_chart->addSeries(m_filt_series);
    m_axisX = new QValueAxis;
    m_axisX->setRange(0,maxX);
    m_axisX->setLabelFormat("%g");
    m_axisX->setTitleText("Sample Number");
    m_axisY = new QValueAxis;
    m_axisY->setRange(minY, maxY);
    m_filt_series->setPen(QPen(QColor("red")));
    m_filt_series->setName("Filtered Signal");
    m_raw_series->setPen(QPen(QColor("blue")));
    m_raw_series->setName("Raw Signal");

    m_chart->addAxis(m_axisX, Qt::AlignBottom);
    m_raw_series->attachAxis(m_axisX);
    m_filt_series->attachAxis(m_axisX);


    m_chart->addAxis(m_axisY, Qt::AlignLeft);

    m_raw_series->attachAxis(m_axisY);
    m_filt_series->attachAxis(m_axisY);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    m_chart->setTitle(QString("Heart Monitor For %1").arg(clientName));

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Plotter::updateHeartRate);
    timer->start(10000);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout(this);
    QLabel * currentHr = new QLabel("Current Heart Rate: ");
    topLayout->addWidget(currentHr);
    lbl_hr = new QLabel();
    topLayout->addWidget(lbl_hr);
    QWidget * topWidget = new QWidget();
    topWidget->setLayout(topLayout);
    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}

//-------------------------------------------------------------------------------------------------------------//
// SLOT: addToPlot
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void Plotter::addToPlot(const QString &, float val)
{
    float filt_val, front;
    // add value to average filter buffer
    m_avgq.append(val);
    q_total += val;

    // if we'eve reached out sample size
    if(m_avgq.size() == sample_size)
    {
        front = m_avgq.front();
        m_avgq.pop_front();
        q_total -= front;
        val = val - (q_total/m_avgq.size());
        m_raw_series->append(m_sample_num, val);

        mean_filtq.append(val);
        mean_filt_total += val;
        if(mean_filtq.size() == mean_filt_size)
        {
            filt_val = mean_filt_total/mean_filt_size;
            front = mean_filtq.front();
            mean_filtq.pop_front();
            mean_filt_total -= front;
            m_filt_series->append(m_sample_num, filt_val);
            m_hr_vect.push_back(filt_val);

        }

    }


    if(val > maxY)
        maxY = val + 20;

    if(val < minY)
        minY = val - 20;

    if(maxX - m_sample_num < 50)
        maxX = maxX + 500;

    if(m_sample_num % 1000 == 0)
    {
        maxY = m_largest_prev + 10;
    }
    else
    {
        if(maxY > m_largest_prev)
            m_largest_prev = maxY;
    }

    m_axisY->setRange(minY, maxY);
    m_axisX->setRange(maxX-1500,maxX);

    m_sample_num++;

}


//-------------------------------------------------------------------------------------------------------------//
// SLOT: updateHeartRate
//
//
//
//-------------------------------------------------------------------------------------------------------------//
void Plotter::updateHeartRate()
{
    std::cout << "update heart rate called" << std::endl;
    std::vector<int> peaks;
    if(!m_hr_vect.empty())
        findPeaks(m_hr_vect, peaks);

    lbl_hr->setText(QString::number(peaks.size()*6));

    m_hr_vect.clear();
}
