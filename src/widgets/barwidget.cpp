#include "barwidget.hpp"

#include <QFontMetrics>
#include <QGridLayout>
#include <QPalette>
#include <QPropertyAnimation>

#include "core/config.hpp"
#include "core/constants.hpp"
#include "core/player.hpp"
#include "core/shortcutprocessor.hpp"
#include "core/utils.hpp"
#include "widgets/iconfactory.hpp"

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
{
    init();

    connect(&egg_player, &Player::audioChanged, this, &BarWidget::onPlayerAudioChanged);
    connect(&egg_player, &Player::positionChanged, this, &BarWidget::onPlayerPositionChanged);
    connect(&egg_player, &Player::volumeChanged, &m_volumeSlider, &Slider::setValue);

    connect(&m_playPauseButton, &IconButton::released, &ShortcutProcessor::playPauseAction);
    connect(&m_nextButton, &IconButton::released, &ShortcutProcessor::nextAction);
    connect(&m_previousButton, &IconButton::released, &ShortcutProcessor::previousAction);
    connect(&m_shuffleButton, &LockableIconButton::locked, &egg_player.playlist(), &Playlist::setShuffle);
    connect(&m_loopButton, &LockableIconButton::locked, &egg_player.playlist(), &Playlist::setLoop);
    connect(&m_volumeButton, &IconButton::released, this, &BarWidget::onVolumeButtonPressed);

    connect(&m_durationSlider, &Slider::sliderMoved, this, &BarWidget::onDurationSliderMoved);
    connect(&m_durationSlider, &Slider::sliderValueChanged, &egg_player, &Player::setPosition);
    connect(&m_volumeSlider, &Slider::sliderMoved, &egg_player, &Player::setVolume);
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
    if (m_durationSlider.isPressed()
            || m_durationSlider.maximum() < position)
        return;

    m_durationSlider.setValue(position);
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

void BarWidget::init()
{
    setAutoFillBackground(true);
    setColor(Cover::defaultCover().color());
    setFixedHeight(cfg_bar.height());

    initUi();
    initStyle();
}

void BarWidget::initUi()
{
    m_coverLabel.setPixmap(Cover::defaultCover().pixmap(cfg_bar.coverSize()));
    m_coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_trackLabel.setFixedWidth(cfg_bar.labelWidth().track());
    m_trackLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    m_currentTimeLabel.setFixedWidth(cfg_bar.labelWidth().time());
    m_currentTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_currentTimeLabel.setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_totalTimeLabel.setFixedWidth(cfg_bar.labelWidth().time());
    m_totalTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_totalTimeLabel.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_durationSlider.setEnabled(false);
    m_durationSlider.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setVisible(false);
    m_volumeSlider.setRange(0, 100);
    m_volumeSlider.setValue(cfg_player.volume());
    m_volumeSlider.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setFixedWidth(5 * cfg_bar.iconSize() + 4 * cfg_bar.spacing());

    m_previousButton.setIcons(IconFactory::make(constants::ico::previous));
    m_nextButton.setIcons(IconFactory::make(constants::ico::next));
    m_shuffleButton.setIcons(IconFactory::make(constants::ico::shuffle));
    m_loopButton.setIcons(IconFactory::make(constants::ico::loop));

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

void BarWidget::initStyle()
{
    setStyleSheet(FileUtil::read(constants::css::bar)
        .replace("groove-height", QString::number(cfg_bar.slider().grooveHeight()))
        .replace("handle-size-half", QString::number(cfg_bar.slider().handleSize() / 2))
        .replace("handle-size", QString::number(cfg_bar.slider().handleSize()))
        .replace("icon-size-half", QString::number(cfg_bar.iconSize() / 2))
    );
}
