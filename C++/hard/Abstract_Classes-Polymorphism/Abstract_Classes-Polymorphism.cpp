#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};


class LRUCache : public Cache
{
    private:
        bool is_full;
    
        void    set_isfull(bool b) {
            this->is_full = b;
        };

        bool    get_isfull() const{
            return this->is_full;
        };

    public:
        LRUCache(): is_full(false){};

        LRUCache(int _cp) {
            this->cp = _cp;
            this->tail = NULL;
            this->head = NULL;
            is_full = false;
        };

        ~LRUCache(){};

        int get(int x) {
            return mp.find(x) != mp.end() ? mp[x]->value : -1;
        };
        
        Node*   get_head() const {
            return head;
        };
        
        Node    *get_node(int k) {
            Node* tmp = head; 

            for (; tmp->key != k; tmp = tmp->next);
            return tmp;
        };

        void    add_node(int k, int val) {
            Node *node = new Node(NULL, this->head, k, val);
            this->head->prev = node;
            this->head = node;
            mp[k] = node;
        };

        void    rm_node() {
            Node* tmp = this->head;
            mp.erase(tail->key);
            tmp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete tmp;
        };

        void    set(int k, int val) {
            if (mp.empty()) {
                Node *node = new Node(k, val);
                mp[k] = node;
                head = tail = node;
            }
            else {
            if (mp.find(k) != mp.end()) { 
                Node* node = mp[k];
                
                if (head == node) {
                    node->value = val;
                    return;
                }
                
                node->value = val;
                
                if (node->prev) {
                    node->prev->next = node->next;
                }
                if (node->next) {
                    node->next->prev = node->prev;
                }
                
                if (node == tail) {
                    tail = node->prev;
                }
                
                node->next = head;
                node->prev = nullptr;
                if (head) {
                    head->prev = node;
                }
                head = node;
                
                mp[k] = head;
            }
                else {
                    this->add_node(k, val);
                    if (get_isfull() == true)
                        this->rm_node();
                }
            }
            if (!get_isfull() && this->cp == mp.size())
                set_isfull(true);
        };
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   Node* head = l.get_head();

    // while (head)
    // {
    //     std::cout << head->key << " : " << head->value << endl;
    //     head = head->next;
    // }
   return 0;
}
