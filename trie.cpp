#include <iostream>
#include <vector>

vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        tokens.push_back(item);
    }
    return tokens;
}

#define nil 0

typedef struct Node Node;
struct Node
{
	Node	*child;
	Node	*next;
	char	data;
	bool	word;
	int	ref;

	Node(char c) {
		data = c;
		ref = 1;
		word = false;
		next = nil;
		child = nil;
	}
};


void
insertnode(string s, Node **head)
{
	Node	**p, *q;
	int		sz;

	p = head;
	q = *p;
	sz = s.size();

	for(int i = 0; i < sz; i++) {
		for(q = *p; q != nil; q = q->next) {
			if(q->data == s[i]) {
				p = &q->child;
				q->ref++;
				break;
			}
		}
		if(q == nil) {
			q = new Node(s[i]);
			if(!q)
				return;
			q->next = *p;
			*p = q;
			p = &q->child;
		}
	}

	if(q)
		q->word = true;
}

void
deletehelp(Node *q)
{
	if(!q)
		return;

	deletehelp(q->next);
	deletehelp(q->child);
	free(q);
}

void
deletenode(char *s, Node **head)
{
	Node	**p, *q;
	int	i, len;

	p = head;
	q = *p;
	len = strlen(s);
	for(i = 0; i < len; i++) {
		for(q = *p; q != nil; q = q->next) {
			if(q->data == s[i]) {
				q->ref--;
				if(q->ref == 0) {
					*p = q->next;
					q->next = nil;
					deletehelp(q);
					return;
				}
			}
			p = &q->next;
		}
		if(q == nil) {
			printf("lost string %s\n", s);
			return;
		}
		p = &q->child;
	}
}

int
findnode(Node *head, char *s)
{
	Node *q;
	int i, len;

	q = head;
	len = strlen(s);

	for(i = 0; i < len; i++) {
		for(; q != nil; q = q->next) {
			if(q->data == s[i]) {
				break;
			}
		}
		if(q == nil)
			return 0;
		q =  q->child;
	}
	return 1;
}

void
printtree(Node *head)
{
	Node	*q;

	if(!head) {
		return;
	}

	for(q = head; q != nil; q = q->next) {
		printf(" %c", q->data);
	}
	for(q = head; q != nil; q = q->next) {
		printtree(q->child);
	}
	printf("\n");
}

int
main()
{
	Node *head = nil;

	insertnode("car", &head);
	insertnode("tac", &head);
//	insertnode("cat", &head);
//	insertnode("cab", &head);

	printtree(head);
	printf("no  = %d\n", no);
	printf(" ttt: %d\n", findnode(head, "bob"));
	printf(" ca: %d\n", findnode(head, "ca"));
	printf(" cab: %d\n", findnode(head, "cab"));
}

