#ifndef RECORD_HPP
#define RECORD_HPP

#include <algorithm>
#include <cstddef>
#include <ostream>
#include <string>

constexpr size_t MAX_NAME_LENGTH = 12;

#pragma pack(push, 1)
struct Record {

  using key_type = int;

  key_type cod{};                 // 4
  char nombre[MAX_NAME_LENGTH]{}; // 12
  int ciclo{};                    // 4

  Record() = default;
  Record(key_type _cod, std::string _nombre, int _ciclo)
      : cod(_cod), ciclo(_ciclo) {
    std::copy(_nombre.begin(), _nombre.end(), nombre);
  }

  friend std::ostream &operator<<(std::ostream &os, const Record &r) {
    os << r.cod << " " << r.nombre << " " << r.ciclo;
    return os;
  }
};
#pragma pack(pop)

#endif // !RECORD_HPP
