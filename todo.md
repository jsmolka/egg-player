# Things to do
- replace const static with static const
- proper style for ifdef in constants

## Cache
- introduce versioning system with own table
- use current state as first version and write possible conversions for future changes
- save current state at exiting / load at startup

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