#include "audiolist.hpp"

void AudioList::sortByTitle()
{
    std::sort(begin(), end(),
        [](const Audio &a1, const Audio &a2) {return a1.title() < a2.title();});
}

void AudioList::sortByArtist()
{
    std::sort(begin(), end(),
        [](const Audio &a1, const Audio &a2) {return a1.artist() < a2.artist();});
}

void AudioList::sortByAlbum()
{
    std::sort(begin(), end(),
        [](const Audio &a1, const Audio &a2) {return a1.album() < a2.album();});
}

void AudioList::sortByTrack()
{
    std::sort(begin(), end(),
        [](const Audio &a1, const Audio &a2) {return a1.track() < a2.track();});
}
