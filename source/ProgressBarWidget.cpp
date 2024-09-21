#include <QFontMetrics>
#include <QPainter>
#include <QPainterPath>

#include "ProgressBarWidget.hpp"

#include <qfloat16.h>
#include <qnamespace.h>
#include <qtextoption.h>

namespace CodeTask
{

static constexpr auto ANIMATION_DURATION = 100;

static constexpr auto FULL_CIRCLE_DEGREES = 360;
static constexpr auto PROGRESS_BAR_START_ANGLE = 90;
static constexpr auto PROGRESS_BAR_WIDTH_COEFICIENT = 0.125;

static constexpr auto ONE_HALF = 0.5;
static constexpr auto ONE_THIRD = 0.333;
static constexpr auto TO_PERCENT = 100;

ProgressBarWidget::ProgressBarWidget(QWidget* parent)
    : QWidget(parent)
    , m_progress_bar_animation(this, "internalValue")
{
    m_progress_bar_animation.setEasingCurve(QEasingCurve::Linear);
    m_progress_bar_animation.setDuration(ANIMATION_DURATION);

    QObject::connect(this,
                     &ProgressBarWidget::ValueChanged,
                     [this](qreal value)
                     {
                         if (m_progress_bar_animation.state() == QAbstractAnimation::Running) {
                             return;
                         }
                         m_progress_bar_animation.setStartValue(m_internal_value);
                         m_progress_bar_animation.setEndValue(value);
                         m_progress_bar_animation.start();
                     });
    QObject::connect(&m_progress_bar_animation,
                     &QPropertyAnimation::finished,
                     [this]()
                     {
                         if (m_internal_value != m_value) {
                             m_progress_bar_animation.setStartValue(m_internal_value);
                             m_progress_bar_animation.setEndValue(m_value);
                             m_progress_bar_animation.start();
                         }

                         if (m_internal_value >= 1.0) {
                             emit LoadingFinished();
                         }
                     });

    QObject::connect(this, &ProgressBarWidget::InternalValueChanged, [this](qreal) { update(); });
}

void ProgressBarWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    // const auto BACKGROUND_COLOR = QColor("#000000");
    const auto PROGRESS_BAR_COLOR = QColor("#0000BF");
    const auto PERCENT_SIGN_COLOR = QColor("#8C8C8C");
    const auto TEXT_COLOR = QColor("#FFFFFF");

    const QString INIT_TEXT = "INITIALIZING";

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    // painter.fillRect(rect(), BACKGROUND_COLOR);

    // Calculate useful metrics
    qreal current_progress_degrees = InternalValue() * FULL_CIRCLE_DEGREES;
    qreal current_value_percent = qRound(InternalValue() * TO_PERCENT);
    QString current_value_text = QString::number(current_value_percent);

    auto smallest_size = SmallestSize();
    auto progress_bar_width = qRound(smallest_size * PROGRESS_BAR_WIDTH_COEFICIENT);
    QRect progress_bar_bounding_box(static_cast<int>((width() - smallest_size) * ONE_HALF),
                                    static_cast<int>((height() - smallest_size) * ONE_HALF),
                                    smallest_size - progress_bar_width,
                                    smallest_size - progress_bar_width);

    auto percent_text_font = painter.font();
    percent_text_font.setPixelSize(qRound(smallest_size * PROGRESS_BAR_WIDTH_COEFICIENT));
    percent_text_font.setBold(true);

    auto percent_sign_font = painter.font();
    percent_sign_font.setPixelSize(qRound(smallest_size * (PROGRESS_BAR_WIDTH_COEFICIENT * ONE_HALF)));

    auto init_text_font = painter.font();
    init_text_font.setPixelSize(qRound(smallest_size * (PROGRESS_BAR_WIDTH_COEFICIENT * ONE_THIRD)));

    auto percent_text_size = QFontMetrics(percent_text_font).size(Qt::TextSingleLine, current_value_text);
    auto percent_sign_size = QFontMetrics(percent_sign_font).size(Qt::TextSingleLine, "%");
    auto first_line_size = QSize(percent_text_size.width() + percent_sign_size.width(), percent_text_size.height());
    auto second_line_size = QFontMetrics(init_text_font).size(Qt::TextSingleLine, INIT_TEXT);

    // Draw progress bar
    auto starting_x = qRound(progress_bar_bounding_box.left() + progress_bar_bounding_box.width() * ONE_HALF);
    auto starting_y = progress_bar_bounding_box.top();

    QPainterPath path;
    path.moveTo(starting_x, starting_y);
    path.arcTo(progress_bar_bounding_box, PROGRESS_BAR_START_ANGLE, -current_progress_degrees);

    QPen pen;
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(PROGRESS_BAR_COLOR);
    pen.setWidth(static_cast<int>(progress_bar_width));
    painter.translate(progress_bar_width * ONE_HALF, progress_bar_width * ONE_HALF);
    painter.strokePath(path, pen);

    // Draw Text

    painter.translate(0, 0);
    auto text_center_x = progress_bar_bounding_box.left() + progress_bar_bounding_box.width() * ONE_HALF;
    auto text_center_y = progress_bar_bounding_box.top() + progress_bar_bounding_box.height() * ONE_HALF;

    auto percent_text_x = static_cast<int>(text_center_x - first_line_size.width() * ONE_HALF);
    auto percent_text_y = static_cast<int>(text_center_y);

    auto init_text_x = static_cast<int>(text_center_x - second_line_size.width() * ONE_HALF);
    auto init_text_y = percent_text_y + second_line_size.height();

    painter.setFont(percent_text_font);
    painter.setPen(TEXT_COLOR);
    painter.drawText(percent_text_x, percent_text_y, current_value_text);

    painter.setFont(percent_sign_font);
    painter.setPen(PERCENT_SIGN_COLOR);
    painter.drawText(percent_text_x + percent_text_size.width(), percent_text_y, "%");

    painter.setFont(init_text_font);
    painter.setPen(TEXT_COLOR);
    painter.drawText(init_text_x, init_text_y, INIT_TEXT);
}

}  // namespace CodeTask