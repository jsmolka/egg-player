#include "songinfo.hpp"

/*
 * Constructor.
 *
 * :param audio: audio pointer
 * :param parent: parent pointer
 */
SongInfo::SongInfo(Audio *audio, QWidget *parent) :
    QWidget(parent)
{
    pm_audio = audio;
}

/*
 * Destructor.
 */
SongInfo::~SongInfo()
{

}

/*
 * Initialize function. Loops over all
 * created labels and shows them with
 * stretch value.
 *
 * :param stretches: list of stretches
 */
void SongInfo::init(const QList<int> &stretches)
{
    QGridLayout *layout = new QGridLayout(this);
    setLayout(layout);

    for (int i = 0; i < m_labels.size(); i++)
    {
        layout->addWidget(m_labels[i], 0, i);
        layout->setColumnStretch(i, stretches[i]);
    }
}

/*
 * Show track.
 */
void SongInfo::showTrack()
{
    createLabel(QString::number(pm_audio->track()));
}

/*
 * Show title.
 */
void SongInfo::showTitle()
{
    createLabel(pm_audio->title());
}

/*
 * Show artist.
 */
void SongInfo::showArtist()
{
    createLabel(pm_audio->artist());
}

/*
 * Show album.
 */
void SongInfo::showAlbum()
{
    createLabel(pm_audio->album());
}

/*
 * Show year.
 */
void SongInfo::showYear()
{
    createLabel(QString::number(pm_audio->year()));
}

/*
 * Show genre.
 */
void SongInfo::showGenre()
{
    createLabel(pm_audio->genre());
}

/*
 * Show length.
 */
void SongInfo::showLength()
{
    createLabel(Utils::timeString(pm_audio->length()), Qt::AlignRight);
}

/*
 * Paint event for custom css.
 */
void SongInfo::paintEvent(QPaintEvent *)
{
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

/*
 * Creates label.
 *
 * :param string: text
 * :param align: horizontal alignment
 */
void SongInfo::createLabel(const QString &string, Qt::Alignment align)
{
    QLabel *label = new QLabel(string, this);
    label->setAlignment(align | Qt::AlignVCenter);
    label->setAttribute(Qt::WA_TranslucentBackground);
    m_labels << label;
}
