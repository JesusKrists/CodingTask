#include <QPainter>

#include "ProgressBarWidget.hpp"

namespace CodeTask
{
ProgressBarWidget::ProgressBarWidget(QWidget* parent)
    : QProgressBar(parent)
{
}

void ProgressBarWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

}  // namespace CodeTask