#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Tag
{
    private:
        std::string value;
        std::string name;
        std::string id;
        std::map<std::string, std::string> attr;
        vector <Tag> nested;

    public:
        Tag(/* args */): value("Not Found!"), name("Not Found!"), id("Not Found!"){};

        ~Tag(){};

        Tag(std::string _v, std::string _n, std::string _id): value(_v), name(_n), id(_id){};

        std::string get_name() const {
            return this->name;
        };

        std::string get_value() const {
            return this->value;
        };

        std::string get_id() const {
            return this->id;
        };

        std::map<std::string, std::string> get_attri() const {
            return this->attr;
        };

        void    set_name(std::string  _name) {
            this->name = _name;
        }

        void    set_value(std::string  _value) {
            this->value = _value;
        }

        void    set_id(std::string & _id) {
            this->id = _id;
        };

        void    set_attr(std::string key, std::string value) {
            this->attr[key] = value;
        };

        std::string get_attr(std::string key) {
            return this->attr[key];
        };

        void    set_nested(Tag tag){
            this->nested.push_back(tag);
        };

        vector<Tag> get_nested() const {
            return this->nested;
        };

        void    print_tag() const {
            cout << "{ \n id: " << id << endl << " name: " << name << endl << " value: " << value << endl;
            if (!this->get_attri().empty()) {

                cout << " attributes:\n \t{\n";
                for (auto& i: this->get_attri()) {
                    cout << "\t\t"<< i.first << ": " << i.second << '\n';
                }
                cout << "\t}" << endl;
                }
                cout << "}" << endl << endl;
            }
};

#include <sstream>

Tag get_tag(const char * line) {
    Tag tag;
    stringstream ss(line);
    string word;

    while (ss >> word) {
        if (word[0] == '<')
            tag.set_id(word.erase(0, 1));
        else if (word == "value" || word == "name") {
            if (word == "value") {
                ss >> word;
                ss >> word;
                tag.set_value(word.substr(word.find('\"') + 1, word.rfind('\"') - word.find('\"') - 1));
            }
            else {
                ss >> word;
                ss >> word;
                tag.set_name(word.substr(word.find('\"') + 1, word.rfind('\"') - word.find('\"') - 1));
            }
        }
        else {
            tag.set_attr(word.substr(0, word.find('=')), word.substr(word.find('=') + 2, word.find('\"') - 1));
        }
    }
    // tag.print_tag();
    return tag;
};


bool    is_open(const char *line) {
    return (line [1]== '/');
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N, Q;
    cin >> N >> Q;
    cin.ignore();
    char input[N][200];

    int level = 0;
    vector<Tag> taz;
      
    for (int i = 0; i < N; i++) {
        std::cin.getline(input[i], 200);
        if (!is_open(input[i])) {
            if (!level) 
                taz.push_back(get_tag(input[i]));
            else
                (taz.back()).set_nested(get_tag(input[i]));
            level++;
        }
        else {
            level--;
        }
    };

    char queries[Q][200];
    for (int i = 0; i < Q; i++) {
        std::cin.getline(queries[i], 200);
    };
    return 0;
}
