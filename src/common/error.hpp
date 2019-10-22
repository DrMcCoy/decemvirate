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
 *  Basic exceptions to throw.
 */

#ifndef COMMON_ERROR_HPP
#define COMMON_ERROR_HPP

#include <exception>
#include <string>
#include <stack>

#include "external/fmt/core.hpp"

namespace Common {

/** Exception that provides a stack of explanations. */
class StackException : public std::exception {
public:
	using Stack = std::stack<std::string>;

	StackException() = default;
	template<typename... Args>
	StackException(const std::string &format, const Args & ... args) {
		vadd(format, fmt::make_format_args(args...));
	}
	StackException(const StackException &e) = default;
	StackException(const std::exception &e);
	~StackException()= default;

	template<typename... Args>
	void add(const std::string &format, const Args & ... args) {
		vadd(format, fmt::make_format_args(args...));
	}
	void add(const StackException &e);
	void add(const std::exception &e);

	const char *what() const noexcept;

	bool empty() const { return _stack.empty(); }

	Stack &getStack() noexcept { return _stack; }
	const Stack &getStack() const noexcept { return _stack; }

private:
	void vadd(const std::string &format, fmt::format_args args);

	Stack _stack;
};

using Exception = StackException;

extern const Exception kOpenError;  ///< Exception when a file couldn't be opened.
extern const Exception kReadError;  ///< Exception when reading from a stream failed.
extern const Exception kSeekError;  ///< Exception when seeking a stream failed.
extern const Exception kWriteError; ///< Exception when writing to a stream failed.

/** Print a whole exception stack to stderr and the log. */
void printException(Exception e, const std::string &prefix = "ERROR: ");
void printExceptionWarning(const Exception &e);

/** Exception dispatcher that prints the exception as an error, and adds another reason on top.
 *  This is intended for fatal errors. */
template<typename... Args> void exceptionDispatcherError(const std::string &format, const Args & ... args);
/** Exception dispatcher that prints the exception as an error.
 *  This is intended for fatal errors. */
void exceptionDispatcherError();

/** Exception dispatcher that prints the exception as a warning, and adds another reason on top.
 *  This is intended for non-fatal exceptions that can be ignored. */
template<typename... Args> void exceptionWarning(const std::string &format, const Args & ... args);
/** Exception dispatcher that prints the exception as a warning.
 *  This is intended for non-fatal exceptions that can be ignored. */
void exceptionDispatcherWarning();

void vexceptionDispatcherError(const std::string &format, fmt::format_args args);
template<typename... Args>
void exceptionDispatcherError(const std::string &format, const Args & ... args) {
	vexceptionDispatcherError(format, fmt::make_format_args(args...));
}

void vexceptionWarning(const std::string &format, fmt::format_args args);
template<typename... Args>
void exceptionWarning(const std::string &format, const Args & ... args) {
	vexceptionWarning(format, fmt::make_format_args(args...));
}

} // End of namespace Common

#endif // COMMON_ERROR_HPP
