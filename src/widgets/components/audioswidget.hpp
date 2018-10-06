#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QVector>

#include "audio.hpp"
#include "audios.hpp"
#include "tablewidget.hpp"

class AudiosWidget : public TableWidget
{
    Q_OBJECT

public:
    enum AudioInfo {Title, Artist, Album, Track, Year, Genre, Duration};

    explicit AudiosWidget(QWidget *parent = nullptr);

    void setAudios(Audios *audios);
    void addColumn(AudioInfo info, Qt::Alignment horizontal = Qt::AlignLeft, bool expand = true);

private slots:
    void onAudiosUpdated(int row);
    void onAudiosInserted(int row);
    void onAudiosRemoved(int row);
    void onAudiosMoved(int from, int to);

private:
    struct Column
    {
        AudioInfo info;
        Qt::Alignment alignment;
    };
    void insert(Audio *audio, int row = -1);
    QString audioText(Audio *audio, int column) const;

    void setup();
    void setupCss();

    Audios *m_audios;
    QVector<Column> m_columns;
};

#endif // AUDIOSWIDGET_HPP
