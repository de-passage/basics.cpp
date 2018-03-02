#ifndef GUARD_DETAILS_HASH_HPP__
#define GUARD_DETAILS_HASH_HPP__

#include <type_traits>
#include <string>

namespace details {
	// Is true_type if T is the same type as one of the types in the Args list
	template<class T, class...Args> struct is_one_of;
	template<class T, class ...Args> struct is_one_of<T, T, Args...> : std::true_type {};
	template<class T, class U, class ...Args> struct is_one_of<T, U, Args...> : is_one_of<T, Args...> {};
	template<class T> struct is_one_of<T> : std::false_type {};

	// Remove pointer and const qualification
	template<class T> struct decay { typedef T value; };
	template<class T> struct decay<const T*> { typedef T value; };
	template<class T> struct decay<T*> { typedef T value; };
	template<class T>
		using decay_t = typename decay<T>::value;
}

template<class T, class = void>
struct hash;

template<class T>
struct hash<T, std::enable_if_t<std::is_integral<T>::value>> {
	std::size_t operator()(const T& t) { return t; }
};

template<class T>
struct hash<T, std::enable_if_t<details::is_one_of<details::decay_t<std::decay_t<T>>, char, wchar_t>::value>> {
	std::size_t operator()(const T p) {
		// Forward to hash<string> for simplicity but in production code separating that specialization in a different
		// file would allow for more granular dependency management, since std::string is not necessary to every program using hash tables
		return hash<std::basic_string<details::decay_t<T>>>()(std::basic_string<details::decay_t<T>>(p));
	}
};

template<class T>
struct hash<T, std::enable_if_t<details::is_one_of<std::decay_t<T>, std::string, std::wstring>::value>> {
	std::size_t operator()(const T& t) { 
		// djb2 by Dan Berstein
		std::size_t hash = 5381;

		for(auto c = t.begin(); c != t.end(); ++c)
			hash = ((hash << 5) + hash) + *c;

		return hash;
	}
};

#endif
