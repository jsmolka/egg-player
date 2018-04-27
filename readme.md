# egg-player
A Groove Music like music player.

## Features
### Customization
The player offers two ways for customizing the user interface and player in general. One comes in the form of css files located unter ```resources/css``` and allows the user to change mostly color and shape related things. If the proportions of the player are off on maschines with high dpi scaling, you can set a lot of hardcoded values in the config file located unter ```User/Documents/egg-player```.

### Global shortcuts
The player supports global shortcuts for the following actions with default shortcuts
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

The default settings for those settings are your keyboards media keys. If you do not have those or want to change the shortcuts, you can do that in the config file. There is a group called ```Shortcut``` wher you can insert a combination of shift, ctrl, alt and a key on the keyboard. All possible keys can be found in the [shortcut.cpp](https://github.com/jsmolka/egg-player/blob/master/src/utils/shortcut.cpp) file. One example for a shortcut combination would be ```Alt+Shift+P```. If you want to change it back into the media keys, you can simply use ```Media```.

### Error logs
If logging is enabled in the config, the player automatically logs all warnings and errors. Those are stored under ```User/Documents/egg-player```. If anything in the player does not work the log is a really good way to start. It tells you in which class the error occurred and what the error actually was.

## Roadmap
- [x] documentation
- [ ] playlist support
- [x] use [bass.dll](http://www.un4seen.com/) as audio backend
- [ ] own tag library based on [libmp3](https://github.com/TheOnlyCaky/libmp3) to support unicode characters
- [ ] proper scaling on different machines
- [x] proper multithreading
- [x] global shortcuts
- [ ] reactive cache

## Things to do
- black title bar through [Windows API](https://msdn.microsoft.com/en-us/library/windows/desktop/ms724940%28v=vs.85%29.aspx)
- custom css with repaint event for LengthSlider
- fixed size for labels in SongInfo
