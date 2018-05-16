# egg-player
A Groove Music like music player.

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] [bass.dll](http://www.un4seen.com/) as audio backend
- [x] proper dpi scaling
- [ ] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Changes since lastest release
- add UTF-8 support
- improve startup times
- improve load times
- improve memory usage

## Things to do
### Internal
- add application startup to log
- add egg_old.log to store old logs
- more detailed logs, especially for player 
- char-by-char conversion instead of TStringToQString
- use namespaces or classes in utils
- max property for timer
- use milliseconds song time as timer max
- setting song to end should start next one
- BASS proper error handling
- prevent moving slider with arrow keys
- minimize amount of new allocations
- app minimum size
- clickable scrollbar
- music bar padding in config
- do not allow icon buttons to get focus
- add sorted option to library
- remove unnecessary description from events

### Cosmetic
- [black title bar](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- do not show certain info at low size
- library scroll acceleration
- highlight active song
- scrollbar with [round corners](https://stackoverflow.com/questions/12438095/qt-vertical-scroll-bar-stylesheets)
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
