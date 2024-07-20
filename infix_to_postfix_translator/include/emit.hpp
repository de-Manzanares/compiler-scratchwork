#ifndef INCLUDE_EMIT_HPP_
#define INCLUDE_EMIT_HPP_

#include <iostream>

inline void emit() {}

template <typename T, typename... Types>
void emit(T const &t, Types const &...args) {
  std::cout << t << ' ';
  emit(args...);
}

#endif // INCLUDE_EMIT_HPP_
