#include "RandomFile.hpp"
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

void test_insert(RandomFile& rf) {
    Record record(5, "a", 9);
    Record record2(6, "b", 10);

    rf.insert(record);
    rf.insert(record2);
}

void test_at(RandomFile& rf) {
    std::cout << rf.at(5) << std::endl;
    std::cout << rf.at(6) << std::endl;
}

int main() {

  write();
  read();

  RandomFile rf;

  test_insert(rf);
  test_at(rf);

  return 0;
}
