from os import getcwd
from os import makedirs
from os.path import basename
from os.path import dirname
from os.path import exists
from os.path import join
from shutil import copyfile


def copy(src, dst):
    """
    Copies a file from src to dst. Creates the dst dir it does not 
    exist already.

    :param src: source file
    :param dst: destination file
    """
    directory = dirname(dst)
    if not exists(directory):
        makedirs(directory)
    try:
        copyfile(src, dst)
    except IOError as err:
        print(str(err))


def main():
    """
    This function copies all necessary files needed for deployment
    into the specified deployment directory. The paths which might 
    need to be specified are marked by comments.
    """
    qt = "C:/Qt/5.11.1/msvc2017_64"  # Qt install directory
    deploy = join(getcwd(), "egg-player")  # Deployment directory

    tree = {
        deploy: [
            join(getcwd(), "bin/release/egg-player.exe"),  # Relase application location
            join(getcwd(), "lib/bass-2.4/bin/bass.dll"),  # Bass dll location
            join(getcwd(), "lib/taglib-1.11.1/bin/tag.dll"),  # TagLib dll location
            join(qt, "bin/Qt5Core.dll"),
            join(qt, "bin/Qt5Gui.dll"),
            join(qt, "bin/Qt5Sql.dll"),
            join(qt, "bin/Qt5Widgets.dll")
        ],
        join(deploy, "imageformats"): [
            join(qt, "plugins/imageformats/qjpeg.dll")
        ],
        join(deploy, "platforms"): [
            join(qt, "plugins/platforms/qwindows.dll")
        ],
        join(deploy, "sqldrivers"): [
            join(qt, "plugins/sqldrivers/qsqlite.dll")
        ],
        join(deploy, "styles"): [
            join(qt, "plugins/styles/qwindowsvistastyle.dll")
        ]
    }

    for path, files in tree.items():
        for f in files:
            new = join(path, basename(f))
            print(f, ">", new)
            copy(f, new)


if __name__ == "__main__":
    main()
