# egg-player
A Groove Music like music player.

## Features
- cover caching and short startup times
- customizable user inferface thanks to css and config
- error logs

## Roadmap
- documentation
- playlist support
- write own tag library to support unicode characters based on [libmp3](https://github.com/TheOnlyCaky/libmp3)
- proper scaling on different machines
- proper multithreading
- system wide shortcuts
- reactive cache

## Known issues
### Songs do not play
This has something to do with the default mediaplayer backend Qt is using under Windows. It's called DirectShow and unable to play audios with covers greater than 100kb.

Possible fixes:
- switch Qt mediaplayer backend to WMF with the configuration option ```-mediaplayer-backend wmf```
- download a different audio backend like [K-Lite](https://www.codecguide.com/download_kl.htm)
- replace covers of not playing songs with smaller ones

### Songs play longer than displayed
This, again, has something to do with the DirectShow backend. The duration it uses is usually some seconds longer than the actual duration. As a result of that the audio is slighty strechted and plays longer than it should.

Possible fixes:
- switch Qt mediaplayer backend to WMF with the configuration option ```-mediaplayer-backend wmf```

## Things to do
- black title bar through [Windows API](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- faster caching
- splash screen while caching
- add slots and signals for Library
- custom css with repaint event for LengthSlider
- fill cover to always get square
