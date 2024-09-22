#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QTimer>

#include "FadingStackedWidget.hpp"

#include <qabstractanimation.h>
#include <qeasingcurve.h>
#include <qparallelanimationgroup.h>

namespace CodeTask
{

static constexpr auto FADE_DURATION = 1000;
static constexpr auto ONE_FOURTH = 0.25;

FadingStackedWidget::FadingStackedWidget(QWidget* parent)
    : QStackedWidget(parent)
{
}

void FadingStackedWidget::SwitchTo(int index)
{
    if (m_animating) {
        return;
    }

    m_new_index = index;

    auto* current_widget = widget(currentIndex());
    auto* next_widget = widget(index);

    next_widget->setGeometry(contentsRect());

    auto* fade_out_effect = new QGraphicsOpacityEffect();  // NOLINT
    current_widget->setGraphicsEffect(fade_out_effect);
    auto* fade_out_property_animation = new QPropertyAnimation(fade_out_effect, "opacity");
    fade_out_property_animation->setDuration(FADE_DURATION);
    fade_out_property_animation->setEasingCurve(QEasingCurve::OutCubic);
    fade_out_property_animation->setStartValue(1);
    fade_out_property_animation->setEndValue(0);
    QObject::connect(fade_out_property_animation,
                     &QPropertyAnimation::finished,
                     [=]()
                     {
                         current_widget->hide();

                         if (fade_out_effect != nullptr) {
                             fade_out_effect->deleteLater();
                         }
                     });

    QTimer::singleShot(FADE_DURATION * ONE_FOURTH,
                       [this, next_widget, index]()
                       {
                           next_widget->show();
                           next_widget->raise();

                           auto* fade_in_effect = new QGraphicsOpacityEffect();  // NOLINT
                           next_widget->setGraphicsEffect(fade_in_effect);
                           auto* fade_in_property_animation = new QPropertyAnimation(fade_in_effect, "opacity");
                           fade_in_property_animation->setDuration(FADE_DURATION);
                           fade_in_property_animation->setEasingCurve(QEasingCurve::InCubic);
                           fade_in_property_animation->setStartValue(0);
                           fade_in_property_animation->setEndValue(1);
                           QObject::connect(fade_in_property_animation,
                                            &QPropertyAnimation::finished,
                                            [this, fade_in_effect, index]()
                                            {
                                                if (fade_in_effect != nullptr) {
                                                    fade_in_effect->deleteLater();
                                                }

                                                setCurrentIndex(index);
                                                m_animating = false;
                                                emit AnimationFinished();
                                            });

                           fade_in_property_animation->start(QAbstractAnimation::DeleteWhenStopped);
                       });

    fade_out_property_animation->start(QAbstractAnimation::DeleteWhenStopped);
    m_animating = true;
}

void FadingStackedWidget::resizeEvent(QResizeEvent* event)
{
    QStackedWidget::resizeEvent(event);

    if (m_animating) {
        widget(m_new_index)->setGeometry(contentsRect());
    }
}

}  // namespace CodeTask