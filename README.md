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
