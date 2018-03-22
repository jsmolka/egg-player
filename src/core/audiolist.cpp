#include "audiolist.hpp"

AudioList::AudioList()
{

}

void AudioList::sortByTitle(bool reverse)
{
    if (!reverse)
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.title() < a2.title();});
    else
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.title() > a2.title();});
}

void AudioList::sortByArtist(bool reverse)
{
    if (!reverse)
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.artist() < a2.artist();});
    else
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.artist() > a2.artist();});
}

void AudioList::sortByAlbum(bool reverse)
{
    if (!reverse)
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.album() < a2.album();});
    else
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.album() > a2.album();});
}

void AudioList::sortByTrack(bool reverse)
{
    if (!reverse)
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.track() < a2.track();});
    else
        std::sort(begin(), end(),
            [](const Audio &a1, const Audio &a2) {return a1.track() > a2.track();});
}
