#ifndef RECORD_HPP
#define RECORD_HPP

#include <cstddef>

constexpr size_t MAX_NAME_LENGTH = 12;

struct Record {

  using key_type = int;

  key_type cod;                 // 4
  char nombre[MAX_NAME_LENGTH]; // 12
  int ciclo;                    // 4
};
#endif // !RECORD_HPP
