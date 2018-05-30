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
- use member query
- use member database
- cache transaction
  - start in constructor
  - commit in destructor
  - consider passing a flag for read only
- use QFileSystemWatcher
  - update library accordingly
- multithreaded loading for uncached songs
  - store uncached songs in vector
  - load audios in multiple threads
  - store audios in vector
  - insert all in a background thread
- duration instead of length
- check max in timer pause
- store file size in cache
- update audio if size changed
- search the library by typing
  - search based on sorted
  - store last result, show it if there is no current
  - reset search string after certain time

### Cosmetic
- do not show certain info at low size
- [smooth scrolling](https://github.com/zhou13/qsmoothscrollarea)
- color transition in bar