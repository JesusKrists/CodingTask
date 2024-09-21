#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QTimer>

#include "ClockWidget.hpp"
#include "FadingStackedWidget.hpp"
#include "ProgressBarWidget.hpp"

namespace CodeTask
{

class Window
{
  public:
    Window();

  private:
    QMainWindow m_window;
    FadingStackedWidget m_stacked_widget;
    ProgressBarWidget m_progress_bar_widget;
    ClockWidget m_clock_widget;

    QTimer m_loading_timer;
};

}  // namespace CodeTask