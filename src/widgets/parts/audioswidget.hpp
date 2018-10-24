#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QVector>

#include "core/audio.hpp"
#include "core/audios.hpp"
#include "core/globals.hpp"
#include "widgets/parts/tablewidget.hpp"

namespace AudioInfo
{
    enum Info {Title, Artist, Album, Track, Year, Genre, Duration};
}

class AudiosWidget : public TableWidget
{
    Q_OBJECT

public:
    explicit AudiosWidget(QWidget *parent = nullptr);

    void setAudios(Audios *audios);
    Audios *audios() const;

    void addColumn(AudioInfo::Info info, Qt::Alignment horizontal = Qt::AlignLeft, bool expand = true);

private slots:
    void onAudiosUpdated(int row);
    void onAudiosInserted(int row);
    void onAudiosRemoved(int row);
    void onAudiosMoved(int from, int to);

private:
    struct Column
    {
        AudioInfo::Info info;
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
