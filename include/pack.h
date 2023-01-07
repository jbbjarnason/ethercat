#ifndef ETHERCAT_PACK_H
#define ETHERCAT_PACK_H

#pragma once

#include <cstddef>
#include <type_traits>
#include <vector>
#include <utility>

namespace ec {

template<typename T, std::size_t... Is>
constexpr std::vector<std::byte> pack_struct_impl(const T &s, std::index_sequence<Is...>) {
  return {std::byte{reinterpret_cast<const std::byte *>(&s)[Is]}...};
}

template<typename T>
constexpr std::vector <std::byte> pack_struct(const T &s) {
  return pack_struct_impl(s, std::make_index_sequence < sizeof(T) > {});
}

}

#endif //ETHERCAT_PACK_H
