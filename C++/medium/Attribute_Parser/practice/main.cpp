#include <iostream>
#include <string>
#include <map>
class Tag
{
    private:
        int data;
        std::string id;
        std::string parent; 

        std::string value;
        std::string name;
        std::map<std::string, std::string> attr;
    public:
        Tag(){};
        Tag(std::string i, std::string par_,int d ): id(i), parent(par_), data(d), value("Not Found!"), name("Not Found!"){};
        ~Tag(){};

        std::string get_parent() const {
            return this->parent;
        }

        std::string get_value() const {
            return this->value;
        }

        std::string get_name() const {
            return this->name;
        }
        // -----------------------------------------------------------------------

        void set_parent(std::string str) {
            this->parent = str;
        }

        void set_value(std::string str) {
            this->value = str;
        }

        void set_name(std::string str) {
            this->name = str;
        }
};

bool    is_open(char c) {
    return c != '/';
}

std::string get_id(std::string str) {
    size_t pos1 =  str.find(' ') - 1;
    size_t pos2 = str.find('>') - 1;
    return str.substr(1, pos1 <= pos2 ? pos1 : pos2);
}

#include <sstream>
#include <string.h>
std::string vn(const char *vm, std::stringstream &ss) {
    std::string word;
    ss >> word;
    ss >> word;    
    return word.substr(1, word.rfind('\"') - 1);
}
void    parse(Tag& t, const char *input) {
    
    std::stringstream ss(input);
    std::string word;

    ss >> word;
    while (ss >> word)
    {
        // std::cout << word << std::endl;
        if (word == "value")
            t.set_value(vn("value", ss));
        else if (word == "name")
            t.set_name(vn("name", ss));
            // do name
        else if (word != "") ;
            // do attribute
        // break;
    }
}

int main(void) {
    std::map<std::string, Tag> m;
    std::string parent("");

    int N, Q, i = 0;
    std::cin >> N >> Q;
    (void)Q;
    std::cin.ignore();
    char input[N][200];

    for (; i < N; i++) {
        std::cin.getline(input[i], 200);
        if (is_open(input[i][1])) {
            std::string id = get_id(std::string(input[i]));
            m[id] = Tag(id, parent, i);
            parent = id;
            parse(m[id], input[i]);
        }
        else
            parent = m[parent].get_parent();
    }

    for (auto &x: m) {
        std::cout << "me " << x.first << " -> my parent is: " << x.second.get_parent() << " my value is: " << x.second.get_value() << " my name is: "<< x.second.get_name() <<  std::endl;
    }
    return 0;
}
