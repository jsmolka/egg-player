# egg-player
A Groove Music like music player.

## Roadmap
- [ ] documentation
- [ ] playlist support
- [x] [taglib](https://github.com/taglib/taglib) for tag reading
- [x] [bass.dll](http://www.un4seen.com/) as audio backend
- [x] proper dpi scaling
- [x] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Things to do

### General
- rewrite library widget
- fix bug with shuffle and first song
- tweak smooth tablewidget values
  - see line 67
- create different sizes for icon button (make them less blurry)
- change directory structure
- disable scrollwheel on slider

### Threading
- look into write-ahread-logging
- create threads with worker threads inside of them
- audio loader
  - chunk the globbed files and pass them to worker threads
  - the worker threads loads the audios from the cache or from file and emits them
  - the audio loader inserts them into the cache and updates outdated ones
  - add an option audio objects to show that is loaded from the cache
- cache builder
  - only load covers for new and outdated audios
- rewrite library

### Reactive cache
- use a file system watcher
- update library, cache and audios accordingly

### Windows util
- create a windows util
- use defines to make it cross platform compatible
- change app background color to black to prevent white flashing when resizing
  - need to use the [windows api](https://forum.qt.io/topic/69867/temporary-white-border-on-resizing-qt-quick-application-window-on-windows-desktop/2)
  - remove background color from css
- move config scale functions into this util
- move shortcut register functions into this util
  
### User interface
- do not show certain info at low size
- fuzzy library searching
- [expand scrollbar](https://stackoverflow.com/a/23677355/7057528)
- [scrollable text](https://stackoverflow.com/a/10655396/7057528)