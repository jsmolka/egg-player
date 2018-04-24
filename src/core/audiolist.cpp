#include "audiolist.hpp"

/*
 * Sorts audio list by title.
 */
void AudioList::sortByTitle()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return QString::compare(a1->title(),
                                    a2->title(),
                                    Qt::CaseInsensitive) < 0;
        }
    );
}

/*
 * Sorts audio list by artist.
 */
void AudioList::sortByArtist()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return QString::compare(a1->artist(),
                                    a2->artist(),
                                    Qt::CaseInsensitive) < 0;
        }
    );
}

/*
 * Sorts audio list by album.
 */
void AudioList::sortByAlbum()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return QString::compare(a1->album(),
                                    a2->album(),
                                    Qt::CaseInsensitive) < 0;
        }
    );
}

/*
 * Sorts audio list by track.
 */
void AudioList::sortByTrack()
{
    std::sort(begin(), end(),
        [](const Audio *a1, const Audio *a2) {
            return a1->track() < a2->track();
        }
    );
}
