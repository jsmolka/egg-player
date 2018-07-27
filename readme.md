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

## Changes since lastest release
- significantly improve audio caching 
- significantly improve cover caching 
- change icon hover style

## Things to do

### General
- rewrite library widget
- qt key sequence for shortcut
- proper template function implementation for chunk
- look into cache cover id getter
- look into compile error for types
- do not update the player if it is not playing
- rename audio to track
- implement isocpp guidelines
- varadic template for logger
- use audio checksum to detect changes


### Utils
- update fileutil
  - add readline, use in config
  - optional default value for read function
  - diriterator with filter and files only
- use inline functions for utils
- move css loading to its widget
- move font loading from util to main
- save mainwindow pre fullscreen size
- abstractcontroller dry
- use static inside instance function

### Icons
- use svg format / different sizes
- test icons in the icon preview example

### Cache
- query cover by id in music bar
- add move functions for more use cases

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
- [color transition](https://stackoverflow.com/a/34445886/7057528)