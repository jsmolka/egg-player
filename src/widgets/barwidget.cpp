#include "barwidget.hpp"

#include <QFontMetrics>
#include <QGridLayout>
#include <QPalette>
#include <QPropertyAnimation>

#include "core/player.hpp"
#include "widgets/parts/iconfactory.hpp"

BarWidget::BarWidget(QWidget *parent)
    : QWidget(parent)
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
    , m_durationSlider(this)
    , m_volumeSlider(this)
    , m_scPlayPause(cfg_shortcut.playPause(), false, this)
    , m_scNext(cfg_shortcut.next(), false, this)
    , m_scPrevious(cfg_shortcut.previous(), false, this)
    , m_scVolumeUp(cfg_shortcut.volumeUp(), true, this)
    , m_scVolumeDown(cfg_shortcut.volumeDown(), true, this)
{
    setup();

    connect(egg_player, &Player::audioChanged, this, &BarWidget::onPlayerAudioChanged);
    connect(egg_player, &Player::positionChanged, this, &BarWidget::onPlayerPositionChanged);
    connect(egg_player, &Player::volumeChanged, &m_volumeSlider, &Slider::setValue);

    connect(&m_nextButton, &IconButton::pressed, &egg_player->playlist(), &Playlist::next);
    connect(&m_playPauseButton, &IconButton::pressed, egg_player, &Player::toggleState);
    connect(&m_previousButton, &IconButton::pressed, this, &BarWidget::onPlayerPrevious);
    connect(&m_shuffleButton, &IconButton::locked, &egg_player->playlist(), &Playlist::setShuffle);
    connect(&m_loopButton, &IconButton::locked, &egg_player->playlist(), &Playlist::setLoop);
    connect(&m_volumeButton, &IconButton::pressed, this, &BarWidget::onVolumeButtonPressed);

    connect(&m_durationSlider, &Slider::sliderMoved, this, &BarWidget::onDurationSliderMoved);
    connect(&m_durationSlider, &Slider::sliderValueChanged, egg_player, &Player::setPosition);
    connect(&m_volumeSlider, &Slider::sliderMoved, egg_player, &Player::setVolume);

    connect(&m_scPlayPause, &Shortcut::pressed, egg_player, &Player::toggleState);
    connect(&m_scNext, &Shortcut::pressed, &egg_player->playlist(), &Playlist::next);
    connect(&m_scPrevious, &Shortcut::pressed, this, &BarWidget::onPlayerPrevious);
    connect(&m_scVolumeUp, &Shortcut::pressed, egg_player, &Player::increaseVolume);
    connect(&m_scVolumeDown, &Shortcut::pressed, egg_player, &Player::decreaseVolume);
}

void BarWidget::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}

QColor BarWidget::color() const
{
    return palette().color(QPalette::Background);
}

void BarWidget::onPlayerAudioChanged(Audio *audio)
{
    m_durationSlider.setEnabled(true);
    m_durationSlider.setRange(0, audio->duration().secs());

    m_trackLabel.setText(trackLabelText(audio));
    m_coverLabel.setPixmap(audio->cover().pixmap(cfg_bar.coverSize()));

    m_currentTimeLabel.setText(Duration(0).toString());
    m_totalTimeLabel.setText(audio->duration().toString());

    startTransition(audio->cover().color());
}

void BarWidget::onPlayerPositionChanged(int position)
{
    if (egg_player->playlist().isEmpty()
            || m_durationSlider.isPressed()
            || m_durationSlider.maximum() < position)
        return;

    m_durationSlider.setValue(position);
    m_currentTimeLabel.setText(Duration(position).toString());
}

void BarWidget::onPlayerPrevious()
{
    if (cfg_player.previousLimit() < m_durationSlider.value())
        egg_player->setPosition(0);
    else
        egg_player->playlist().previous();
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

void BarWidget::onDurationSliderMoved(int value)
{
    m_currentTimeLabel.setText(Duration(value).toString());
}

QString BarWidget::trackLabelText(Audio *audio) const
{
    const QFontMetrics metrics(font());
    return QString("%1\n%2").arg(
        metrics.elidedText(audio->tag().title(), Qt::ElideRight, m_trackLabel.width()),
        metrics.elidedText(audio->tag().artist(), Qt::ElideRight, m_trackLabel.width())
    );
}

void BarWidget::startTransition(const QColor &color)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "color", this);
    animation->setStartValue(this->color());
    animation->setEndValue(color);
    animation->setDuration(250);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
}

void BarWidget::setup()
{
    setAutoFillBackground(true);
    setColor(Cover::defaultCover().color());
    setFixedHeight(cfg_bar.height());

    setupCss();
    setupUi();
}

void BarWidget::setupCss()
{
    setStyleSheet(FileUtil::read(CSS_BAR)
        .replace("groove-height", QString::number(cfg_bar.grooveHeight()))
        .replace("handle-size-half", QString::number(cfg_bar.handleSize() / 2))
        .replace("handle-size", QString::number(cfg_bar.handleSize()))
        .replace("icon-size-half", QString::number(cfg_bar.iconSize() / 2))
    );
}

void BarWidget::setupUi()
{
    m_coverLabel.setPixmap(Cover::defaultCover().pixmap(cfg_bar.coverSize()));
    m_coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_trackLabel.setFixedWidth(cfg_bar.trackWidth());
    m_trackLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_currentTimeLabel.setFixedWidth(cfg_bar.timeWidth());
    m_currentTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_currentTimeLabel.setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    m_totalTimeLabel.setFixedWidth(cfg_bar.timeWidth());
    m_totalTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

    m_durationSlider.setEnabled(false);
    m_durationSlider.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setVisible(false);
    m_volumeSlider.setRange(0, 100);
    m_volumeSlider.setValue(cfg_player.volume());
    m_volumeSlider.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setFixedWidth(5 * cfg_bar.iconSize() + 4 * cfg_bar.spacing());

    m_previousButton.setIcons({IconFactory::make(ICO_PREVIOUS)});
    m_nextButton.setIcons({IconFactory::make(ICO_NEXT)});
    m_shuffleButton.setIcons({IconFactory::make(ICO_SHUFFLE)});
    m_loopButton.setIcons({IconFactory::make(ICO_LOOP)});

    m_shuffleButton.setLockable(true);
    m_loopButton.setLockable(true);

    const QSize iconSize = QSize(cfg_bar.iconSize(), cfg_bar.iconSize());
    m_playPauseButton.setSize(iconSize);
    m_previousButton.setSize(iconSize);
    m_nextButton.setSize(iconSize);
    m_shuffleButton.setSize(iconSize);
    m_loopButton.setSize(iconSize);
    m_volumeButton.setSize(iconSize);

    m_shuffleButton.setLocked(cfg_player.shuffle());
    m_loopButton.setLocked(cfg_player.loop());

    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(cfg_bar.spacing());
    layout->setContentsMargins(cfg_bar.margin(), cfg_bar.margin(), cfg_bar.margin(), cfg_bar.margin());
    layout->addWidget(&m_coverLabel, 0, 0);
    layout->addWidget(&m_trackLabel, 0, 1);
    layout->addWidget(&m_currentTimeLabel, 0, 2);
    layout->addWidget(&m_durationSlider, 0, 3);
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
