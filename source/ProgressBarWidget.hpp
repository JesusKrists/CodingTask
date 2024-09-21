#pragma once

#include <QProgressBar>
#include <QPropertyAnimation>

#include <qpropertyanimation.h>
#include <qtmetamacros.h>

namespace CodeTask
{

class ProgressBarWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal internalValue READ InternalValue WRITE SetInternalValue NOTIFY InternalValueChanged)
  public:
    explicit ProgressBarWidget(QWidget* parent = nullptr);

    void SetValue(qreal value)
    {
        m_value = value;
        emit ValueChanged(m_value);
    }
    qreal Value() const { return m_value; }

    Q_SIGNAL void LoadingFinished();
    Q_SIGNAL void ValueChanged(qreal value);

  protected:
    void paintEvent(QPaintEvent* event) override;

  private:
    int SmallestSize() const { return qMin(width(), height()); }

    Q_SIGNAL void InternalValueChanged(qreal);
    qreal InternalValue() const { return m_internal_value; }
    void SetInternalValue(qreal value)
    {
        m_internal_value = value;
        emit InternalValueChanged(m_internal_value);
    }
    qreal m_internal_value = 0.0;

    qreal m_value = 0.0;
    QPropertyAnimation m_progress_bar_animation;
};

}  // namespace CodeTask