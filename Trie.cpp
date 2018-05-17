#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Trie {
	struct Node {
		map<char, unique_ptr<Node> > children;
		bool isLeaf;
		Node() : isLeaf{ false } {}
	};

	unique_ptr<Node> root;
public:
	Trie();
	void insert(const string& str);
	bool search(const string& str);
};

Trie::Trie() :root{ nullptr } {}

void Trie::insert(const string& str) {
	if (root == nullptr) {
		unique_ptr<Node> node(new Node());
		root = move(node);
	}

	Node *temp = root.get();
	for (const char& c : str) {
		if (temp->children.find(c) == temp->children.end()) {
			unique_ptr<Node> node(new Node());
			temp->children[c] = move(node);
		}

		temp = temp->children[c].get();
	}

	temp->isLeaf = true;
}

bool Trie::search(const string &str) {
	if (root == nullptr) return false;

	Node *temp = root.get();
	for (const char& c : str) {
		if (temp->children.find(c) == temp->children.end())
			return false;
		temp = temp->children[c].get();
	}
	return (temp->isLeaf);
}

int main() {
	Trie t;
	const string a[] = { "A", "to" , "tea" , "ted" , "ten", "i" , "in" , "inn" };
	int l = sizeof(a) / sizeof(a[0]);

	for (int i = 0; i < l; i++) {
		t.insert(a[i]);
	}

	return 0;
}