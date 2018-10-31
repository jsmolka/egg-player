#ifndef BARWIDGET_HPP
#define BARWIDGET_HPP

#include <QLabel>
#include <QWidget>

#include "core/audio.hpp"
#include "core/shortcut.hpp"
#include "widgets/parts/iconbutton.hpp"
#include "widgets/parts/lockableiconbutton.hpp"
#include "widgets/parts/playpausebutton.hpp"
#include "widgets/parts/slider.hpp"
#include "widgets/parts/volumebutton.hpp"

class BarWidget : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor)

public:
    explicit BarWidget(QWidget *parent = nullptr);

    void setColor(const QColor &color);
    QColor color() const;

private slots:
    void onPlayerAudioChanged(Audio *audio);
    void onPlayerPositionChanged(int position);
    void onPlayerPrevious();
    void onVolumeButtonPressed();
    void onDurationSliderMoved(int value);

private:
    QString trackLabelText(Audio *audio) const;

    void startTransition(const QColor &color);

    void setup();
    void setupCss();
    void setupUi();

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

    Shortcut m_scPlayPause;
    Shortcut m_scNext;
    Shortcut m_scPrevious;
    Shortcut m_scVolumeUp;
    Shortcut m_scVolumeDown;
};

#endif // BARWIDGET_HPP
