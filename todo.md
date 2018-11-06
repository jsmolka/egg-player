# Things to do

## Notes
- Audios
  - delete current state in player / playlist
  - use smart pointer for automatic deletion
- BarWidget
  - update name if the current audio changes
  - properly split into subclasses
- TableWidget
  - consider the following changes
    - [replace hover with select](https://stackoverflow.com/questions/8644367/how-to-highlight-a-row-in-qtablewidget)
    - [hover implementation 1](https://stackoverflow.com/questions/20565930/qtableview-how-can-i-highlight-the-entire-row-for-mouse-hover)
    - [hover implementation 2](https://stackoverflow.com/questions/23111075/how-to-highlight-the-entire-row-on-mouse-hover-in-qtablewidget-qt5)
- Threading
  - moveToThread maybe protected

##  Post-Rework
- remove globals
- remove unnecessary getter / setter

## Rework
- replace const static with static const
- proper style for ifdef in constants
- make code generally more robust and log unlikely behavior
- use namespaces
- Player: make it a pure singleton
- use limit in database
- process ThreadObject events differently
- edit project file and exclude windows libraries

## Database Rework
- table with current version, converter functions
- properly fix "database is locked"
  - maybe create a DatabasePool singleton
    - assign db reference to base, save in provider
  - loads and opens the database for a connection
  - properly closes and removes them at destruction
- proper query binding

## Filesystem Rework
- make it more robust
- split into more and better classes
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