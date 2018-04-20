# egg-player
A Groove Music like music player.

## Features
- cover caching and short startup times
- customizable user inferface thanks to css and config
- error logs

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] use [bass.dll](http://www.un4seen.com/) as audio backend
- [ ] write own tag library to support unicode characters based on [libmp3](https://github.com/TheOnlyCaky/libmp3)
- [ ] proper scaling on different machines
- [ ] proper multithreading
- [ ] system wide shortcuts
- [ ] reactive cache

## Things to do
- black title bar through [Windows API](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- faster caching
- splash screen while caching
- add slots and signals for Library
- custom css with repaint event for LengthSlider
