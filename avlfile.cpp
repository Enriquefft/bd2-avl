#include "avlfile.hpp"

Record AVLFile::find(int64_t pos_node, int key) {
  if (pos_node == -1){
      throw runtime_error("No hay datos en el arbol");
  }

  ifstream file(this->m_filename, ios::binary);
  file.seekg(pos_node); // Vamos a la posición del nodo
  // Leemos el record
  Record record;
  file >> record;
  file.close();

  if (record.cod == key) {
      return record;
  } else if (record.cod < key) {
      // Se busca por el hijo izquierdo
      return find(record.left, key);
  } else if (record.cod > key) {
      // Se busca por el hijo derecho
      return find(record.left, key);
  } else {
      throw runtime_error("No se encontró la llave");
  }
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
