#include <cstdint>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

constexpr size_t MAX_NAME_LENGTH = 12;

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
};
#pragma pack(pop)

class AVLFile {
private:
  std::string m_filename;
  int64_t m_pos_root;

public:
  explicit AVLFile(string filename)
      : m_filename(std::move(filename)), m_pos_root(0) {}

  Record find(int key) { return find(m_pos_root, key); }

  void insert(Record record) { insert(m_pos_root, record); }

  vector<Record> inorder() { return inorder(m_pos_root); }

private:
  Record find(long pos_node, int key) {
    /*
    if (node == nullptr)
            return false;
    else if (value < node->data)
            return find(node->left, value);
    else if (value > node->data)
            return find(node->right, value);
    else
            return true;
    */
  }

  void insert(long pos_node, Record record) {
    /*
    if (node == nullptr)
            node = new NodeBT<T>(value);
    else if (value < node->data)
            insert(node->left, value);
    else
            insert(node->right, value);
    */
  }

  vector<Record> inorder(long pos_node) {
    /*
    if (node == nullptr)
            return;
    displayPreOrder(node->left);
    cout << node->data << endl;
    displayPreOrder(node->right);
    */
  }
};
