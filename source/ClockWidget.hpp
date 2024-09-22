#pragma once

#include <QCoreApplication>
#include <QLabel>
#include <QResizeEvent>
#include <QTimer>

#include <qevent.h>

namespace CodeTask
{

class ClockWidget : public QWidget
{
  public:
    explicit ClockWidget(QWidget* parent = nullptr);

  protected:
    void resizeEvent(QResizeEvent* event) override
    {
        QWidget::resizeEvent(event);
        UpdateLabelFontSizes();
    }

  private:
    void UpdateLabelFontSizes();
    void UpdateLabels();

    QLabel m_time_label;
    QLabel m_weekday_label;
    QLabel m_date_label;

    QTimer m_update_timer;
};

}  // namespace CodeTask