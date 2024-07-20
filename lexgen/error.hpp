#ifndef INCLUDE_ERROR_HPP_
#define INCLUDE_ERROR_HPP_

#include <iostream>

inline void error() { std::cout << '\n'; }

template <typename T, typename... Types>
void error(T const &t, Types const &...args) {
  std::cout << t << ' ';
  error(args...);
}

#endif // INCLUDE_ERROR_HPP_
