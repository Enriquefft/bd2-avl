#ifndef RANDOM_INDEX_HPP
#define RANDOM_INDEX_HPP

#include "Record.hpp"
#include <string>
#include <unordered_map>

constexpr std::string_view DEFAULT_INDEX_FILE = "index.dat";

class RandomIndex : std::unordered_map<Record::key_type, Record> {
public:
  explicit RandomIndex(
      std::string_view index_file = DEFAULT_INDEX_FILE); // Read index
  ~RandomIndex();                                        // write index

private:
  std::string m_index_file;
};

#endif // !RANDOM_INDEX_HPP
