#include "musicbar.hpp"

MusicBar::MusicBar(QWidget *parent)
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
    , m_lengthSlider(this)
    , m_volumeSlider(this)
    , m_scPlayPause(cfgShortcut->playPause(), false, this)
    , m_scNext(cfgShortcut->next(), false, this)
    , m_scPrevious(cfgShortcut->previous(), false, this)
    , m_scVolumeUp(cfgShortcut->volumeUp(), true, this)
    , m_scVolumeDown(cfgShortcut->volumeDown(), true, this)
{
    setup();
    setupUi();

    connect(eggPlayer, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(eggPlayer, SIGNAL(stateChanged(Player::State)), this, SLOT(onPlayerStateChanged(Player::State)));
    connect(eggPlayer, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
    connect(eggPlayer, SIGNAL(volumeChanged(int)), this, SLOT(onPlayerVolumeChanged(int)));

    connect(&m_nextButton, SIGNAL(pressed()), eggPlayer, SLOT(next()));
    connect(&m_playPauseButton, SIGNAL(pressed()), this, SLOT(onPlayPauseButtonPressed()));
    connect(&m_previousButton, SIGNAL(pressed()), eggPlayer, SLOT(previous()));
    connect(&m_shuffleButton, SIGNAL(locked(bool)), this, SLOT(onShuffleButtonLocked(bool)));
    connect(&m_loopButton, SIGNAL(locked(bool)), this, SLOT(onLoopButtonLocked(bool)));
    connect(&m_volumeButton, SIGNAL(pressed()), this, SLOT(onVolumeButtonPressed()));

    connect(&m_lengthSlider, SIGNAL(sliderMoved(int)), this, SLOT(onLengthSliderMoved(int)));
    connect(&m_lengthSlider, SIGNAL(sliderValueChanged(int)), this, SLOT(onLengthSliderValueChanged(int)));
    connect(&m_volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(onVolumeSliderMoved(int)));

    connect(&m_scPlayPause, SIGNAL(pressed()), this, SLOT(onShortcutPlayPausePressed()));
    connect(&m_scNext, SIGNAL(pressed()), eggPlayer, SLOT(next()));
    connect(&m_scPrevious, SIGNAL(pressed()), eggPlayer, SLOT(previous()));
    connect(&m_scVolumeUp, SIGNAL(pressed()), this, SLOT(onShortcutVolumeUpPressed()));
    connect(&m_scVolumeDown, SIGNAL(pressed()), this, SLOT(onShortcutVolumeDownPressed()));
}

MusicBar::~MusicBar()
{

}

QLabel * MusicBar::coverLabel()
{
    return &m_coverLabel;
}

QLabel * MusicBar::trackLabel()
{
    return &m_trackLabel;
}

QLabel * MusicBar::currentTimeLabel()
{
    return &m_currentTimeLabel;
}

QLabel * MusicBar::totalTimeLabel()
{
    return &m_totalTimeLabel;
}

IconButton * MusicBar::playPauseButton()
{
    return &m_playPauseButton;
}

IconButton * MusicBar::nextButton()
{
    return &m_nextButton;
}

IconButton * MusicBar::previousButton()
{
    return &m_previousButton;
}

IconButton * MusicBar::shuffleButton()
{
    return &m_shuffleButton;
}

IconButton * MusicBar::loopButton()
{
    return &m_loopButton;
}

IconButton * MusicBar::volumeButton()
{
    return &m_volumeButton;
}

ClickableSlider * MusicBar::lengthSlider()
{
    return &m_lengthSlider;
}

ClickableSlider * MusicBar::volumeSlider()
{
    return &m_volumeSlider;
}

void MusicBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void MusicBar::onPlayerAudioChanged(Audio *audio)
{
    QPixmap cover = Cache().cover(audio, cfgBar->coverSize());

    m_coverLabel.setPixmap(cover);
    m_trackLabel.setText(QString("%1\n%2").arg(audio->title(), audio->artist()));

    m_currentTimeLabel.setText(Util::time(0));
    m_totalTimeLabel.setText(Util::time(audio->duration()));

    m_lengthSlider.setRange(0, audio->duration());
    m_lengthSlider.setEnabled(true);

    setColor(ColorUtil::background(cover, audio->coverId()));
}

void MusicBar::onPlayerStateChanged(Player::State state)
{
    m_playPauseButton.setSelectedIcon(state == Player::State::Playing ? 1 : 0);
}

void MusicBar::onPlayerPositionChanged(int position)
{
    if (!m_lengthSlider.isPressed())
    {
        m_currentTimeLabel.setText(Util::time(position));
        m_lengthSlider.setValue(position);
    }
}

void MusicBar::onPlayerVolumeChanged(int volume)
{
    setVolumeConfig(volume);
    setVolumeIcon(volume);
    setVolumeSlider(volume);
}

void MusicBar::onPlayPauseButtonPressed()
{
    if (m_playPauseButton.selectedIcon() == 0)
        eggPlayer->play();
    else
        eggPlayer->pause();
}

void MusicBar::onShuffleButtonLocked(bool locked)
{
    eggPlayer->setShuffle(locked);
    cfgPlayer->setShuffle(locked);
}

void MusicBar::onLoopButtonLocked(bool locked)
{
    eggPlayer->setLoop(locked);
    cfgPlayer->setLoop(locked);
}

void MusicBar::onVolumeButtonPressed()
{
    if (m_volumeSlider.isVisible())
    {
        m_volumeSlider.setVisible(false);
        showButtons();
    }
    else
    {
        hideButtons();
        m_volumeSlider.setVisible(true);
    }
}

void MusicBar::onLengthSliderMoved(int value)
{
    m_currentTimeLabel.setText(Util::time(value));
}

void MusicBar::onLengthSliderValueChanged(int value)
{
    if (value != eggPlayer->currentAudio()->duration())
        eggPlayer->setPosition(value);
    else
        eggPlayer->next();
}

void MusicBar::onVolumeSliderMoved(int value)
{
    setVolumePlayer(value);
}

void MusicBar::onShortcutPlayPausePressed()
{
    if (eggPlayer->isPlaying())
        eggPlayer->pause();
    else
        eggPlayer->play();
}

void MusicBar::onShortcutVolumeUpPressed()
{
    setVolumePlayer(eggPlayer->volume() + 1);
}

void MusicBar::onShortcutVolumeDownPressed()
{
    setVolumePlayer(eggPlayer->volume() - 1);
}

void MusicBar::loadCss()
{
    setStyleSheet(
        FileUtil::read(CSS_MUSICBAR)
            .replace("groove-height", QString::number(cfgBar->grooveHeight()))
            .replace("handle-size-half", QString::number(cfgBar->handleSize() / 2))
            .replace("handle-size", QString::number(cfgBar->handleSize()))
            .replace("icon-size-half", QString::number(cfgBar->iconSize() / 2))
    );
}

void MusicBar::setup()
{
    loadCss();

    setAutoFillBackground(true);
    setFixedHeight(cfgBar->height());
    setColor(ColorUtil::background(Util::defaultCover()));
}

void MusicBar::setupUi()
{
    m_coverLabel.setPixmap(Util::defaultCover(cfgBar->coverSize()));
    m_coverLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_trackLabel.setFixedWidth(cfgBar->trackWidth());
    m_trackLabel.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    m_currentTimeLabel.setFixedWidth(cfgBar->timeWidth());
    m_currentTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);
    m_currentTimeLabel.setAlignment(Qt::AlignRight | Qt::AlignHCenter);
    m_totalTimeLabel.setFixedWidth(cfgBar->timeWidth());
    m_totalTimeLabel.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);

    m_lengthSlider.setEnabled(false);
    m_lengthSlider.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setVisible(false);
    m_volumeSlider.setRange(0, 100);
    m_volumeSlider.setValue(cfgPlayer->volume());
    m_volumeSlider.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
    m_volumeSlider.setFixedWidth(5 * cfgBar->iconSize() + 4 * cfgBar->spacing());

    m_playPauseButton.init({QIcon(ICO_PLAY), QIcon(ICO_PAUSE)}, cfgBar->iconSize());
    m_previousButton.init({QIcon(ICO_PREVIOUS)}, cfgBar->iconSize());
    m_nextButton.init({QIcon(ICO_NEXT)}, cfgBar->iconSize());
    m_shuffleButton.init({QIcon(ICO_SHUFFLE)}, cfgBar->iconSize(), true);
    m_loopButton.init({QIcon(ICO_LOOP)}, cfgBar->iconSize(), true);
    m_volumeButton.init({QIcon(ICO_VOLUME_FULL), QIcon(ICO_VOLUME_MEDIUM),
                         QIcon(ICO_VOLUME_LOW), QIcon(ICO_VOLUME_MUTE)}, cfgBar->iconSize());

    m_shuffleButton.setLocked(cfgPlayer->shuffle());
    m_loopButton.setLocked(cfgPlayer->loop());
    setVolumeIcon(cfgPlayer->volume());

    QGridLayout *layout = new QGridLayout(this);
    layout->setHorizontalSpacing(cfgBar->spacing());
    layout->setContentsMargins(cfgBar->margin(), cfgBar->margin(), cfgBar->margin(), cfgBar->margin());
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

void MusicBar::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}

void MusicBar::setButtonVisibility(bool visible)
{
    m_previousButton.setVisible(visible);
    m_playPauseButton.setVisible(visible);
    m_nextButton.setVisible(visible);
    m_shuffleButton.setVisible(visible);
    m_loopButton.setVisible(visible);
}

void MusicBar::hideButtons()
{
    setButtonVisibility(false);
}

void MusicBar::showButtons()
{
    setButtonVisibility(true);
}

void MusicBar::setVolumeConfig(int volume)
{
    cfgPlayer->setVolume(volume);
}

void MusicBar::setVolumeIcon(int volume)
{
    if (volume > 66)
        m_volumeButton.setSelectedIcon(0);
    else if (volume > 33)
        m_volumeButton.setSelectedIcon(1);
    else if (volume > 0)
        m_volumeButton.setSelectedIcon(2);
    else
        m_volumeButton.setSelectedIcon(3);
}

void MusicBar::setVolumePlayer(int volume)
{
    eggPlayer->setVolume(volume);
}

void MusicBar::setVolumeSlider(int volume)
{
    m_volumeSlider.setValue(volume);
}
