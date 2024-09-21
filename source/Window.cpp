#include <QGraphicsOpacityEffect>
#include <QLayout>
#include <QPropertyAnimation>

#include "Window.hpp"

#include "ProgressBarWidget.hpp"

namespace CodeTask
{

static constexpr auto DEFAULT_WINDOW_WIDTH = 1024;
static constexpr auto DEFAULT_WINDOW_HEIGHT = 768;

static constexpr auto DEFAULT_PADDING = 32;

static constexpr qreal LOADING_TIMER_LENGTH = 1000;
static constexpr qreal LOADING_TIMER_INTERVAL = 100;

Window::Window()
{
    m_window.setWindowTitle("CodeTask");
    m_window.resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    m_window.setCentralWidget(&m_stacked_widget);

    m_stacked_widget.setContentsMargins(DEFAULT_PADDING, DEFAULT_PADDING, DEFAULT_PADDING, DEFAULT_PADDING);
    m_stacked_widget.addWidget(&m_progress_bar_widget);
    m_stacked_widget.addWidget(&m_clock_widget);

    QObject::connect(&m_loading_timer,
                     &QTimer::timeout,
                     [this]()
                     {
                         static auto timeout_count = 0;

                         auto progress_value = (++timeout_count * LOADING_TIMER_INTERVAL) / LOADING_TIMER_LENGTH;
                         if (progress_value >= 1.0) {
                             m_loading_timer.stop();
                             QObject::connect(&m_progress_bar_widget,
                                              &ProgressBarWidget::LoadingFinished,
                                              [this]() { m_stacked_widget.SwitchTo(1); });
                         }

                         m_progress_bar_widget.SetValue(progress_value);
                     });

    m_loading_timer.start(static_cast<int>(LOADING_TIMER_INTERVAL));

    m_window.show();
}

}  // namespace CodeTask