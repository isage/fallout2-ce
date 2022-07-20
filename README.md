# Fallout 2 Community Edition - PSVita port.

## Installation

You must own the game to play. Purchase your copy on [GOG](https://www.gog.com/game/fallout_2) or [Steam](https://store.steampowered.com/app/38410). Download latest release or build from source.

### PSVita
* Download and install fallout2-ce.vpk
* Copy master.dat, critter.dat, patch000.dat, data and sound folders from your PC game into `ux0:/data/fallout2/`
#### PSVita controls
![Controls](/os/psvita/sce_sys/manual/001.png)

### Windows

Download and copy `fallout2-ce.exe` to your `Fallout2` folder. It serves as a drop-in replacement for `fallout2.exe`.

### Linux

- Use Windows installation as a base - it contains data assets needed to play. Copy `Fallout2` folder somewhere, for example `/home/john/Desktop/Fallout2`.

- Download and copy `fallout2-ce` to this folder.

- Install [SDL2](https://libsdl.org/download-2.0.php):

```console
$ sudo apt install libsdl2-2.0-0
```

- Run `./fallout2-ce`.

### macOS

> **NOTE**: macOS 11 or higher is required. The app is not universal. It should run on Apple Silicon under Rosetta 2, but I haven't tried it.

- Use Windows installation as a base - it contains data assets needed to play. Copy `Fallout2` folder somewhere, for example `/Applications/Fallout2`.

- Download and copy `fallout2-ce.app` to this folder.

- Run `fallout2-ce.app`.

## Contributing

Integrating Sfall goodies is the top priority. Quality of life updates are OK too. Please no large scale refactorings at this time as we need to reconcile changes from Reference Edition, which will make this process slow and error-prone. In any case open up an issue with your suggestion or to notify other people that something is being worked on.

### Intergrating Sfall

There are literally hundreds if not thousands of fixes and features in sfall. I guess not all of them are needed in Community Edition, but for the sake of compatibility with big mods out there, let's integrate them all.

## Legal & License

See [Fallout 2 Reference Edition](https://github.com/alexbatalov/fallout2-re). Same conditions apply until the source code in this repository is changed significantly.
