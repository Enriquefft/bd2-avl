#include "avlfile.hpp"

Record AVLFile::find(int64_t pos_node, int key) {
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
  ifstream file(this->m_filename, ios::binary);
  file.seekg(pos_node); // Vamos a la posición del nodo
  // Leemos el record
  Record tmp;
  file >> tmp;

  return Record();
}

void AVLFile::insert(int64_t pos_node, Record record) {
  /*
  if (node == nullptr)
          node = new NodeBT<T>(value);
  else if (value < node->data)
          insert(node->left, value);
  else
          insert(node->right, value);
  */
}

vector<Record> AVLFile::inorder(int64_t pos_node) {
  /*
  if (node == nullptr)
          return;
  displayPreOrder(node->left);
  cout << node->data << endl;
  displayPreOrder(node->right);
  */
    return vector<Record>();
}
