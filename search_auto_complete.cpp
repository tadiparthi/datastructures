/*
 * https://leetcode.com/problems/design-search-autocomplete-system/
 * using Trie, top 3  search results
 */

struct ResStr
{
    string sentence;
    int times;
    ResStr() {}
    ResStr(string s, int t) { sentence = s; times = t;}
    bool operator < (const ResStr &s) 
    {
        if(times != s.times) {
            return times > s.times;
        }
        return sentence < s.sentence;
    }
};

struct Node
{
    Node *next, *child;
    char c;
    string sentence;
    bool word;
    int times;
    
    Node(char c) 
    {
        this->c = c;
        sentence.clear();
        word = false;
        times = 0;
        next = nullptr;
        child = nullptr;
    }
};

void
insert_word(Node **head, const string &s, int times)
{
    Node **q, *p;
    
    q = head;
    for(const char c : s) {
        for(p = *q; p != nullptr; p = p->next) {
            if(p->c == c)
                break;
            q = &p->next;
        }
        if(p == nullptr) {
            p = new Node(c);
            *q = p;
        }
        q = &p->child;
    }
    p->word = true;
    p->sentence = s;
    p->times += times;
}

Node*
get_node(Node *head, string &s)
{
    Node *p = head;
    int sz = s.size();

    for(int i = 0; i < sz; i++) {
        char c = s[i];
        for(; p != nullptr; p = p->next) {
            if(p->c == c)
                break;
        }
        if(p == nullptr || i == sz-1)
            break;
        p = p->child;
    }
//    if(p && p->word) cout << "found p=" << p << " " << p->sentence << " " << p->times << endl;
    return p;
}

void
browse_node(Node *n, vector<ResStr> &res)
{
    for(;n != nullptr; n = n->next) {
        browse_node(n->child, res);
        if(n->word) {
            res.push_back({n->sentence, n->times});
        }
    }
}

void
print_helper(Node *head, string &str)
{
    Node *p = head;
    for(p = head; p != nullptr; p = p->next) {
        str += p->c;
        if(p->word) {
            cout << p << " " << str <<" " << p->times << endl;
        }
        print_helper(p->child, str);
        str.pop_back();
    }
}

class AutocompleteSystem {
    Node *head;
    string str;
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        head = nullptr;
        str.clear();
        int pos = 0;
        for(const auto &s: sentences) {
            insert_word(&head, s, times[pos++]);
        }
        string tmp;
//        print_helper(head, tmp);
    }

    vector<string> input(char c) {
        if(c == '#') {
            if(str.empty()) return vector<string> ();
            insert_word(&head, str, 1);
            str.clear();
            return vector<string> ();
        }
        str += c;
        Node *n = get_node(head, str);
        vector<ResStr> res;
        if(n != nullptr && n->word) {
            res.push_back({n->sentence, n->times});
        }
        if(n != nullptr)
            browse_node(n->child, res);
        sort(begin(res), end(res));
        if(res.size() > 3)
            res.resize(3);

        vector<string> vec;
        for(const auto &r: res) {
            vec.push_back(r.sentence);
        }
        return vec;
    }
};

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem* obj = new AutocompleteSystem(sentences, times);
 * vector<string> param_1 = obj->input(c);
 */
