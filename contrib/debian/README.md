
Debian
====================
This directory contains files used to package safeinsured/safeinsure-qt
for Debian-based Linux systems. If you compile safeinsured/safeinsure-qt yourself, there are some useful files here.

## safeinsure: URI support ##


safeinsure-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install safeinsure-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your safeinsureqt binary to `/usr/bin`
and the `../../share/pixmaps/safeinsure128.png` to `/usr/share/pixmaps`

safeinsure-qt.protocol (KDE)

