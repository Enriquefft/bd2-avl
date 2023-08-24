#include "avlfile.hpp"
#include <utility>
#include <vector>

using namespace std;

namespace {

void write_file(string filename) {
  AVLFile file(std::move(filename));
  Record record{};
  for (int i = 0; i < 4; i++) {
    record.set_data();
    file.insert(record);
  }
}

void read_file(string filename) {
  AVLFile file(std::move(filename));
  cout << "--------- show all sorted data -----------\n";
  vector<Record> result = file.inorder();
  for (Record record : result) {
    cout << record;
  }
}

} // namespace

int main() {
  write_file("data.dat");
  read_file("data.dat");
  return 0;
}
