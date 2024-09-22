#include <QDateTime>
#include <QLocale>
#include <QVBoxLayout>

#include "ClockWidget.hpp"

#include <qnamespace.h>

namespace CodeTask
{

static constexpr auto UPDATE_INTERVAL = 1000;

static constexpr auto TIME_FONT_SCALE = 0.175;
static constexpr auto WEEKDAY_FONT_SCALE = TIME_FONT_SCALE * 0.5;

ClockWidget::ClockWidget(QWidget* parent)
    : QWidget(parent)
{
    m_update_timer.setInterval(UPDATE_INTERVAL);
    QObject::connect(&m_update_timer, &QTimer::timeout, this, &ClockWidget::UpdateLabels);

    auto* layout = new QVBoxLayout(this);  // NOLINT
    layout->addStretch();
    layout->addWidget(&m_time_label);
    layout->addWidget(&m_weekday_label);
    layout->addWidget(&m_date_label);
    layout->addStretch();
    layout->setAlignment(Qt::AlignHCenter);

    UpdateLabelFontSizes();
    UpdateLabels();

    m_update_timer.start();
}

void ClockWidget::UpdateLabelFontSizes()
{
    auto size = rect();

    auto time_font = m_time_label.font();
    time_font.setBold(true);
    time_font.setPixelSize(static_cast<int>(size.height() * TIME_FONT_SCALE));
    m_time_label.setFont(time_font);

    auto weekday_font = m_weekday_label.font();
    weekday_font.setBold(true);
    weekday_font.setPixelSize(static_cast<int>(size.height() * WEEKDAY_FONT_SCALE));
    m_weekday_label.setFont(weekday_font);

    auto date_font = m_date_label.font();
    date_font.setPixelSize(static_cast<int>(size.height() * WEEKDAY_FONT_SCALE));
    m_date_label.setFont(date_font);
}

void ClockWidget::UpdateLabels()
{
    QLocale system_locale = QLocale::system();
    QString formatted_time = system_locale.toString(QDateTime::currentDateTime(), "hh:mm");
    QString formatted_weekday = system_locale.toString(QDateTime::currentDateTime(), "dddd");
    QString formatted_date = system_locale.toString(QDateTime::currentDateTime(), "MMM d");

    m_time_label.setText(formatted_time);
    m_weekday_label.setText(formatted_weekday);
    m_date_label.setText(formatted_date);
}

}  // namespace CodeTask