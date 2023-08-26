#ifndef RANDOM_INDEX_HPP
#define RANDOM_INDEX_HPP

#include "Record.hpp"
#include <iostream>
#include <string>
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
    std::cout << "Loading index from " << index_file << std::endl;
  }
  ~RandomIndex() {
    std::cout << "Saving index to " << m_index_file << std::endl;
  }

private:
  std::string m_index_file;
};

#endif // !RANDOM_INDEX_HPP
