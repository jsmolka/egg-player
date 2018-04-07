#include "musicbar.hpp"

MusicBar::MusicBar(QWidget *parent) : QWidget(parent)
{
    m_cache.connect();
    pm_player = new Player(this);

    setupUi();

    connect(pm_nextButton, SIGNAL(pressed()), pm_player, SLOT(next()));
    connect(pm_backButton, SIGNAL(pressed()), pm_player, SLOT(back()));
    connect(pm_loopButton, SIGNAL(locked(bool)), pm_player, SLOT(setLoop(bool)));
    connect(pm_shuffleButton, SIGNAL(locked(bool)), pm_player, SLOT(setShuffled(bool)));    
    connect(pm_playButton, SIGNAL(pressed()), this, SLOT(onPlayButtonPressed()));

    connect(pm_lengthSlider, SIGNAL(positionChanged(int)), pm_player, SLOT(setPosition(int)));

    connect(pm_player, SIGNAL(audioChanged(Audio *)), this, SLOT(onPlayerAudioChanged(Audio *)));
    connect(pm_player, SIGNAL(stateChanged(bool)), this, SLOT(onPlayerStateChanged(bool)));
    connect(pm_player, SIGNAL(positionChanged(int)), this, SLOT(onPlayerPositionChanged(int)));
}

MusicBar::~MusicBar()
{

}

Player * MusicBar::player()
{
    return pm_player;
}

QLabel * MusicBar::coverLabel()
{
    return pm_coverLabel;
}

QLabel * MusicBar::trackLabel()
{
    return pm_trackLabel;
}

QLabel * MusicBar::currentTimeLabel()
{
    return pm_currentTimeLabel;
}

QLabel * MusicBar::totalTimeLabel()
{
    return pm_totalTimeLabel;
}

LengthSlider * MusicBar::lengthSlider()
{
    return pm_lengthSlider;
}

IconButton * MusicBar::playButton()
{
    return pm_playButton;
}

IconButton * MusicBar::nextButton()
{
    return pm_nextButton;
}

IconButton * MusicBar::backButton()
{
    return pm_backButton;
}

IconButton * MusicBar::shuffleButton()
{
    return pm_shuffleButton;
}

IconButton * MusicBar::loopButton()
{
    return pm_loopButton;
}

IconButton * MusicBar::volumeButton()
{
    return pm_volumeButton;
}

void MusicBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QStyleOption option;
    option.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void MusicBar::onPlayButtonPressed()
{
    if (pm_player->index() != -1)
    {
        if (pm_playButton->selectedIcon() == 0)
            pm_player->play();
        else
            pm_player->pause();
    }
}

void MusicBar::onPlayerAudioChanged(Audio *audio)
{
    QPixmap cover = m_cache.cover(audio->path(), 50);

    pm_trackLabel->setText(QString("%1\n%2").arg(audio->title(), audio->artist()));
    pm_coverLabel->setPixmap(cover);

    pm_totalTimeLabel->setText(lengthString(audio->length()));
    pm_currentTimeLabel->setText(lengthString(0));
    pm_lengthSlider->setRange(0, audio->length());

    setColor(ColorUtil::backgroundColor(cover));
}

void MusicBar::onPlayerStateChanged(bool playing)
{
    pm_playButton->setSelectedIcon(playing ? 1 : 0);
}

void MusicBar::onPlayerPositionChanged(int position)
{
    pm_currentTimeLabel->setText(lengthString(position));
    if (!pm_lengthSlider->isPressed())
        pm_lengthSlider->setValue(position);
}

void MusicBar::setupUi()
{
    setFixedHeight(67);
    setStyleSheet(CSS_MUSICBAR);
    setAutoFillBackground(true);
    setColor(ColorUtil::backgroundColor(defaultCover()));

    QGridLayout *layout = new QGridLayout;
    layout->setSpacing(15);

    pm_coverLabel = new QLabel(this);
    pm_coverLabel->setPixmap(defaultCover());
    pm_coverLabel->setFixedSize(QSize(50, 50));
    layout->addWidget(pm_coverLabel, 0, 0);

    pm_trackLabel = new QLabel(this);
    pm_trackLabel->setFixedSize(QSize(240, 50));
    layout->addWidget(pm_trackLabel, 0, 1);

    pm_currentTimeLabel = new QLabel(this);
    pm_currentTimeLabel->setFixedWidth(60);
    pm_currentTimeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(pm_currentTimeLabel, 0, 2);

    pm_lengthSlider = new LengthSlider(this);
    pm_lengthSlider->setFixedHeight(50);
    layout->addWidget(pm_lengthSlider, 0, 3);

    pm_totalTimeLabel = new QLabel(this);
    pm_totalTimeLabel->setFixedWidth(60);
    pm_totalTimeLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(pm_totalTimeLabel, 0, 4);

    QList<IconButton *> buttons;
    QSize size(37, 37);

    pm_backButton = new IconButton(this);
    pm_backButton->init({QIcon(ICO_BACK)}, size);
    buttons << pm_backButton;

    pm_playButton = new IconButton(this);
    pm_playButton->init({QIcon(ICO_PLAY), QIcon(ICO_PAUSE)}, size);
    buttons << pm_playButton;

    pm_nextButton = new IconButton(this);
    pm_nextButton->init({QIcon(ICO_NEXT)}, size);
    buttons << pm_nextButton;

    pm_shuffleButton = new IconButton(this);
    pm_shuffleButton->init({QIcon(ICO_SHUFFLE)}, size, true);
    buttons << pm_shuffleButton;

    pm_loopButton = new IconButton(this);
    pm_loopButton->init({QIcon(ICO_REPLAY)}, size, true);
    buttons << pm_loopButton;

    pm_volumeButton = new IconButton(this);
    pm_volumeButton->init({QIcon(ICO_VOLUME), QIcon(ICO_MUTE)}, size);
    buttons << pm_volumeButton;

    int column = 5;
    for (IconButton *button : buttons)
    {
        layout->addWidget(button, 0, column);
        column++;
    }
    setLayout(layout);
}

QPixmap MusicBar::defaultCover()
{
    QPixmap image(IMG_DEFAULT_COVER);
    return image.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

QString MusicBar::lengthString(int length)
{
    int seconds = length % 60;
    int minutes = (length - seconds) / 60;

    QString secondsString = QString("%1").arg(seconds, 2, 10, QChar('0'));
    QString minutesString = QString::number(minutes);

    return QString("%1:%2").arg(minutesString, secondsString);
}

void MusicBar::setColor(const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::Background, color);
    setPalette(palette);
}
