/* Decemvirate - A FLOSS Pathfinder TTRPG helper
 *
 * Decemvirate is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * Decemvirate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Decemvirate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with Decemvirate. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Pathfinder database.
 */

#ifndef PATHFINDER_DB_HPP
#define PATHFINDER_DB_HPP

#include <string>

#include "src/sqlite3/db.hpp"

#include "src/pathfinder/germanpublication.hpp"
#include "src/pathfinder/englishpublication.hpp"
#include "src/pathfinder/germanspell.hpp"
#include "src/pathfinder/germanfeat.hpp"

namespace Pathfinder {

class VersionDB {
public:
	VersionDB(const std::string &file, int64_t reqVersionMajor, int64_t minVersionMinor);
	VersionDB(const VersionDB &) = delete;
	VersionDB(VersionDB &&) = default;
	~VersionDB() = default;

	VersionDB &operator=(const VersionDB &) = delete;
	VersionDB &operator=(VersionDB &&) = default;

	std::string getFile() const { return _db.getFile(); }

	int64_t getVersionMajor() const noexcept { return _versionMajor; }
	int64_t getVersionMinor() const noexcept { return _versionMinor; }
	int64_t getVersionPatch() const noexcept { return _versionPatch; }

	std::string getVersionString() const noexcept {  return _versionString; }


protected:
	SQLite3::DB _db;

	int64_t _versionMajor, _versionMinor, _versionPatch;
	std::string _versionString;
};


class DB : public VersionDB {
public:
	DB(const std::string &file, int64_t minVersionMajor, int64_t minVersionMinor);
	DB(const DB &) = delete;
	DB(DB &&) = default;
	~DB() = default;

	DB &operator=(const DB &) = delete;
	DB &operator=(DB &&) = default;

	std::optional<GermanPublication> findGermanPublicationByAbbreviation(const std::string &abbreviation);

	std::optional<EnglishPublication> findEnglishPublicationByProductCode(const std::string &productCode);
	std::optional<EnglishPublication> findEnglishPublicationByAbbreviation(const std::string &abbreviation);

	std::vector<GermanPublication> findGermanPublicationsByTitle(const std::string &title);
	std::vector<GermanPublication> findGermanPublicationsByTitle(const std::string &title, size_t &count);

	std::vector<EnglishPublication> findEnglishPublicationsByTitle(const std::string &title);
	std::vector<EnglishPublication> findEnglishPublicationsByTitle(const std::string &title, size_t &count);

	std::vector<EnglishPublication> findOriginals(const GermanPublication &german);
	std::vector<GermanPublication> findTranslations(const EnglishPublication &english);

	std::vector<GermanSpell> findGermanSpellsByGermanName(const std::string &name);
	std::vector<GermanSpell> findGermanSpellsByEnglishName(const std::string &name);

	std::vector<GermanSpell> findGermanSpellsByClass(const std::string &name, int level);

	std::vector<GermanFeat> findGermanFeatsByGermanName(const std::string &name);
	std::vector<GermanFeat> findGermanFeatsByEnglishName(const std::string &name);


private:
	FindGermanPublicationByAbbreviation _findGermanPublicationByAbbreviation;

	FindEnglishPublicationByProductCode _findEnglishPublicationByProductCode;
	FindEnglishPublicationByAbbreviation _findEnglishPublicationByAbbreviation;

	FindGermanPublicationsByTitle _findGermanPublicationsByTitle;
	FindEnglishPublicationsByTitle _findEnglishPublicationsByTitle;

	FindGermanPublicationsByPaizoCode _findGermanPublicationsByPaizoCode;

	FindGermanSpellsByGermanName _findGermanSpellsByGermanName;
	FindGermanSpellsByEnglishName _findGermanSpellsByEnglishName;

	FindGermanSpellsByClass _findGermanSpellsByClass;

	FindGermanFeatsByGermanName _findGermanFeatsByGermanName;
	FindGermanFeatsByEnglishName _findGermanFeatsByEnglishName;
};

} // End of namespace Pathfinder

#endif // PATHFINDER_DB_HPP
