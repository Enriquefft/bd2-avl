#ifndef RANDOM_FILE_HPP
#define RANDOM_FILE_HPP

#include "RandomIndex.hpp"
#include <string>

constexpr std::string_view DEFAULT_DATA_FILE = "data.dat";

class RandomFile {

public:
  using data_type = Record;
  using key_type = data_type::key_type;

  explicit RandomFile(std::string_view data_file = DEFAULT_DATA_FILE);
  ~RandomFile() = default; // Index is written on RandomIndex destructor

  auto at(const key_type &key) -> data_type;
  auto insert(const data_type &data) -> bool;

private:
  std::string m_data_file;
  RandomIndex m_index;
};

#endif // !RANDOM_FILE_HPP
