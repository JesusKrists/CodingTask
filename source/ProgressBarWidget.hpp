#pragma once

#include <QProgressBar>

namespace CodeTask
{

class ProgressBarWidget : public QProgressBar
{
  public:
    explicit ProgressBarWidget(QWidget* parent = nullptr);

  protected:
    void paintEvent(QPaintEvent* event) override;
};

}  // namespace CodeTask