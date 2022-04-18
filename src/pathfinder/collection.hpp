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
 *  Utility class for working with collections.
 */

#ifndef PATHFINDER_COLLECTION_HPP
#define PATHFINDER_COLLECTION_HPP

#include <algorithm>
#include <tuple>
#include <vector>

namespace Pathfinder {

class Collection {
public:
	template<typename T>
	static void sortByTitle(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getTitle() < b.getTitle();
		});
	}

	template<typename T>
	static void sortByDate(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getDate() < b.getDate();
		});
	}

	template<typename T>
	static void sortByAbbreviation(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getAbbreviation() < b.getAbbreviation();
		});
	}

	template<typename T>
	static void sortByCategory(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getCategory() < b.getCategory();
		});
	}

	template<typename T>
	static void sortByProductCode(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getProductCode() < b.getProductCode();
		});
	}

	template<typename T>
	static void sortByGermanName(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getGermanName() < b.getGermanName();
		});
	}

	template<typename T>
	static void sortByEnglishName(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getEnglishName() < b.getEnglishName();
		});
	}

	template<typename T>
	static void sortBySchool(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getSchool() < b.getSchool();
		});
	}

	template<typename T>
	static void sortByBook(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getBook() < b.getBook();
		});
	}

	template<typename T>
	static void sortByPage(std::vector<T> &collection) {
		std::stable_sort(collection.begin(), collection.end(), [](const T &a, const T &b) -> bool {
			return a.getPage() < b.getPage();
		});
	}

	template<typename T>
	static void sortByBookAndPage(std::vector<T> &collection) {
		sortByPage(collection);
		sortByBook(collection);
	}

	template<typename T>
	static void sortByClassLevel(std::vector<T> &collection, const std::string &className) {
		std::stable_sort(collection.begin(), collection.end(), [&className](const T &a, const T &b) -> bool {
			return a.getClassLevel(className) < b.getClassLevel(className);
		});
	}

	template<typename T>
	static std::tuple<std::vector<T>, std::vector<T>> partitionByBook(std::vector<T> &collection, const std::string &book) {
		auto it = std::stable_partition(collection.begin(), collection.end(), [&book](const T &a) { return a.getBook() == book; });

		return std::make_tuple(std::vector<T>(collection.begin(), it), std::vector<T>(it, collection.end()));
	}

};

} // End of namespace Pathfinder

#endif // PATHFINDER_COLLECTION_HPP
