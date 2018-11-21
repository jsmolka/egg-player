# Things to do

## General
- properly bind the column in database queries
- explore the benefits of smart pointers and the limits of Qt parenting
- properly forward declare classes, remove unnecessary ones from headers
- explore the benefits of enum classes and flags
- create a base class or a template for pimpl idiom classes

## Audio
- implement Audio using the pimpl idiom
- create constructors and operators to keep the overhead low when copying
- figure out how to create a std::shared_pointer using a nullptr

## Logger
- rewrite the logger using a Qt like [syntax](https://github.com/crosire/reshade/blob/master/source/log.hpp)
- add different log levels (info, warning, fatal)
- exit the application using a message box if the level is fatal
- add a macro for each level (egg_info(), egg_warning(), egg_fatal())
- try finding a way to keep the stream open, close at error
- maybe define streams for classes which use the logger

## Macros
- rename property macros to EGG_PROP_P / C
- remove the macros for getter and setter or make them private
- add property macro for pimple classes (EGG_PROP_P)

## User Interface

### Bar
- use different sliders for volume and duration
  - make the volume slider pop out instead of hiding other icons
  - improve the duration slider style (include some form of hover effect)
  - create a unique handle for the duration slider
- update the track label if the played audio has been modified
- consider splitting into more subclasses
- fade cover through black when changing the audio
- create an AudioFinder class which handles keystrokes
  - create keyReset config field

### Library
- make the scrollbar expandable
- adjust the appearance of library items
  - consider using a less bright white
  - consider using a slightly smaller font size
- add vertical black bars to the library border
- improve smooth scrolling