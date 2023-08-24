#include <vector>
using namespace std;

struct Record
{
    int cod;
	char nombre[12];
	int ciclo;
	
	long left, right;
};

class AVLFile
{
private:
    string filename;
    long pos_root;
public:
    AVLFile(string filename){
		this pos_root = 0;
		this->filename = filename;
	}
	
    Record find(int key){
		return find(pos_root, key);
	}
	
	void insert(Record record){
		insert(po_root, record);
	}
	
    vector<Record> inorder(){
		return inorder(pos_root);
	}

private:
	Record find(long pos_node, int key){
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

	void insert(long pos_node, Record record){
		/*
		if (node == nullptr)
			node = new NodeBT<T>(value);
		else if (value < node->data)
			insert(node->left, value);
		else
			insert(node->right, value); 
		*/
	}
	
	vector<Record> inorder(long pos_node){
		/*
		if (node == nullptr)
			return;
		displayPreOrder(node->left);
		cout << node->data << endl;
		displayPreOrder(node->right);
		*/
	}
};
