
Debian
====================
This directory contains files used to package robbiecond/robbiecon-qt
for Debian-based Linux systems. If you compile robbiecond/robbiecon-qt yourself, there are some useful files here.

## robbiecon: URI support ##


robbiecon-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install robbiecon-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your robbiecon-qt binary to `/usr/bin`
and the `../../share/pixmaps/robbiecon128.png` to `/usr/share/pixmaps`

robbiecon-qt.protocol (KDE)

