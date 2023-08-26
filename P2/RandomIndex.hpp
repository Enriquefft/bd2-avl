#ifndef RANDOM_INDEX_HPP
#define RANDOM_INDEX_HPP

#include "Record.hpp"
#include <fstream>
#include <unordered_map>

constexpr std::string_view DEFAULT_INDEX_FILE = "index.dat";

class RandomIndex : public std::unordered_map<Record::key_type, Record> {
  using base_class = std::unordered_map<Record::key_type, Record>;

public:
  // Inherit constructors
  using base_class::unordered_map;
  using base_class::operator=;

  explicit RandomIndex(std::string_view index_file = DEFAULT_INDEX_FILE)
      : m_index_file(index_file) {

    std::ifstream index(m_index_file, std::ios::binary);

    Record::key_type key = 0;
    Record value;

    while (index.peek() != EOF) {
      index.read(reinterpret_cast<char *>(&key), sizeof(key));
      index.read(reinterpret_cast<char *>(&value), sizeof(value));

      if (index.fail()) {
        throw std::runtime_error("Failed to read index file");
      }
      emplace(key, value);
    }
  }
  ~RandomIndex() {
    std::ofstream index(m_index_file, std::ios::binary);
    for (const auto &[key, value] : *this) {
      index.write(reinterpret_cast<const char *>(&key), sizeof(key));
      index.write(reinterpret_cast<const char *>(&value), sizeof(value));
    }
  }

private:
  std::string m_index_file;
};

#endif // !RANDOM_INDEX_HPP
