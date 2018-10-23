# Things to do
- replace const static with static const
- proper style for ifdef in constants
- make code generally more robust and log unlikely behavior
- remove custom file and path type
- use imports relative to main ("core/audio.hpp", "core/db/audio.hpp")
- use namespaces
- switch getter and setter position (also in macro)
- use SqlRecord in Cover

## Database
- save the currently played audio (with position) and try to load it on start
- split into multiple classes with different functionality
- DbProvider
  - returns /creates the database of the current thread
- DbInitializer
  - initializes database
  - create tables
  - insert default cover
  - convert between versions
    - alter columns depending on the current db version
- DbItem
  - base class for db items / tables
  - assignTo function to assign to corresponding class
  - commit function to apply made changes to the database
  - several getby functions
  - use a base function for getby and just pass the condition (consider limit)
- DbComplex
  - contains functions which will alter multiple tables at the same time

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