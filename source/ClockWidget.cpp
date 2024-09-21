#include <QPainter>

#include "ClockWidget.hpp"

#include <qnamespace.h>

namespace CodeTask
{
ClockWidget::ClockWidget(QWidget* parent)
    : QLabel(parent)
{
}

void ClockWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Rocks!");
}

}  // namespace CodeTask