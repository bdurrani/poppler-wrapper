# Development Notes

### Building with the latest release

I ran into some issues with the version of poppler that is installed by
default on the current systems (0.86.1).
Specifically, the C++ library was remove consecutive line breaks. `pdftotext` did not
have this issue for some reason.
I verified using the test utilities that are build as part of the C++ libraries that
the issue does not exist in the latest release.
This means in order for this to work, I would need to link with the latest released versions
of poppler.

### Using Ninja

Poppler uses Ninja, so if I want to build against it, I need to use it as well.
It errors out with anything else.
