#pragma once

#include <QStackedWidget>

namespace CodeTask
{

class FadingStackedWidget : public QStackedWidget
{
  public:
    explicit FadingStackedWidget(QWidget* parent = nullptr);

  protected:
    // void paintEvent(QPaintEvent* event) override;
};

}  // namespace CodeTask