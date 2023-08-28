#include "avlfile.hpp"
#include <utility>
#include <vector>

using namespace FILESYSTEM;

namespace {

void print_records(std::string filename) {
  AVLFile file(std::move(filename));
  auto records = file.load();
  for (auto record : records) {
    std::cout << record << '\n';
  }
}

void write_file(std::string filename) {
  AVLFile file(std::move(filename));

  std::vector<Record> records;

  Record record3(3, 3, "3");
  Record record7(7, 4, "4");
  Record record4(4, 4, "4");
  Record record2(2, 2, "2");
  Record record1(1, 1, "1");
  Record record6(6, 4, "4");
  Record record5(5, 4, "4");

  records.push_back(record3);
  records.push_back(record7);
  records.push_back(record4);
  records.push_back(record2);
  records.push_back(record1);
  records.push_back(record6);
  records.push_back(record5);

  for (const auto &rec : records) {
    file.insert(rec);
  }

} // namespace

[[maybe_unused]] void find_record(std::string filename) {

  AVLFile file(std::move(filename));
  int cod = 0;
  std::cin >> cod;
  auto record = file.find(cod);

  std::cout << record;
}

void read_file(std::string filename) {
  AVLFile file(std::move(filename));
  std::cout << "--------- show all sorted data -----------\n";
  std::vector<Record> result = file.inorder();
  for (const Record &record : result) {
    std::cout << record << '\n';
  }
}

} // namespace

int main() {
  write_file("data.dat");
  print_records("data.dat");
  // find_record("data.dat");

  read_file("data.dat");
  return 0;
}
