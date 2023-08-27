#include "RandomIndex.hpp"
#include <iostream>

namespace {
[[maybe_unused]] void write() {

  RandomIndex idx;
  Record record1(1, "n", 1);
  Record record2(2, "n", 1);
  Record record3(3, "n", 1);
  idx.insert(record1);
  idx.insert(record2);
  idx.insert(record3);
}

[[maybe_unused]] void read() {

  RandomIndex idx;
  for (const auto &[key, record] : idx) {
    std::cout << key << " " << record << std::endl;
  }
}

[[maybe_unused]] void find() {

  RandomIndex idx;

  auto record = *idx.find(1);
  if (record.first == 1) {
    std::cout << "Found 1: " << record.second << std::endl;
  }
}

} // namespace

int main() {

  write();
  read();
  find();

  return 0;
}
