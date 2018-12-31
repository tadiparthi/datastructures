
using namespace std;
#define nil 0

struct Node {
	int key;
	int val;
        int freq;
	Node *next, *prev;
	Node(int k = -1, int v = -1) {
		key = k;
		val = v;
		next = nil;
		prev = nil;
                freq = 1;
	}
};

struct DLL
{
	Node *head;
	Node *tail;
	DLL()
	{
		head = new Node();
		tail = new Node();

		head->next = tail;
		tail->next = head;
	}


	/*
	 * add node in sorted by freq 
	 */

        void
        addNode(Node *n)
        {
                Node *p = head->next;
                while(p != tail) {
                        if(n->freq < p->freq) {
				break;
                        }
                        p = p->next;
                }
		n->next = p;
		n->prev = p->prev;

		p->prev->next = n;
		p->prev = n;
        }

        void
	addatHead(Node *n)
	{
		if(n == nil)
			return;

		n->next = head->next;
		n->prev = head;

		head->next->prev = n;
		head->next = n;
	}

	void
	addatTail(Node *n)
	{
		if(n == nil)
			return;

		n->next = tail;
		n->prev = tail->prev;

		tail->prev->next = n;
		tail->prev = n;
	}

	void
	removeNode(Node *n)
	{
		if(n == nil)
			return;

		n->next->prev = n->prev;
		n->prev->next = n->next;
	}

	Node*
	popTail()
	{
		if(head->next == tail)
			return nil;

		Node *n = tail->prev;
		removeNode(n);
		return n;
	}

	Node*
	popHead()
	{
		if(head->next == tail)
			return nil;

		Node *n = head->next;
		removeNode(n);
		return n;
	}

	Node*
	getHead()
	{
		if(head->next == tail)
			return nil;
		return head->next;
	}

	Node*
	getTail()
	{
		if(head->next == tail)
			return nil;
		return tail->prev;
	}

	void
	print(string header, int key = 0)
	{
		int count = 0;
		cout<<"header=" << header <<" key=" << key << endl;
		for(Node *p = head->next; p != tail; p = p->next) {
			cout<<" key="<<p->key<<" val="<<p->val<<" freq="<<p->freq<<endl;
			count++;
		}
		cout<< count <<"  ****************" << endl;
	}
};

class LFUCache {
	int capacity, count;
	unordered_map<int, Node*> data;
	DLL dll;

public:
    LFUCache(int capacity) {
	this->capacity = capacity;
	count = 0;
    }

    int get(int key) {
	if(data.find(key) == data.end())
		return -1;

	dll.print(string("before get key"), key);

	Node *p = data[key];

        p->freq++;
	dll.removeNode(p);
	dll.addNode(p);

	dll.print(string("after get key"), key);

	return p->val;
    }
    
    void put(int key, int value) {
//	dll.print(string("put key"), key);
	if(capacity == 0) return;
	if(data.find(key) == data.end()) {
		Node* n = dll.getHead();
                Node *p = new Node(key, value);
		dll.addNode(p);

		data[key] = p;
		count++;
		if(count > capacity) {
			dll.removeNode(n);
			if(n != nil)
	                        data.erase(n->key);
                        delete n;
                        count--;
//			dll.print(string("after resize"));
                }
		return;
	}

	Node *p = data[key];
	p->val = value;
        p->freq++;
	dll.removeNode(p);
	dll.addNode(p);
//	dll.print(string("after add"));
    }
};

main()
{
#if 0
	LFUCache l(2);
	l.put(1,1);
	l.put(2,2);

	cout<< "get 1=" << l.get(1)<<endl;
	l.put(3, 3);
	cout<< "get 2=" << l.get(2)<<endl;
	cout<<"get 3="<< l.get(3)<<endl;
	l.put(4,4);

	cout<<"get1="<< l.get(1)<<endl;
	cout<<"get3="<< l.get(3)<<endl;
	cout<<"get4="<< l.get(4)<<endl;
#endif
	LFUCache p(0);
	p.put(0, 0);
	cout <<" get 0" << p.get(0) << endl;
}
