#include "avlfile.hpp"
#include <utility>
#include <vector>

using namespace std;

namespace {

void print_records(string filename) {
  AVLFile file(std::move(filename));
  auto records = file.load();
  for (auto record : records) {
    cout << record;
  }
}

void write_file(string filename) {
  AVLFile file(std::move(filename));
  Record record{};
  // for (int i = 0; i < 4; i++) {
  record.set_data();
  file.insert(record);
  // record.set_data();
  // file.insert(record);
  // }
}

[[maybe_unused]] void find_record(string filename) {

  AVLFile file(std::move(filename));
  int cod = 0;
  std::cin >> cod;
  auto record = file.find(cod);

  std::cout << record;
}

// void read_file(string filename) {
//   AVLFile file(std::move(filename));
//   cout << "--------- show all sorted data -----------\n";
//   vector<Record> result = file.inorder();
//   for (Record record : result) {
//     cout << record;
//   }
// }

} // namespace

int main() {
  write_file("data.dat");
  print_records("data.dat");

  // find_record("data.dat");

  // read_file("data.dat");
  return 0;
}
