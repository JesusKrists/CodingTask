#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QTimer>

#include "Window.hpp"

namespace CodeTask
{

static constexpr auto DEFAULT_WINDOW_WIDTH = 1024;
static constexpr auto DEFAULT_WINDOW_HEIGHT = 768;

Window::Window()
{
    m_window.setWindowTitle("CodeTask");
    m_window.resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    m_window.setCentralWidget(&m_stacked_widget);

    m_stacked_widget.addWidget(&m_progress_bar_widget);
    m_stacked_widget.addWidget(&m_clock_widget);

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(&m_window);
    QPropertyAnimation* anim = new QPropertyAnimation(effect, "opacity");
    anim->setStartValue(0);
    anim->setEndValue(1);
    anim->setEasingCurve(QEasingCurve::InBack);
    m_stacked_widget.setGraphicsEffect(effect);

    QTimer::singleShot(5000, [=]() { anim->start(QPropertyAnimation::DeleteWhenStopped); });

    QObject::connect(anim,
                     &QPropertyAnimation::finished,
                     [&]()
                     {
                         m_stacked_widget.setGraphicsEffect(nullptr);
                         m_stacked_widget.setCurrentIndex(1);
                     });

    m_window.show();
}

}  // namespace CodeTask