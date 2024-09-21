#pragma once

#include <QMainWindow>
#include <QStackedWidget>

#include "ClockWidget.hpp"
#include "ProgressBarWidget.hpp"

namespace CodeTask
{

class Window
{
  public:
    Window();

  private:
    QMainWindow m_window;
    QStackedWidget m_stacked_widget;
    ProgressBarWidget m_progress_bar_widget;
    ClockWidget m_clock_widget;
};

}  // namespace CodeTask