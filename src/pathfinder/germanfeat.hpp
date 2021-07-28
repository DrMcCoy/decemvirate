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
 *  German Pathfinder feats.
 */

#ifndef PATHFINDER_GERMANFEAT_HPP
#define PATHFINDER_GERMANFEAT_HPP

#include <string>
#include <vector>
#include <optional>

#include "src/sqlite3/findlikematch.hpp"

namespace Pathfinder {

/** A German Pathfinder feat. */
class GermanFeat {
public:
	/** Read a German English Pathfinder feat from a database query result. */
	GermanFeat(const SQLite3::MapStatement::Row &row);

	/** Return the German name of the feat. */
	std::string getGermanName() const { return _germanName; }

	/** Return the English name of the feat. */
	std::string getEnglishName() const { return _englishName; }

	/** Return the German book abbreviation the feat is found in. */
	std::string getBook() const { return _book; }

	/** Return the page of the book the feat is found in. */
	std::string getPage() const { return _page; }

	/** Return the German short description of the feat. */
	std::string getDescription() const { return _description; }

	/** Return the types this feat falls in. */
	std::vector<std::string> getTypes() const { return _types; }


private:
	std::string _germanName;
	std::string _englishName;
	std::string _book;
	std::string _page;
	std::string _description;

	std::vector<std::string> _types;
};


/** Find German feat by German name. */
class FindGermanFeatsByGermanName : public SQLite3::FindLikeMatch {
public:
	FindGermanFeatsByGermanName(SQLite3::DB &db, size_t limit = SQLite3::FindLikeMatch::kNoLimit);
	FindGermanFeatsByGermanName(const FindGermanFeatsByGermanName &) = delete;
	FindGermanFeatsByGermanName(FindGermanFeatsByGermanName &&) = default;
	~FindGermanFeatsByGermanName() override = default;

	FindGermanFeatsByGermanName &operator=(const FindGermanFeatsByGermanName &) = delete;
	FindGermanFeatsByGermanName &operator=(FindGermanFeatsByGermanName &&) = default;

	std::vector<GermanFeat> run(const std::string &name);
	std::vector<GermanFeat> run(const std::string &name, size_t &count);
};


/** Find German feat by English name. */
class FindGermanFeatsByEnglishName : public SQLite3::FindLikeMatch {
public:
	FindGermanFeatsByEnglishName(SQLite3::DB &db, size_t limit = SQLite3::FindLikeMatch::kNoLimit);
	FindGermanFeatsByEnglishName(const FindGermanFeatsByEnglishName &) = delete;
	FindGermanFeatsByEnglishName(FindGermanFeatsByEnglishName &&) = default;
	~FindGermanFeatsByEnglishName() override = default;

	FindGermanFeatsByEnglishName &operator=(const FindGermanFeatsByEnglishName &) = delete;
	FindGermanFeatsByEnglishName &operator=(FindGermanFeatsByEnglishName &&) = default;

	std::vector<GermanFeat> run(const std::string &name);
	std::vector<GermanFeat> run(const std::string &name, size_t &count);
};

} // End of namespace Pathfinder

#endif // PATHFINDER_GERMANFEAT_HPP
