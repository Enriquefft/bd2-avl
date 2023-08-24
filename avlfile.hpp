#ifndef AVL_FILE_HPP
#define AVL_FILE_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

constexpr size_t MAX_NAME_LENGTH = 12;
constexpr string_view HEADER_FILE = "metadata.txt";

#pragma pack(push, 1)
struct Record {
  int cod;
  char nombre[MAX_NAME_LENGTH];
  int ciclo;

  int64_t left;
  int64_t right;

  friend std::ostream &operator<<(ostream &stream, const Record &record) {

    stream << record.cod << " ";

    stream.write(static_cast<const char *>(record.nombre), MAX_NAME_LENGTH);

    stream << " " << record.ciclo;
    return stream;
  }

  static auto size_in_bytes() -> size_t {
    return sizeof(int) + MAX_NAME_LENGTH + sizeof(int);
    +sizeof(int64_t) + sizeof(int64_t) + 2;
  }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Metadata {
  size_t root_pos{0};
  friend std::ostream &operator<<(ostream &stream, const Metadata &metadata) {
    stream << metadata.root_pos;
    return stream;
  }
};
#pragma pack(pop)

class AVLFile {
private:
  std::string m_filename;
  int64_t m_pos_root{0};

  void update_header(int64_t pos);
  void open_or_create(const char *file_name);

public:
  explicit AVLFile(string filename) : m_filename(std::move(filename)) {

    if (m_filename.substr(m_filename.size() - 4) != ".txt") {
      throw std::invalid_argument("ERROR: El archivo debe ser .txt");
    }

    open_or_create(m_filename.data()); // Can throw
  }

  Record find(int key) { return find(m_pos_root, key); }

  void insert(Record record) { insert(m_pos_root, record); }

  vector<Record> inorder() { return inorder(m_pos_root); }

private:
  Record find(long pos_node, int key);
  void insert(long pos_node, Record record);
  vector<Record> inorder(long pos_node);
};
#endif // !AVL_FILE_HPP
