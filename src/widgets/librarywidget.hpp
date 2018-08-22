#ifndef LIBRARYWIDGET_HPP
#define LIBRARYWIDGET_HPP

#include <QVector>

#include "audio.hpp"
#include "audios.hpp"
#include "tablewidget.hpp"

class LibraryWidget : public TableWidget
{
    Q_OBJECT

public:
    explicit LibraryWidget(QWidget *parent = nullptr);
    ~LibraryWidget();

    enum AudioInfo {None, Title, Artist, Album, Track, Year, Genre, Duration};

    void setAudios(Audios *audios);
    void removeAudios();

    void addColumn(AudioInfo info, Qt::Alignment horizontal = Qt::AlignLeft, bool expand = true);

public slots:
    void insert(Audio *audio, int row = -1);

private slots:
    void onAudiosUpdated(Audio *audio);
    void onAudioInserted(int index);
    void onAudiosRemoved(int index);

private:
    struct Column
    {
        Column(AudioInfo info = AudioInfo::None, Qt::Alignment alignment = 0) :
            info(info), alignment(alignment) {}

        AudioInfo info;
        Qt::Alignment alignment;
    };

    void setup();
    void setupCss();

    QString audioText(Audio *audio, int column) const;

    Audios *m_audios;
    QVector<Column> m_columns;
};

#endif // LIBRARYWIDGET_HPP
