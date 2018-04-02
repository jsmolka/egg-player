# egg-player
A Groove Music like music player.

## Known issues
#### Songs do not play
This has something to do with the audio codec / backend Qt is using for Windows. It is called DirectShow and for some reason it is not able to play mp3 files with high resolution / dpi covers. Possible fixes are replacing the current song covers with lower dpi versions (500 pixel should be enough anyway) or downloading a different audio backend like [K-Lite](https://www.codecguide.com/download_kl.htm).

## Things to do

#### General
- black window
- documentation
- recompile with different audio backend

##### library.cpp
- splash screen while caching
- artist / album maps
- proper destructor for audio pointer

#### musiclibrary.cpp
- songs / albums / artists tabs

##### colorutil.cpp
- constant time for algorithm
- prefer 'colorful' colors over dark ones
