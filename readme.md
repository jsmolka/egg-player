# egg-player
A Groove Music like music player.

## Features
### Customization
Instead of using Qt's resource system the Egg Player loads its customizable files at every start. This includes the css files under ```resources/css``` which allow all kind of color and shape related changes. Apart from that there is a global config file located under ```User/Documents/egg-player```. This config holds, next to shortcuts and general settings, a lot of user interface related values. Those might be useful for machines with higher dpi scaling because the app is not optimized for use cases like that right now. In those cases the user can manually these values to create an appealing look.

### Global shortcuts
The Egg Player supports global shortcuts for media actions. The following tables contains those media actions with their default values.
<table>
  <tr>
    <th>Action</th>
    <th>Shortcut</th>
  </tr>
  <tr>
    <td>play / pause song</td>
    <td>Ctrl + F11</td>
  </tr>
  <tr>
    <td>play next song</td>
    <td>Ctrl + F12</td>
  </tr>
  <tr>
    <td>play previous song</td>
    <td>Ctrl + F10</td>
  </tr>
  <tr>
    <td>increase volume</td>
    <td>Ctrl + F8</td>
  </tr>
  <tr>
    <td>decrease volume</td>
    <td>Ctrl + F7</td>
  </tr>
</table>

Those default values can be changed by simply altering their value in the config file which gets parsed at every startup. There is a group called ```Shortcut``` where the user can insert a combination of shift, ctrl, alt and a key on the keyboard. All possible keys can be found in the [shortcut.cpp](https://github.com/jsmolka/egg-player/blob/master/src/utils/shortcut.cpp) file. One example for a shortcut combination would be ```Alt+Shift+P```. Note that you cannot use the same shortcut for two actions or reuse a shortcut which is being used by the system already.

### Error logs
If logging is enabled in the config, the player automatically logs all warnings and errors. Those are stored under ```User/Documents/egg-player```. If anything in the player does not work the log is a really good place to start. It tells you in which class the error or warning occurred and gives you a rather detailed description.

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] use [bass.dll](http://www.un4seen.com/) as audio backend
- [ ] own tag library based on [libmp3](https://github.com/TheOnlyCaky/libmp3) to support unicode characters
- [ ] proper scaling on different machines
- [ ] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Changes since newest release

### New features
- multiple library paths

### Changelog
- use json for config

## Things to do
- [black title bar](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- fixed size for labels in SongInfo
- fix weird center alignment of volume slider
- do not show certain info at low size
- loads Library in thread and signal that it is ready -> update user interface
- library scroll acceleration
- make app [DPI unware](https://msdn.microsoft.com/en-us/library/windows/desktop/mt846517%28v=vs.85%29.aspx)
- css round border for all devices
