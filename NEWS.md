Changes in Decemvirate version 0.2.0
====================================

This version of Decemvirate comes with a new version of the sqlite3 database,
0.5.0, which adds a few more spells that were missing, and also adds class
information to each spell.

Additionally, the decemvirate itself can now show this spell class information
and acquired a new command: findspellbyclass. This new command lists all spells
accessible to a certain class, optionally only of a specific spell level.

Finally, the sorting of German-language data has been fixed, so that umlaut
characters now correctly follow the German dictionary order.


Changes in Decemvirate version 0.1.0
====================================

This is the first official release of Decemvirate.

Decemvirate is a free/libre and open source (FLOSS) helper program for the
Pathfinder tabletop roleplaying game, especially for German-language players.
Decemvirate contains a database with certain metadata about this game and
allows users to search through it. Currently, it can search and display
information about Pathfinder publications, spells and feats, both in the
German and English language, and translate their names between those two
languages.

While all English publications are stored in the database, not all have
been translated into German. Only spells and feats that have been translated
into German are currently within the database.

The following commands are available:
- `finddepub` and `findenpub`: search for German or English publication
- `finddespell` and `findenspell`: search for spell by German or English name
- `finddefeat` and `findenfeat`: search for feat by German or English name

See the README.md for details.
