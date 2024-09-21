#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "FadingStackedWidget.hpp"

#include <qeasingcurve.h>
#include <qparallelanimationgroup.h>

namespace CodeTask
{

static constexpr auto FADE_DURATION = 1000;

FadingStackedWidget::FadingStackedWidget(QWidget* parent)
    : QStackedWidget(parent)
{
}

void FadingStackedWidget::SwitchTo(int index)
{
    if (m_animating) {
        return;
    }

    auto* current_widget = widget(currentIndex());
    auto* next_widget = widget(index);

    auto rect_bb = rect();
    next_widget->setGeometry(0, 0, rect_bb.width(), rect_bb.height());
    // next_widget->move(pnext.x() - offsetx, pnext.y() - offsety);

    next_widget->show();
    next_widget->raise();

    auto* fade_out_effect = new QGraphicsOpacityEffect();  // NOLINT
    current_widget->setGraphicsEffect(fade_out_effect);
    auto* fade_out_property_animation = new QPropertyAnimation(fade_out_effect, "opacity");
    fade_out_property_animation->setDuration(FADE_DURATION);
    fade_out_property_animation->setEasingCurve(QEasingCurve::OutCubic);
    fade_out_property_animation->setStartValue(1);
    fade_out_property_animation->setEndValue(0);
    connect(fade_out_property_animation,
            &QPropertyAnimation::finished,
            [=]()
            {
                if (fade_out_effect != nullptr) {
                    fade_out_effect->deleteLater();
                }
            });

    auto* fade_in_effect = new QGraphicsOpacityEffect();  // NOLINT
    next_widget->setGraphicsEffect(fade_in_effect);
    auto* fade_in_property_animation = new QPropertyAnimation(fade_in_effect, "opacity");
    fade_in_property_animation->setDuration(FADE_DURATION);
    fade_in_property_animation->setEasingCurve(QEasingCurve::InCubic);
    fade_in_property_animation->setStartValue(0);
    fade_in_property_animation->setEndValue(1);
    connect(fade_in_property_animation,
            &QPropertyAnimation::finished,
            [=]()
            {
                if (fade_in_effect != nullptr) {
                    fade_in_effect->deleteLater();
                }
            });

    auto animation_group = new QParallelAnimationGroup();
    animation_group->addAnimation(fade_out_property_animation);
    animation_group->addAnimation(fade_in_property_animation);
    QObject::connect(animation_group,
                     &QParallelAnimationGroup::finished,
                     [this, current_widget, index]()
                     {
                         setCurrentIndex(index);
                         current_widget->hide();
                         m_animating = false;
                         emit AnimationFinished();
                     });

    animation_group->start(QAbstractAnimation::DeleteWhenStopped);
    m_animating = true;
}

}  // namespace CodeTask