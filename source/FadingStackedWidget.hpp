#pragma once

#include <QStackedWidget>

#include <qtmetamacros.h>

namespace CodeTask
{

class FadingStackedWidget : public QStackedWidget
{
    Q_OBJECT
  public:
    explicit FadingStackedWidget(QWidget* parent = nullptr);

    void SwitchTo(int index);

    Q_SIGNAL void AnimationFinished();

  private:
    bool m_animating = false;
};

}  // namespace CodeTask