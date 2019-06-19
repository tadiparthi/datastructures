#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define nil 0
#define alphabet 26
#define char2off(s) int(s-'a')
#define off2char(s) (s+'a')

class Node
{
	vector<Node*> child;
	int	ref;
	bool	word;
public:
	Node() : child(alphabet, nil) {
		ref = 1;
		word = false;
		
	}
	bool isWord() { return word; }
	void setWord(){ word = true; }
	void addChar(char c)
	{
		int off = char2off(c);
		if(off < 0 || off >= alphabet)
			return;
		if(child[off] != nil)
			return;
		child[off] = new Node();
	}

	Node* getChar(char  c)
	{
		return getChild(char2off(c));
	}

	Node* getChild(int off)
	{
		if(off < 0 || off >= alphabet)
			return nil;
		 return child[off];
	}
	int getChildSize(){return alphabet;}
};

class Trie
{
	Node* head;

public:
	Trie(){ head = new Node();}

	void
	addWordHelper(string &w, int off, Node *node)
	{
		if(w.size() == off) {
			node->setWord();
			return;
		}
		char c = w[off++];
		node->addChar(c);
		addWordHelper(w, off, node->getChar(c));
	}

	bool
	searchWordHelper(string &w, int off, Node *node)
	{
		if(node == nil)
			return false;
		if(off == w.size())
			return node->isWord();
		char c = w[off++];
		if(c == '.') {
			for(int i = 0; i < alphabet; i++) {
				bool r = searchWordHelper(w, off, node->getChild(i));
				if(r)
					return true;
			}
			return false;
		}
		return searchWordHelper(w, off, node->getChar(c));
	}

	void
	addWord(string &w)
	{
		addWordHelper(w, 0, head);
	}

	bool
	searchWord(string w)
	{
		return searchWordHelper(w, 0, head);
	}

	vector<string>
	getWords()
	{
		vector<string> res;
		string str ="";
	//	getWordsHelper(head, res, str);
		return res;
	}
};

int
main()
{
	Trie t;

	vector<string> words = { "bad", "pad", "sad", "test", "hblqo" };	
	for(auto w : words)
		t.addWord(w);	

	cout <<" finding=" << "assf"  <<" " << t.searchWord("assf") << endl;
	cout <<" finding=" << "bssf"  <<" " << t.searchWord("bssf") << endl;
	cout <<" finding=" << "bad"  <<" " << t.searchWord("bad") << endl;
	cout <<" finding=" << "test"  <<" " << t.searchWord("test") << endl;
	cout <<" finding=" << "hello"  <<" " << t.searchWord("hello") << endl;
	cout <<" finding=" << "b.d"  <<" " << t.searchWord("b.d") << endl;
	cout <<" finding=" << "h.l.o"  <<" " << t.searchWord("h.l.o") << endl;

	vector<string> tot = t.getWords();
}
