Decemvirate README
==================

Decemvirate is a free/libre and open source (FLOSS) helper program for the
Pathfinder tabletop roleplaying game, licensed under the terms of the
[GNU Affero General Public License version 3](https://www.gnu.org/licenses/agpl.html)
(or later).

This repository contains an SQLite3 database. For details on its contents, see
data/README.data. To easier manage that database inside a git repository, we're
using [git-sqlite](https://github.com/cannadayr/git-sqlite). Just checking out,
building and using Decemvirate does not require git-sqlite, but viewing commit
diffs and merging commits does. To continue viewing the database as an opaque
binary blob, remove the relevant line in .gitattributes.

[Decemvirate itself can be found on GitHub here.](https://github.com/DrMcCoy/decemvirate)

Usage
-----

```
Usage:
  decemvirate [OPTION...] <command> [<parameters>]

  -h, --help          Show this text and exit
      --version       Display version and exit
  -d, --database arg  SQLite database to use (required)

Supported commands:
  - finddepub <abbreviation/title>
    Search German publication by abbreviation or title
  - findenpub <code/abbreviation/title>
    Search English publication by product code, abbreviation or title
  - finddespell <name>
    Search German spells by name
  - findenspell <name>
    Search English spells by name
  - finddefeat <name>
    Search German feats by name
  - findenfeat <name>
    Search English feats by name
```

Examples:

- `decemvirate -d data/pathfinder.sqlite finddepub EXP`
- `decemvirate -d data/pathfinder.sqlite finddepub "abr II`
- `decemvirate -d data/pathfinder.sqlite finddepub grundregelwerk`
- `decemvirate -d data/pathfinder.sqlite finddepub drachen`
- `decemvirate -d data/pathfinder.sqlite findenpub PZO1110`
- `decemvirate -d data/pathfinder.sqlite findenpub CR`
- `decemvirate -d data/pathfinder.sqlite findenpub "Core Rule"`
- `decemvirate -d data/pathfinder.sqlite finddespell federfall`
- `decemvirate -d data/pathfinder.sqlite findenspell "feather fall"`
- `decemvirate -d data/pathfinder.sqlite finddefeat mehrfachschuss`
- `decemvirate -d data/pathfinder.sqlite finddefeat manyshot`
