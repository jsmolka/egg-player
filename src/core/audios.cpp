#include "audios.hpp"

/*
 * Sorts vector by title.
 */
void Audios::sortByTitle()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return QString::compare(
                a1->title(),
                a2->title(),
                Qt::CaseInsensitive) < 0;
        }
    );
}

/*
 * Sorts vector by artist.
 */
void Audios::sortByArtist()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return QString::compare(
                a1->artist(),
                a2->artist(),
                Qt::CaseInsensitive) < 0;
        }
    );
}

/*
 * Sorts vector by album.
 */
void Audios::sortByAlbum()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return QString::compare(
                a1->album(),
                a2->album(),
                Qt::CaseInsensitive) < 0;
        }
    );
}

/*
 * Sorts vector by track.
 */
void Audios::sortByTrack()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return a1->track() < a2->track();
        }
    );
}
