# egg-player
A Groove Music like music player.

## Known issues
#### Songs do not play
This has something to do with the audio codec / backend Qt is using for Windows. It is called DirectShow and for some reason it is not able to play mp3 files with high resolution / dpi covers. Possible fixes are replacing the current song covers with lower dpi versions (500 pixel should be enough anyway) or downloading a different audio backend like [K-Lite](https://www.codecguide.com/download_kl.htm).

## Things to do

#### General
- [black title bar](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- good scaling without config
- documentation
- recompile with different audio backend

#### Cache
- faster caching

#### Library
- add slots and signals
- splash screen while caching
- artist / album maps

#### LengthSlider
- custom css with repaint event

#### Player
- remove time delay at start / overhead at end

#### MusicBar
- fix problems with long songs

#### MusicLibrary
- songs / albums / artists tabs
