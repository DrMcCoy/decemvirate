Changes in Decemvirate version 0.6.0
====================================

This version of Decemvirate adds URLs to spells.

The GermanSpells table was extended with two new columns, EnglishURL and
GermanURL, which were populated with URLs to d20pfsrd.com, aonprd.com
and 5footstep.de. The CLI commands findenspell and finddespell now
display those URLs and the web service linkifies the spell names with
those URLs.

Additionally, a few spelling mistakes in the GermanSpells table were
fixed.


Changes in Decemvirate version 0.5.0
====================================

This version of Decemvirate adds URLs to feats.

The GermanFeats table was extended with two new columns, EnglishURL and
GermanURL, which were populated with URLs to d20pfsrd.com, aonprd.com
and 5footstep.de. The CLI commands findenfeat and finddefeat now
display those URLs and the web service linkifies the feat names with
those URLs.

Additionally, a few spelling mistakes in the GermanFeats table were
fixed.


Changes in Decemvirate version 0.4.0
====================================

This version of Decemvirate is a complete rewrite in Python.

The rewrite has full feature-parity with the old C++ application and
additionally comes with a full web services using Flask.

The usage has slightly changed. See the README.md for details.


Changes in Decemvirate version 0.3.2
====================================

This version of Decemvirate is a maintenance release, making Decemvirate
build again with GNU Make 4.4.

Otherwise, Decemvirate is unchanged. No new features have been added.


Changes in Decemvirate version 0.3.1
====================================

This version of Decemvirate is a maintenance release, updating dependencies and
code to make Decemvirate compile cleanly with gcc 12, which is more strict
when it comes to usages of deprecated and removed C++ features.

Otherwise, Decemvirate is unchanged. No new features have been added.


Changes in Decemvirate version 0.3.0
====================================

This version of Decemvirate comes with a new option to output all information
as JSON instead of plain text. No other changes have been done and the plain
text output *should* be identical as before.


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
