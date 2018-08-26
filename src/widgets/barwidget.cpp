#include "barwidget.hpp"

#include <QGridLayout>
#include <QPainter>
#include <QStyleOption>

#include "cache.hpp"
#include "config.hpp"
#include "constants.hpp"
#include "duration.hpp"
#include "fileutil.hpp"
#include "iconfactory.hpp"
#include "player.hpp"

BarWidget::BarWidget(QWidget *parent)
    : ColorTransitionWidget(parent)
    , m_coverLabel(this)
    , m_trackLabel(this)
    , m_currentTimeLabel(this)
    , m_totalTimeLabel(this)
    , m_playPauseButton(this)
    , m_nextButton(this)
    , m_previousButton(this)
    , m_shuffleButton(this)
    , m_loopButton(this)
    , m_volumeButton(this)
    , m_lengthSlider(this)
    , m_volumeSlider(this)
    , m_scPlayPause(cfgShortcut.playPause(), false, this)
    , m_scNext(cfgShortcut.next(), false, this)
    , m_scPrevious(cfgShortcut.previous(), false, this)
    , m_scVolumeUp(cfgShortcut.volumeUp(), true, this)
    , m_scVolumeDown(cfgShortcut.volumeDown(), true, this)
{
    setup();
    setupUi();

    connect(ePlayer, &Player::audioChanged, this, &BarWidget::onPlayerAudioChanged);
    connect(ePlayer, &Player::positionChanged, this, &BarWidget::onPlayerPositionChanged);
    connect(ePlayer, &Player::volumeChanged, &m_volumeSlider, &Slider::setValue);

    connect(&m_nextButton, &IconButton::pressed, &ePlayer->playlist(), &Playlist::next);
    connect(&m_playPauseButton, &IconButton::pressed, ePlayer, &Player::toggleState);
    connect(&m_previousButton, &IconButton::pressed, &ePlayer->playlist(), &Playlist::previous);
    connect(&m_shuffleButton, &IconButton::locked, &ePlayer->playlist(), &Playlist::setShuffle);
    connect(&m_loopButton, &IconButton::locked, &ePlayer->playlist(), &Playlist::setLoop);
    connect(&m_volumeButton, &IconButton::pressed, this, &BarWidget::onVolumeButtonPressed);

    connect(&m_lengthSlider, &Slider::sliderMoved, this, &BarWidget::onLengthSliderMoved);
    connect(&m_lengthSlider, &Slider::sliderValueChanged, ePlayer, &Player::setPosition);
    connect(&m_volumeSlider, &Slider::sliderMoved, ePlayer, &Player::setVolume);

    connect(&m_scPlayPause, &Shortcut::pressed, ePlayer, &Player::toggleState);
    connect(&m_scNext, &Shortcut::pressed, &ePlayer->playlist(), &Playlist::next);
    connect(&m_scPrevious, &Shortcut::pressed, &ePlayer->playlist(), &Playlist::previous);
    connect(&m_scVolumeUp, &Shortcut::pressed, ePlayer, &Player::increaseVolume);
    connect(&m_scVolumeDown, &Shortcut::pressed, ePlayer, &Player::decreaseVolume);
}

QLabel &BarWidget::coverLabel()
{
    return m_coverLabel;
}

QLabel &BarWidget::trackLabel()
{
    return m_trackLabel;
}

QLabel &BarWidget::currentTimeLabel()
{
    return m_currentTimeLabel;
}

QLabel &BarWidget::totalTimeLabel()
{
    return m_totalTimeLabel;
}

IconButton &BarWidget::playPauseButton()
{
    return m_playPauseButton;
}

IconButton &BarWidget::nextButton()
{
    return m_nextButton;
}

IconButton &BarWidget::previousButton()
{
    return m_previousButton;
}

IconButton &BarWidget::shuffleButton()
{
    return m_shuffleButton;
}

IconButton &BarWidget::loopButton()
{
    return m_loopButton;
}

IconButton &BarWidget::volumeButton()
{
    return m_volumeButton;
}

Slider &BarWidget::lengthSlider()
{
    return m_lengthSlider;
}

Slider &BarWidget::volumeSlider()
{
    return m_volumeSlider;
}

