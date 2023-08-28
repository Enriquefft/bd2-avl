#ifndef AVL_FILE_HPP
#define AVL_FILE_HPP

#include "Record.hpp"
#include <filesystem>
#include <vector>

namespace FILESYSTEM {

constexpr std::string_view METADATA_FILE = "metadata.txt";
constexpr int64_t DEFAULT_ROOT_POS = -1;

#pragma pack(push, 1)
struct Metadata {
  int64_t root_pos{DEFAULT_ROOT_POS};
  int64_t record_count{0};
  friend auto operator<<(std::ostream &stream, const Metadata &metadata)
      -> std::ostream & {
    stream.write(reinterpret_cast<const char *>(&metadata), sizeof(metadata));
    return stream;
  }
};
#pragma pack(pop)

class AVLFile {
private:
  std::string m_filename;
  std::fstream m_file_stream;
  int64_t m_pos_root{DEFAULT_ROOT_POS};
  int64_t m_record_count{0};

  enum class LR : char { LEFT = 'L', RIGHT = 'R' };

  void open_or_create(const char *file_name);
  auto read_metadata() -> bool;
  void update_header(int64_t pos, int64_t size);
  void update_parent(int64_t pos_parent, LR lr, int64_t pos_child);

public:
  explicit AVLFile(std::string filename) : m_filename(std::move(filename)) {

    auto file_end = m_filename.substr(m_filename.size() - 4);
    if (file_end != ".txt" && file_end != ".dat") {

      throw std::invalid_argument("ERROR: El archivo debe ser .txt");
    }

    open_or_create(m_filename.data()); // Can throw
    if (!read_metadata()) {
      std::cerr << "ERROR: No se pudo leer la metadata, creando archivo\n";
      update_header(DEFAULT_ROOT_POS, 0);
    }
  }

  auto find(int key) -> Record {
    if (m_pos_root == DEFAULT_ROOT_POS) {
      throw std::runtime_error("No hay datos en el arbol");
    }
    return find(m_pos_root, key);
  }

  auto insert(Record record) -> bool {

    int64_t inserted_pos = insert(m_pos_root, record);

    if (m_pos_root == DEFAULT_ROOT_POS) {
      m_pos_root = inserted_pos;
      update_header(m_pos_root, m_record_count);
    }
    return inserted_pos != DEFAULT_ROOT_POS;
  }

  auto inorder() -> std::vector<Record> { return inorder(m_pos_root); }
  auto load() -> std::vector<Record> {

    m_file_stream.open(m_filename.data(), std::ios::in | std::ios::binary);

    std::vector<Record> records;
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
  auto inorder(int64_t pos_node) -> std::vector<Record>;
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
  Metadata header_data;

  // The record count must be readable
  if (!(metadata.read(reinterpret_cast<char *>(&header_data),
                      sizeof(header_data)))) {
    std::cerr << "ERROR: No se pudo leer la metadata\n";
    return false;
  }

  m_record_count = header_data.record_count;
  m_pos_root = header_data.root_pos;

  metadata.close();
  return true;
}

inline void AVLFile::update_header(int64_t root_pos, int64_t size) {

  m_record_count = size;

  Metadata header_data{root_pos, size};

  std::ofstream metadata(METADATA_FILE.data(), std::ios::out);

  metadata << header_data;

  metadata.close();
}

inline void AVLFile::update_parent(int64_t pos_parent, LR lr,
                                   int64_t pos_child) {

  int64_t lr_pos = lr == LR::LEFT ? Record::LEFT_OFFSET : Record::RIGHT_OFFSET;
  lr_pos += pos_parent;

  // std::cout << "Updating parent\n";
  //
  // std::cout << "Parent pos: " << pos_parent << '\n';
  // std::cout << "Child pos: " << pos_child << '\n';
  // std::cout << "LR pos: " << lr_pos << '\n';

  m_file_stream.open(m_filename.data(),
                     std::ios::in | std::ios::out | std::ios::binary);
  m_file_stream.seekp(lr_pos);

  m_file_stream.write(reinterpret_cast<char *>(&pos_child), sizeof(int64_t));
  m_file_stream.close();
}

} // namespace FILESYSTEM

#endif // !AVL_FILE_HPP
