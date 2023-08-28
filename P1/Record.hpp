#ifndef RECORD_HPP
#define RECORD_HPP

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>

constexpr size_t MAX_NAME_LENGTH = 12;

#pragma pack(push, 1)
struct Record {
  int cod{};                      // 4
  char nombre[MAX_NAME_LENGTH]{}; // 12
  int ciclo{};                    // 4

  int64_t left = -1;  // 8
  int64_t right = -1; // 8

  Record() = default;

  Record(int _cod, int _cicle, std::string nombre) : cod(_cod), ciclo(_cicle) {
    std::copy(nombre.begin(), nombre.end(), this->nombre);
  }

  // cout stream operator
  friend auto operator<<(std::ostream &stream, const Record &record)
      -> std::ostream & {
    stream << record.cod << ' ' << record.nombre << ' ' << record.ciclo << ' '
           << record.left << ' ' << record.right;
    return stream;
  }

  // File stream operators
  friend auto operator<<(std::fstream &stream, const Record &record)
      -> std::fstream & {
    stream.write(reinterpret_cast<const char *>(&record), sizeof(record));
    return stream;
  }
  friend auto operator<<(std::ofstream &stream, const Record &record)
      -> std::ofstream & {
    stream.write(reinterpret_cast<const char *>(&record), sizeof(record));
    return stream;
  }

  static constexpr int64_t LEFT_OFFSET =
      sizeof(cod) + sizeof(nombre) + sizeof(ciclo);
  static constexpr int64_t RIGHT_OFFSET = LEFT_OFFSET + sizeof(left);

  void read_data() {
    std::cout << "Codigo: \t";
    std::cin >> cod;
    std::cout << "Nombre: \t";
    std::cin >> nombre;
    std::cout << "Ciclo: \t";
    std::cin >> ciclo;
  }

  friend auto operator>>(std::istream &stream, Record &record)
      -> std::istream & {
    stream.read(reinterpret_cast<char *>(&record), sizeof(record));
    return stream;
  }
};
#pragma pack(pop)

#endif // !#ifndef RECORD_HPP