void BarWidget::onPlayerAudioChanged(Audio *audio)
{
    m_lengthSlider.setEnabled(true);
    m_lengthSlider.setRange(0, audio->duration().secs());

    m_coverLabel.setPixmap(audio->cover().picture(cfgBar.coverSize()));
    m_trackLabel.setText(QString("%1\n%2").arg(audio->title(), audio->artist()));

    m_currentTimeLabel.setText(Duration(0).toString());
    m_totalTimeLabel.setText(audio->duration().toString());

    colorTransition(audio->cover().dominantColor());
}

void BarWidget::onPlayerPositionChanged(int position)
{
    if (m_lengthSlider.isPressed() || m_lengthSlider.maximum() < position)
        return;

    m_lengthSlider.setValue(position);
    m_currentTimeLabel.setText(Duration(position).toString());
}

void BarWidget::onVolumeButtonPressed()
{
    const bool visible = m_volumeSlider.isVisible();

    m_volumeSlider.setVisible(!visible);
    m_previousButton.setVisible(visible);
    m_playPauseButton.setVisible(visible);
    m_nextButton.setVisible(visible);
    m_shuffleButton.setVisible(visible);
    m_loopButton.setVisible(visible);
}

void BarWidget::onLengthSliderMoved(int value)
{
    m_currentTimeLabel.setText(Duration(value).toString());
}

void BarWidget::setup()
{
    setColor(Cover::defaultCover().dominantColor());
    setFixedHeight(cfgBar.height());

    setupCss();
}

void BarWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_BAR)
        .replace("groove-height", QString::number(cfgBar.grooveHeight()))
        .replace("handle-size-half", QString::number(cfgBar.handleSize() / 2))
        .replace("handle-size", QString::number(cfgBar.handleSize()))
        .replace("icon-size-half", QString::number(cfgBar.iconSize() / 2))
    );
}

void BarWidget::setupUi()
{
    m_coverLabel.setPixmap(Cover::defaultCover().picture(cfgBar.coverSize()));
    m_coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_trackLabel.setFixedWidth(cfgBar.trackWidth());
    m_trackLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_currentTimeLabel.setFixedWidth(cfgBar.timeWidth());
    m_currentTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_currentTimeLabel.setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    m_totalTimeLabel.setFixedWidth(cfgBar.timeWidth());
    m_totalTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

    m_lengthSlider.setEnabled(false);
    m_lengthSlider.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setVisible(false);
    m_volumeSlider.setRange(0, 100);
    m_volumeSlider.setValue(cfgPlayer.volume());
    m_volumeSlider.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setFixedWidth(5 * cfgBar.iconSize() + 4 * cfgBar.spacing());

    m_previousButton.setIcons({IconFactory::make(ICO_PREVIOUS)});
    m_nextButton.setIcons({IconFactory::make(ICO_NEXT)});
    m_shuffleButton.setIcons({IconFactory::make(ICO_SHUFFLE)});
    m_loopButton.setIcons({IconFactory::make(ICO_LOOP)});

    m_shuffleButton.setLockable(true);
    m_loopButton.setLockable(true);

    const QSize buttonSize = QSize(cfgBar.iconSize(), cfgBar.iconSize());
    m_playPauseButton.setSize(buttonSize);
    m_previousButton.setSize(buttonSize);
    m_nextButton.setSize(buttonSize);
    m_shuffleButton.setSize(buttonSize);
    m_loopButton.setSize(buttonSize);
    m_volumeButton.setSize(buttonSize);

    m_shuffleButton.setLocked(cfgPlayer.shuffle());
    m_loopButton.setLocked(cfgPlayer.loop());

    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(cfgBar.spacing());
    layout->setContentsMargins(cfgBar.margin(), cfgBar.margin(), cfgBar.margin(), cfgBar.margin());
    layout->addWidget(&m_coverLabel, 0, 0);
    layout->addWidget(&m_trackLabel, 0, 1);
    layout->addWidget(&m_currentTimeLabel, 0, 2);
    layout->addWidget(&m_lengthSlider, 0, 3);
    layout->addWidget(&m_totalTimeLabel, 0, 4);
    layout->addWidget(&m_previousButton, 0, 5);
    layout->addWidget(&m_volumeSlider, 0, 5, 1, 5, Qt::AlignRight);
    layout->addWidget(&m_playPauseButton, 0, 6);
    layout->addWidget(&m_nextButton, 0, 7);
    layout->addWidget(&m_shuffleButton, 0, 8);
    layout->addWidget(&m_loopButton, 0, 9);
    layout->addWidget(&m_volumeButton, 0, 10);
    setLayout(layout);
}
