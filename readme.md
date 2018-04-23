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
- [ ] own tag library based on [libmp3](https://github.com/TheOnlyCaky/libmp3) to support unicode characters
- [ ] proper scaling on different machines
- [x] proper multithreading
- [ ] system wide shortcuts
- [ ] reactive cache

## Things to do
- black title bar through [Windows API](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- custom css with repaint event for LengthSlider
- use exact milliseconds time in timer, signal at song end
- lengthString function into Util class
