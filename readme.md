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

## Things to do

### Internal
- move library into music library
- use a member query
- multithreaded loading for uncached songs
- use QFileSystemWatcher
- duration instead of length
- cache transaction (commit in destructor)
- load uncached audios in multiple threads
- test for max in timer pause

### Cosmetic
- do not show certain info at low size
- library scroll acceleration
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
- color transition in bar

### Future
- search the library by typing
- themes