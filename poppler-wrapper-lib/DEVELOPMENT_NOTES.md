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

### Hunting for symbols

Use `nm` to check for defined symbols
`-C` will unmangle the symbol name

```bash
nm -C libpoppler.a | grep PORT_Free
```

### Building a static lib for poppler

This is going to be tough. With a static library, you're going to need a static lib
version of all the libs used by poppler.

After fighting with this for a while, I gave up on this.
