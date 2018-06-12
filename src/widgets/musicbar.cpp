#include "musicbar.hpp"

/*
 * Constructor.
 *
 * :param parent: parent, default nullptr
 */
MusicBar::MusicBar(QWidget *parent) :
    QWidget(parent),
    m_coverLabel(this),
    m_trackLabel(this),
    m_currentTimeLabel(this),
    m_totalTimeLabel(this),
    m_playPauseButton(this),
    m_nextButton(this),
    m_previousButton(this),
    m_shuffleButton(this),
    m_loopButton(this),
    m_volumeButton(this),
    m_lengthSlider(this),
    m_volumeSlider(this),
    m_scPlayPause(cfgShortcut->playPause(), false, this),
    m_scNext(cfgShortcut->next(), false, this),
    m_scPrevious(cfgShortcut->previous(), false, this),
    m_scVolumeUp(cfgShortcut->volumeUp(), true, this),
    m_scVolumeDown(cfgShortcut->volumeDown(), true, this)
{
    setup();
    setupUi();

    connect(eggPlayer, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(eggPlayer, SIGNAL(stateChanged(Player::PlayerState)), this, SLOT(onPlayerStateChanged(Player::PlayerState)));
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
    connect(&m_volumeSlider, SIGNAL(sliderValueChanged(int)), SLOT(onVolumeSliderValueChanged(int)));

    connect(&m_scPlayPause, SIGNAL(pressed()), this, SLOT(onShortcutPlayPausePressed()));
    connect(&m_scNext, SIGNAL(pressed()), eggPlayer, SLOT(next()));
    connect(&m_scPrevious, SIGNAL(pressed()), eggPlayer, SLOT(previous()));
    connect(&m_scVolumeUp, SIGNAL(pressed()), this, SLOT(onShortcutVolumeUpPressed()));
    connect(&m_scVolumeDown, SIGNAL(pressed()), this, SLOT(onShortcutVolumeDownPressed()));
}

/*
 * Destructor.
 */
MusicBar::~MusicBar()
{

}

/*
 * Getter for cover label.
 *
 * :return: cover label
 */
QLabel * MusicBar::coverLabel()
{
    return &m_coverLabel;
}

/*
 * Getter for track label property.
 *
 * :return: track label
 */
QLabel * MusicBar::trackLabel()
{
    return &m_trackLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label
 */
QLabel * MusicBar::currentTimeLabel()
{
    return &m_currentTimeLabel;
}

/*
 * Getter for time label property.
 *
 * :return: time label
 */
QLabel * MusicBar::totalTimeLabel()
{
    return &m_totalTimeLabel;
}

/*
 * Getter for play pause button property.
 *
 * :return: play pause button
 */
IconButton * MusicBar::playPauseButton()
{
    return &m_playPauseButton;
}

/*
 * Getter for next button property.
 *
 * :return: next button
 */
IconButton * MusicBar::nextButton()
{
    return &m_nextButton;
}

/*
 * Getter for back button property.
 *
 * :return: back button
 */
IconButton * MusicBar::previousButton()
{
    return &m_previousButton;
}

/*
 * Getter for shuffle button property.
 *
 * :return: shuffle button
 */
IconButton * MusicBar::shuffleButton()
{
    return &m_shuffleButton;
}

/*
 * Getter for loop button property.
 *
 * :return: loop button
 */
IconButton * MusicBar::loopButton()
{
    return &m_loopButton;
}

/*
 * Getter for volume button property.
 *
 * :return: volume button
 */
IconButton * MusicBar::volumeButton()
{
    return &m_volumeButton;
}

/*
 * Getter for length slider property.
 *
 * :return: length slider
 */
ClickableSlider * MusicBar::lengthSlider()
{
    return &m_lengthSlider;
}

/*
 * Getter for volume slider property.
 *
 * :return: volume slider
 */
ClickableSlider * MusicBar::volumeSlider()
{
    return &m_volumeSlider;
}

/*
 * Paint event for custom css.
 */
void MusicBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

/*
 * Sets up all relevant audio information.
 *
 * :param audio: audio
 */
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

/*
 * Sets the corresponding icon of the play button.
 *
 * :param state: player state
 */
void MusicBar::onPlayerStateChanged(Player::PlayerState state)
{
    m_playPauseButton.setSelectedIcon(state == Player::PlayerState::Playing ? 1 : 0);
}

/*
 * Sets the slider position if it is not pressed.
 *
 * :param position: position in seconds
 */
void MusicBar::onPlayerPositionChanged(int position)
{
    if (!m_lengthSlider.isPressed())
    {
        m_currentTimeLabel.setText(Util::time(position));
        m_lengthSlider.setValue(position);
    }
}

/*
 * Sets the volume button icon. All other things retarding volume are done
 * separately.
 */
void MusicBar::onPlayerVolumeChanged(int volume)
{
    setVolumeIcon(volume);
}

/*
 * Starts or pauses the player depeding on the button icon.
 */
void MusicBar::onPlayPauseButtonPressed()
{
    if (m_playPauseButton.selectedIcon() == 0)
        eggPlayer->play();
    else
        eggPlayer->pause();
}

/*
 *
 * Applies the shuffle state to the player and saves it in the config.
 *
 * :param locked: locked
 */
void MusicBar::onShuffleButtonLocked(bool locked)
{
    eggPlayer->setShuffle(locked);
    cfgPlayer->setShuffle(locked);
}

/*
 * Applies the loop state to the player and saves it in the config.
 *
 * :param locked: locked
 */
void MusicBar::onLoopButtonLocked(bool locked)
{
    eggPlayer->setLoop(locked);
    cfgPlayer->setLoop(locked);
}

/*
 * Shows or hides the volume slider.
 */
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

/*
 * Sets the value of the current time label.
 *
 * :param value: position in seconds
 */
void MusicBar::onLengthSliderMoved(int value)
{
    m_currentTimeLabel.setText(Util::time(value));
}

/*
 * Sets the player position. The current times label does not need to be changed
 * because it is connection to the player position changed.
 *
 * :param value: position in seconds
 */
void MusicBar::onLengthSliderValueChanged(int value)
{
    if (value != eggPlayer->currentAudio()->duration())
        eggPlayer->setPosition(value);
    else
        eggPlayer->next();
}

/*
 * Sets the player volume. Does not change the config because of performance
 * reason.
 *
 * :param value: value
 */
void MusicBar::onVolumeSliderMoved(int value)
{
    setVolumePlayer(value);
}

/*
 * Changes the player volume and config value accordingly.
 *
 * :param value: value
 */
void MusicBar::onVolumeSliderValueChanged(int value)
{
    setVolumeConfig(value);
    setVolumePlayer(value);
}

/*
 * Plays or pauses the player.
 */
void MusicBar::onShortcutPlayPausePressed()
{
    if (eggPlayer->isPlaying())
        eggPlayer->pause();
    else
        eggPlayer->play();
}

/*
 * Increases the player volume.
 */
void MusicBar::onShortcutVolumeUpPressed()
{
    changeVolume(eggPlayer->volume(), 1);
}

/*
 * Decreases the player volume.
 */
void MusicBar::onShortcutVolumeDownPressed()
{
    changeVolume(eggPlayer->volume(), -1);
}

/*
 * Loads the style sheet and replaces placeholders.
 */
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

/*
 * Sets up widget.
 */
void MusicBar::setup()
{
    loadCss();

    setAutoFillBackground(true);
    setFixedHeight(cfgBar->height());
    setColor(ColorUtil::background(Util::defaultCover()));
}

/*
 * Sets up user interface.
 */
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

/*
 * Sets music bar color.
 *
 * :param color: color
 */
void MusicBar::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}

/*
 * Sets visibility for all buttons.
 *
 * :param visible: visible
 */
void MusicBar::setButtonVisibility(bool visible)
{
    m_previousButton.setVisible(visible);
    m_playPauseButton.setVisible(visible);
    m_nextButton.setVisible(visible);
    m_shuffleButton.setVisible(visible);
    m_loopButton.setVisible(visible);
}

/*
 * Hides all buttons.
 */
void MusicBar::hideButtons()
{
    setButtonVisibility(false);
}

/*
 * Shows all buttons.
 */
void MusicBar::showButtons()
{
    setButtonVisibility(true);
}

/*
 * Sets player volume in config.
 *
 * :param volume: volume
 */
void MusicBar::setVolumeConfig(int volume)
{
    cfgPlayer->setVolume(volume);
}

/*
 * Sets volume icon according to volume.
 *
 * :param volume: volume
 */
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

/*
 * Sets player volume.
 *
 * :param volume: volume
 */
void MusicBar::setVolumePlayer(int volume)
{
    eggPlayer->setVolume(volume);
}

/*
 * Sets volume slider position.
 *
 * :param volume: volume
 */
void MusicBar::setVolumeSlider(int volume)
{
    m_volumeSlider.setValue(volume);
}

/*
 * Changes volume by a step.
 *
 * :param volume: volume
 * :param step: step
 */
void MusicBar::changeVolume(int volume, int step)
{
    volume = volume + step;
    if (volume < 0 || volume > 100)
        return;

    setVolumeConfig(volume);
    setVolumePlayer(volume);
    setVolumeSlider(volume);
}
