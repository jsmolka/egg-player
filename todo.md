# Things to do

## Rework
- replace const static with static const
- proper style for ifdef in constants
- make code generally more robust and log unlikely behavior
- use namespaces
- Shortcut: use enums for repeat, no bool
- Player: make it a pure singleton
- use limit in database
- ThreadedObject: virtual function for objects per thread

## Database
- table with current version, converter functions
- properly fix "database is locked"
  - maybe create a DatabasePool singleton
  - loads and opens the database for a connection
  - properly closes and removes them at destruction

## Filesystem
- make it more robust
- prevent crashes when adding lots of files

## User interface
- adjust CSS classes for changes (possibly rename them)

### Bar
- use different sliders for volume and duration and volume
  - make the volume slider pop out instead of hiding other icons
  - improve the duration slider style (include some form of hover effect)

### Library
- create an expandable scrollbar for the library
  - show the current alphabet letter
- adjust appearance of library items
  - consider using a less "bright" white for less contrast
- improve smooth scrolling
  - maybe higher refresh rate
  - make it work properly on mouse and touchpad
- fix the bug where only one column is highlighted