# cellar
### bottle management tool for WINE connoisseurs
*(this software is considered unfinished, use at own risk)*

(notice: https://github.com/origintopleft/cellar is a mirror. The upstream repository is at [vcs.lavacano.net/cellar.git](http://vcs.lavacano.net/?p=cellar.git), and bugs are officially tracked at [mantis.lavacano.net](http://mantis.lavacano.net))

## Installation

    $ mkdir build && cd build
    $ cmake ..
    $ make -j4
    $ sudo make install

cellar also supports the use of clang as your compiler and/or ninja as your make system, for those of you who have opinions on such things.

## Quick Usage Primer

    $ cellar create steam
    $ cellar -b steam winetricks vcrun2012

    # without the -b argument, cellar assumes you want to deal with ~/.wine
    # you can manage which bottle that points to with this command
    $ cellar activate steam

    # arguments passed to "cellar launch" are passed to wine
    $ cellar launch /mnt/windows/Steam/Steam.exe

## Features
* **Corking**: Saves a bottle's configuration, including any pressed installers (see below) or installed winetricks, to a directory, then removes the WINE bottle from disk.
  You can then easily rebuild that WINE bottle later by uncorking it, which will automatically rebuild the WINE bottle with your active (or specified) version of WINE, as
  well as install any saved winetricks or run any pressed installers.
* **Pressed Installers**: Saves a copy of an installer to `~/.cellar`, writes it down in the bottle configuration, then runs it within your WINE bottle. If you choose to
  cork this bottle later, this installer will automatically be run after uncorking. If the installer comes with "unattended install" arguments, it's recommended you press
  those in too.
* **Easy WINE and bottle management**: Need a specific bottle for a specific program? `cellar -b bottlename <command>`. Does the bottle need to run a specific instance of
  WINE? `cellar config wine-path /opt/wine-specific/bin/wine`. Confused about which bottle is "active"? `cellar active` will tell you. Different programs may need drastically
  different WINE configurations, but that doesn't mean you need the drastic headaches.

## License
Cellar is available under [the MIT license](https://opensource.org/licenses/MIT).
