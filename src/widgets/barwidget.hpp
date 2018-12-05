#ifndef BARWIDGET_HPP
#define BARWIDGET_HPP

#include <QLabel>
#include <QWidget>

#include "core/audio.hpp"
#include "widgets/iconbutton.hpp"
#include "widgets/lockableiconbutton.hpp"
#include "widgets/playpausebutton.hpp"
#include "widgets/slider.hpp"
#include "widgets/volumebutton.hpp"

class BarWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit BarWidget(QWidget *parent = nullptr);

    void setColor(const QColor &color);
    QColor color() const;

private slots:
    void onPlayerAudioChanged(const Audio &audio);
    void onPlayerPositionChanged(int position);
    void onVolumeButtonPressed();
    void onDurationSliderMoved(int value);

private:
    QString trackLabelText(const Audio &audio) const;

    void colorTransition(const QColor &color);

    void init();
    void initUi();
    void initStyle();

    QLabel m_coverLabel;
    QLabel m_trackLabel;
    QLabel m_currentTimeLabel;
    QLabel m_totalTimeLabel;

    PlayPauseButton m_playPauseButton;
    IconButton m_nextButton;
    IconButton m_previousButton;
    LockableIconButton m_shuffleButton;
    LockableIconButton m_loopButton;
    VolumeButton m_volumeButton;

    Slider m_durationSlider;
    Slider m_volumeSlider;
};

#endif // BARWIDGET_HPP
