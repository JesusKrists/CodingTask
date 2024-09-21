#pragma once

#include <QLabel>

namespace CodeTask
{

class ClockWidget : public QLabel
{
  public:
    explicit ClockWidget(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
};

}  // namespace CodeTask