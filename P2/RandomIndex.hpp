#ifndef RANDOM_INDEX_HPP
#define RANDOM_INDEX_HPP

#include <string>

constexpr std::string_view DEFAULT_INDEX_FILE = "index.dat";

class RandomIndex {
public:
  explicit RandomIndex(
      std::string_view index_file = DEFAULT_INDEX_FILE); // Read index
  ~RandomIndex();                                        // write index

private:
  std::string m_index_file;
};

#endif // !RANDOM_INDEX_HPP
