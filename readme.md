# egg-player
A Groove Music like music player.

## Features
- cover caching and short startup times
- customizable user inferface thanks to css and configs
- error logs

## Roadmap
- playlist support
- write own tag library to support unicode characters based on [libmp3](https://github.com/TheOnlyCaky/libmp3)
- proper scaling on different maschines
- proper multithreading
- system wide shortcuts
- reactive cache

## Known issues
### Songs do not play
This has something to do with the default audio backend Qt is using for Windows. It is called DirectShow and for some reason it is not able to play mp3 files with large covers (around 100kb).
Possible fixes:
- switch Qt mediaplayer backend to WMF with the configuration option ```-mediaplayer-backend wmf```
- downloading a different audio backend like [K-Lite](https://www.codecguide.com/download_kl.htm).
- replace covers of not playing songs with smaller covers (everything lower than 100kb should be ok)

### Songs play longer than displayed
This, again, has something to do with the DirectShow backend. The duration it uses is usually some seconds longer than the actual duration and as a result of that the audio is slighty strechted.
Possible fixed:
- switch Qt mediaplayer backend to WMF with the configuration option ```-mediaplayer-backend wmf```

## Things to do

#### General
- black title bar through [Windows API](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- documentation

#### Cache
- faster caching

#### Library
- add slots and signals
- splash screen while caching
- artist / album maps

#### LengthSlider
- custom css with repaint event

#### MusicLibrary
- songs / albums / artists tabs
