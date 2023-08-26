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

  struct RecordData {
    char nombre[MAX_NAME_LENGTH];
    int ciclo;
    friend std::ostream &operator<<(std::ostream &os, const RecordData &r) {
      os << r.nombre << " " << r.ciclo;
      return os;
    }
  };

  std::pair<key_type, RecordData> m_data;

  Record() = default;
  Record(key_type _cod, std::string _nombre, int _ciclo)
      : m_data{_cod, {"", _ciclo}} {
    std::copy(_nombre.begin(), _nombre.end(), m_data.second.nombre);
  }

  friend std::ostream &operator<<(std::ostream &os, const Record &r) {
    os << r.m_data.first << " " << r.m_data.second;
    return os;
  }

  // Cast operator
  operator std::pair<const key_type, RecordData>() const { return m_data; }
};
#pragma pack(pop)

#endif // !RECORD_HPP
