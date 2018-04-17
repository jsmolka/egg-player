# egg-player
A Groove Music like music player.

## Features
- cover caching and short startup times
- customizable user inferface thanks to css and configs
- error logs

## Roadmap
- play audio formats apart from mp3
- use a different audio backend like [bass.dll](http://www.un4seen.com/)
- playlist support
- write own tag library to support unicode characters based on [libmp3](https://github.com/TheOnlyCaky/libmp3)
- proper scaling on different maschines
- proper multithreading
- system wide shortcuts
- reactive cache

## Known issues
#### Songs do not play
This has something to do with the default audio backend Qt is using for Windows. It is called DirectShow and for some reason it is not able to play mp3 files with large covers (around 100kb).
Possible fixes:
- replace covers of not playing songs with smaller covers (everything lower than 100kb should be ok)
- swtich Qt mediaplayer backend to WMF with the configuration option ```-mediaplayer-backend wmf```
- downloading a different audio backend like [K-Lite](https://www.codecguide.com/download_kl.htm).

#### Songs play longer than displayed
todo: write

## Things to do

#### General
- [black title bar](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
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
