#ifndef RANDOM_FILE_HPP
#define RANDOM_FILE_HPP

#include "RandomIndex.hpp"
#include <string>


class RandomFile {

public:
  using data_type = Record;
  using key_type = data_type::key_type;

  explicit RandomFile() = default;
  ~RandomFile() = default; // Index is written on RandomIndex destructor

  // Ana
  auto at(const key_type &key) -> data_type;
  // Renato
  auto insert(const data_type &data) -> bool;

private:
  RandomIndex m_index;
};

#endif // !RANDOM_FILE_HPP
