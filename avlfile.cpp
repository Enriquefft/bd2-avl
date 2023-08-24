#include "avlfile.hpp"

Record AVLFile::find(long pos_node, int key) {
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

void AVLFile::insert(long pos_node, Record record) {

  // read pos_node
  Record current{};

  m_file_stream.open(m_filename, ios::in);
  m_file_stream.seekg(pos_node);

  /*
  if (node == nullptr)
          node = new NodeBT<T>(value);
  else if (value < node->data)
          insert(node->left, value);
  else
          insert(node->right, value);
  */
}

vector<Record> AVLFile::inorder(long pos_node) {
  /*
  if (node == nullptr)
          return;
  displayPreOrder(node->left);
  cout << node->data << endl;
  displayPreOrder(node->right);
  */
}
