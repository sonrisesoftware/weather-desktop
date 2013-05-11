How to Contribute
=================

Bugs
----

Found a bug? I'd love to fix, but first you need to report it. You can do this
by going to <https://github.com/iBeliever/weather-desktop/issues> and creating
an issue. I'll try to get to it as soon as I can, but first, please make sure
the you explain the issue well, ensure that it is reproducible in a consist
manner, and describe how to reproduce it.

Code
----

### Code Checking ###

Automated code checking is very important as it helps to catch subtle
errors in code. KDE (and thus Weather Desktop) uses an excellent code checker
called `krazy2`.

To run `krazy2` on Weather Desktop, first remove the build directory (this will
prevent `krazy2` from reporting errors in auto-generated code), and then run
this in the top-level directory of Weather Desktop:

    $ krazy2all > code_report
    
Then study the report it generates and fix any errors in your code.

UI Design
---------

### Backgrounds ###

Got a great weather-related background you'd like to allow the app to use?
If you would like this and are willing to license it under the GPLv3 or higher,
please create an issue as described under the Bugs section and attach your
picture. Make sure you explicitly say that you allow it to be licensed under
the GPLv3 or higher so I know that you know that and so I have proof.

Translations
------------

Since I only speak English, it would be awesome to have help translating the
application into other languages. However, I haven't had time to figure out how
to set up the translations system. I've made the app ready for translations, I
just don't know how to actually make and use them yet.
