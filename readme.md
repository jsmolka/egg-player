# egg-player
A Groove Music like music player.

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] [bass.dll](http://www.un4seen.com/) as audio backend
- [x] proper dpi scaling
- [x] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Changes since lastest release
- improve load time

## Things to do

### Internal
- max property for timer
- use milliseconds song time as timer max
- singleton for config
- move library into music library

### Cosmetic
- [black title bar](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- do not show certain info at low size
- library scroll acceleration
- highlight active song
- scrollbar with [round corners](https://stackoverflow.com/questions/12438095/qt-vertical-scroll-bar-stylesheets)
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
- remove library hover style after exit
- proper hover style while and after resizing

### Future
- search the library by typing
- themes