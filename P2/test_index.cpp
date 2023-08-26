#include "RandomIndex.hpp"
#include <iostream>

namespace {
[[maybe_unused]] void write() {

  RandomIndex idx;
  // Record record(1, "n", 1);
  Record record(2, "n", 1);
  Record record2(3, "n", 1);
  idx.insert(record);
  idx.insert(record2);
}

[[maybe_unused]] void read() {

  RandomIndex idx;
  for (const auto &[key, record] : idx) {
    std::cout << key << " " << record << std::endl;
  }
}

} // namespace

int main() {

  write();
  read();

  return 0;
}
