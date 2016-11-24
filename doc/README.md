Robbiecon Core 0.13.99
=====================

Setup
---------------------
Robbiecon Core is the original Robbiecon client and it builds the backbone of the network. However, it downloads and stores the entire history of Robbiecon transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download Robbiecon Core, visit [robbieconcore.org](https://robbieconcore.org/en/releases/).

Running
---------------------
The following are some helpful notes on how to run Robbiecon on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/robbiecon-qt` (GUI) or
- `bin/robbiecond` (headless)

### Windows

Unpack the files into a directory, and then run robbiecon-qt.exe.

### OS X

Drag Robbiecon-Core to your applications folder, and then run Robbiecon-Core.

### Need Help?

* See the documentation at the [Robbiecon Wiki](https://en.robbiecon.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#robbiecon](http://webchat.freenode.net?channels=robbiecon) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=robbiecon).
* Ask for help on the [RobbieconTalk](https://robbiecontalk.org/) forums, in the [Technical Support board](https://robbiecontalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build Robbiecon on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Robbiecon repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/robbiecon/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [RobbieconTalk](https://robbiecontalk.org/) forums, in the [Development & Technical Discussion board](https://robbiecontalk.org/index.php?board=6.0).
* Discuss project-specific development on #robbiecon-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=robbiecon-core-dev).
* Discuss general Robbiecon development on #robbiecon-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=robbiecon-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
