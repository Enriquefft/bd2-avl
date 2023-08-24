#ifndef AVL_FILE_HPP
#define AVL_FILE_HPP

#include <cstdint>
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
  int cod;
  char nombre[MAX_NAME_LENGTH];
  int ciclo;

  int64_t left;
  int64_t right;

  friend auto operator<<(ostream &stream, const Record &record)
      -> std::ostream & {

    stream << record.cod << " ";

    stream.write(static_cast<const char *>(record.nombre), MAX_NAME_LENGTH);

    stream << " " << record.ciclo;
    return stream;
  }
  void set_data() {
    cout << "Codigo:";
    cin >> cod;
    cout << "Nombre: ";
    cin >> nombre;
    cout << "Ciclo: ";
    cin >> ciclo;
  }

  static auto size_in_bytes() -> size_t {
    return sizeof(int) + MAX_NAME_LENGTH + sizeof(int) + sizeof(int64_t) +
           sizeof(int64_t) + 2;
  }
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Metadata {
  int64_t root_pos{0};
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
  int64_t m_pos_root{0};
  int64_t m_record_count{0};

  void open_or_create(const char *file_name);
  auto read_metadata() -> bool;
  void update_header(int64_t pos, int64_t size = 0);

public:
  explicit AVLFile(string filename) : m_filename(std::move(filename)) {

    if (m_filename.substr(m_filename.size() - 4) != ".txt") {
      throw std::invalid_argument("ERROR: El archivo debe ser .txt");
    }

    open_or_create(m_filename.data()); // Can throw
    if (!read_metadata()) {
      std::cerr << "ERROR: No se pudo leer la metadata, creando archivo\n";
      update_header(0);
    }
  }

  auto find(int key) -> Record { return find(m_pos_root, key); }

  void insert(Record record) { insert(m_pos_root, record); }

  auto inorder() -> vector<Record> { return inorder(m_pos_root); }

private:
  auto find(int64_t pos_node, int key) -> Record;
  void insert(int64_t pos_node, Record record);
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

  m_record_count = root_pos;

  std::ofstream metadata(METADATA_FILE.data(), std::ios::out);
  metadata << root_pos << ' ' << size << '\n';
  metadata.close();
}

#endif // !AVL_FILE_HPP
