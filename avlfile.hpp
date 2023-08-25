#ifndef AVL_FILE_HPP
#define AVL_FILE_HPP

#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

constexpr size_t MAX_NAME_LENGTH = 12;
constexpr string_view METADATA_FILE = "metadata.txt";

#pragma pack(push, 1)
struct Record {
  int cod;                      // 4
  char nombre[MAX_NAME_LENGTH]; // 12
  int ciclo;                    // 4

  int64_t left = -1;  // 8
  int64_t right = -1; // 8

  friend auto operator<<(ostream &stream, const Record &record)
      -> std::ostream & {
    stream << record.cod << ' ' << record.nombre << ' ' << record.ciclo << ' '
           << record.left << ' ' << record.right << '\n';
    return stream;
  }
  friend auto operator<<(fstream &stream, const Record &record)
      -> std::fstream & {
    stream << record.cod << ' ' << record.nombre << ' ' << record.ciclo << ' '
           << record.left << ' ' << record.right << '\n';
    return stream;
  }

  void set_data() {
    cout << "Codigo:";
    cin >> cod;
    strncpy(nombre, "nombre", 6);
    ciclo = 1;
  }

  friend auto operator>>(istream &stream, Record &record) -> std::istream & {
    stream.read(reinterpret_cast<char *>(&record), sizeof(record));
    return stream;
  }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Metadata {
  int64_t root_pos{-1};
  int64_t record_count{0};
  friend auto operator<<(ostream &stream, const Metadata &metadata)
      -> std::ostream & {
    stream << metadata.root_pos;
    stream << metadata.record_count;
    return stream;
  }
};
#pragma pack(pop)

class AVLFile {
private:
  std::string m_filename;
  std::fstream m_file_stream;
  int64_t m_pos_root{-1};
  int64_t m_record_count{0};

  enum class LR : char { LEFT = 'L', RIGHT = 'R' };

  void open_or_create(const char *file_name);
  auto read_metadata() -> bool;
  void update_header(int64_t pos, int64_t size);
  void update_parent(int64_t pos_parent, LR lr, int64_t pos_child);

public:
  explicit AVLFile(string filename) : m_filename(std::move(filename)) {

    auto file_end = m_filename.substr(m_filename.size() - 4);
    if (file_end != ".txt" && file_end != ".dat") {

      throw std::invalid_argument("ERROR: El archivo debe ser .txt");
    }

    open_or_create(m_filename.data()); // Can throw
    if (!read_metadata()) {
      std::cerr << "ERROR: No se pudo leer la metadata, creando archivo\n";
      update_header(-1, 0);
    }
  }

  auto find(int key) -> Record {
    if (m_pos_root == -1) {
      throw runtime_error("No hay datos en el arbol");
    }
    return find(m_pos_root, key);
  }

  auto insert(Record record) -> bool {

    int64_t inserted_pos = insert(m_pos_root, record);

    if (m_pos_root == -1) {
      m_pos_root = inserted_pos;
      update_header(m_pos_root, m_record_count);
    }
    return inserted_pos != -1;
  }

  auto inorder() -> vector<Record> { return inorder(m_pos_root); }
  auto load() -> vector<Record> {

    m_file_stream.open(m_filename.data(), std::ios::in | std::ios::binary);

    vector<Record> records;
    Record record;
    while (
        m_file_stream.read(reinterpret_cast<char *>(&record), sizeof(record))) {
      records.push_back(record);
    }

    return records;
  }

private:
  auto find(int64_t pos_node, int key) -> Record;
  auto insert(int64_t pos_node, Record record) -> int64_t;
  auto inorder(int64_t pos_node) -> vector<Record>;
};

inline void AVLFile::open_or_create(const char *file_name) {

  // If file doesn't exists create it
  if (!std::filesystem::exists(file_name) ||
      !std::filesystem::is_regular_file(file_name)) {
    std::clog << "Creating file\n";
    m_file_stream.open(file_name, std::ios::out);

    if (!m_file_stream.is_open()) {
      throw std::runtime_error("Couldn't create file");
    }

    m_file_stream.close();
  }

  // Try to open for read and write in binary mode
  m_file_stream.open(file_name,
                     std::ios::in | std::ios::out /* | std::ios::binary */);
  if (!m_file_stream.is_open()) {
    throw std::runtime_error("Couldn't open file");
  }
  m_file_stream.close();
}

inline auto AVLFile::read_metadata() -> bool {

  open_or_create(METADATA_FILE.data());

  std::ifstream metadata(
      METADATA_FILE.data(),
      std::ios::in); // Already has been checked that it exists

  // The record count must be readable
  if (!(metadata >> m_pos_root >> m_record_count)) {
    std::cerr << "ERROR: No se pudo leer la metadata\n";
    return false;
  }

  metadata.close();
  return true;
}

inline void AVLFile::update_header(int64_t root_pos, int64_t size) {

  m_record_count = size;

  std::ofstream metadata(METADATA_FILE.data(), std::ios::out);
  metadata << root_pos << ' ' << size << '\n';

  metadata.close();
}

inline void AVLFile::update_parent(int64_t pos_parent, LR lr,
                                   int64_t pos_child) {

  cout << "Updating parent\n";
  cout << "Pos parent: " << pos_parent << '\n';
  cout << "LR: " << static_cast<char>(lr) << '\n';
  cout << "Pos child: " << pos_child << '\n';
  //
  int64_t lr_pos = 0;
  // int cod;
  // char nombre[MAX_NAME_LENGTH];
  // int ciclo;
  //
  // int64_t left = -1;
  // int64_t right = -1;

  if (lr == LR::LEFT) {
    lr_pos = pos_parent + sizeof(int) + MAX_NAME_LENGTH + sizeof(int);
  } else {
    lr_pos = pos_parent + sizeof(int) + MAX_NAME_LENGTH + sizeof(int) +
             sizeof(int64_t);
  }

  cout << "LR pos: " << lr_pos << '\n';

  m_file_stream.open(m_filename.data(), std::ios::out | std::ios::binary);
  m_file_stream.seekp(lr_pos);

  // Bug:
  // This is not only overwriting the parent's left or right pointer
  // but also the entire record itself
  m_file_stream.write(reinterpret_cast<char *>(&pos_child), sizeof(int64_t));
  m_file_stream.close();
}

#endif // !AVL_FILE_HPP
