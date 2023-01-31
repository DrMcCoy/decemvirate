Decemvirate README
==================

Decemvirate is a free/libre and open source (FLOSS) helper program for the
Pathfinder tabletop roleplaying game, licensed under the terms of the
[GNU Affero General Public License version 3](https://www.gnu.org/licenses/agpl.html)
(or later), written in Python.

This repository contains an SQLite3 database. For details on its contents, see
data/README.data. To easier manage that database inside a git repository, we're
using [git-sqlite](https://github.com/cannadayr/git-sqlite). Just checking out,
building and using Decemvirate does not require git-sqlite, but viewing commit
diffs and merging commits does. To continue viewing the database as an opaque
binary blob, remove the relevant line in .gitattributes.

[Decemvirate itself can be found on GitHub here.](https://github.com/DrMcCoy/decemvirate)


What does Decemvirate do?
-------------------------

Decemvirate's main use is to translate Pathfinder 1e terminology between
English and German. Specifically, it can search and translate

- feat names
- spell names
- publication (book) names

You can search either the English or the German name of one of these and it
will tell you the translated counterpart.

Additionally, Decemvirate contains various metadata associated with each of
these concepts. For example, for a publication, it also shows the ISBN. For a
feat, it shows a short description. For a spell, it know which classes have that
spell in their spell book. It also knows in which book the feat or spell can be
found, and displays URLs to various additional resources on the internet.

Decemvirate can run both as a command line program and as a web application.

In the former case, single Pathfinder database queries are issued and the
results printed to stdout. In the latter case, a whole web service runs
continuously to allow for easy database querying over a period of time.

Why?
----

Decemvirate was born out of the COVID pandemic, when all my games moved to
online play via FoundryVTT.

We're playing in German, but unfortunately, not all feats and spells in the
Pathfinder 1e system in FoundryVT have been translated to German. Additionally,
sometimes we wanted to look up a complete description of a spell or a feat, and
also see how it was phrased in the original (as opposed to the German
translation). And sometimes I was GM'ing a module that was never translated into
German to begin with, so had to do the translation work myself.

Installation
------------

To install Decemvirate system-wide, use
```
pip install .
```

To install Decemvirate for current user only, use
```
pip install --user .
```

To install Decemvirate in a virtualenv, use
```
pip -m venv env
source env/bin/activate
pip install .
```

Optionally, the included Makefile can be leveraged to install and run
Decemvirate from a virtualenv. Please read the Makefile itself to understand
what it can do.

One example of using the Makefile:

```
PYTHON=python3 make arg="-d data/pathfinder.sqlite web -l :: -p 31000"
```

This would install Decemvirate into a virtualenv and run it as a webserver,
using "python3" the Python environment.


Command line usage
------------------

```
usage: decemvirate [-h] [-v] -d DATABASE
                   {web,finddepub,findenpub,finddespell,findenspell,findspellbyclass,finddefeat,findenfeat}
                   ...

decemvirate -- A FLOSS Pathfinder TTRPG helper

options:
  -h, --help            show this help message and exit
  -v, --version         print the version and exit
  -d DATABASE, --database DATABASE
                        SQLite database to use (required)

Supported commands:
  {web,finddepub,findenpub,finddespell,findenspell,findspellbyclass,finddefeat,findenfeat}
    web                 Run the Decemvirate web application (default)
    finddepub           Search German publication by abbreviation or title
    findenpub           Search English publication by product code,
                        abbreviation or title
    finddespell         Search German spells by name
    findenspell         Search English spells by name
    findspellbyclass    Search spells by class (and level)
    finddefeat          Search German feats by name
    findenfeat          Search English feats by name


Command web:
usage: decemvirate web [-h] [-l HOST] [-p PORT] [-t THREADS]

options:
  -h, --help            show this help message and exit
  -l HOST, --host HOST  hostname or IP address on which to listen (default:
                        127.0.0.0)
  -p PORT, --port PORT  TCP port on which to listen (default: 8080)
  -t THREADS, --threads THREADS
                        the number of threads used to process application
                        logic (default: 4)

Command finddepub:
usage: decemvirate finddepub [-h] abbreviation/title

positional arguments:
  abbreviation/title  abbreviation or title to search for

options:
  -h, --help          show this help message and exit

Command findenpub:
usage: decemvirate findenpub [-h] code/abbreviation/title

positional arguments:
  code/abbreviation/title
                        product code, abbreviation or title to search for

options:
  -h, --help            show this help message and exit

Command finddespell:
usage: decemvirate finddespell [-h] name

positional arguments:
  name        spell to search for

options:
  -h, --help  show this help message and exit

Command findenspell:
usage: decemvirate findenspell [-h] name

positional arguments:
  name        spell to search for

options:
  -h, --help  show this help message and exit

Command findspellbyclass:
usage: decemvirate findspellbyclass [-h] class [level]

positional arguments:
  class       class name to search for
  level       class level search for

options:
  -h, --help  show this help message and exit

Command finddefeat:
usage: decemvirate finddefeat [-h] name

positional arguments:
  name        feat to search for

options:
  -h, --help  show this help message and exit

Command findenfeat:
usage: decemvirate findenfeat [-h] name

positional arguments:
  name        feat to search for

options:
  -h, --help  show this help message and exit

```

Command line examples
---------------------

- `decemvirate -d data/pathfinder.sqlite web`
- `decemvirate -d data/pathfinder.sqlite finddepub EXP`
- `decemvirate -d data/pathfinder.sqlite finddepub "abr II"`
- `decemvirate -d data/pathfinder.sqlite finddepub grundregelwerk`
- `decemvirate -d data/pathfinder.sqlite finddepub drachen`
- `decemvirate -d data/pathfinder.sqlite findenpub PZO1110`
- `decemvirate -d data/pathfinder.sqlite findenpub CR`
- `decemvirate -d data/pathfinder.sqlite findenpub "Core Rule"`
- `decemvirate -d data/pathfinder.sqlite finddespell federfall`
- `decemvirate -d data/pathfinder.sqlite findenspell "feather fall"`
- `decemvirate -d data/pathfinder.sqlite finddefeat mehrfachschuss`
- `decemvirate -d data/pathfinder.sqlite finddefeat manyshot`
- `decemvirate -d data/pathfinder.sqlite findspellbyclass Hexenmeister`
- `decemvirate -d data/pathfinder.sqlite findspellbyclass Jäger 2`

Web server usage
----------------

When running Decemvirate as a webserver using, for example

```
decemvirate -d data/pathfinder.sqlite web -p 31000
```

and then opening http://localhost:31000/ with a web browser, Decemvirate can be
used to continuously query the database.

This is how it'll look:

![Screenshot of a web page showing Decemvirate. On the top, radio buttons can be
set to select which operation (for example, searching for feat by German name)
is used, and below that, a text field allows the search query to be entered. In
the middle, the results would show, currently empty. At the bottom, the current
Decemvirate version is displayed.](images/webserver_example_01.png)

You can then, for example, click "Deutsches Talent" to search for a German feat
and then enter "abhä", and it will list all matching feats with their metadata.

![Similar screenshot like above, but now the results of the described query are
shown: three feats are listed in shadowed boxes in the middle of the page. Each
contain a small description, name of the book and page where it is found and
links to several websites with more in-depth description of the
feat.](images/webserver_example_02.png)

The "5footstep", "d20pfsrd" and "aonprd" links are clickable and lead to the
respective SRDs on the internet, directly to the pages of each feat.

When clicking on one of the book links, for example "ABR V", it will lead
to a different Decemvirate query for that book.

![The website now shows the results of the query for the book "ABR V". There
is one result shown in the middle of the page, with further information on that
book.](images/webserver_example_03.png)

As can be seen, Decemvirate can thus be used to easily search for several key
concepts of the Pathfinder 1e system and receive information about them in both
English and German.

Web server example files
------------------------

The examples/ directory contains example configuration files to run Decemvirate
continuously as a web service on a dedicated server. See the README.md in the
examples/ directory for details.
