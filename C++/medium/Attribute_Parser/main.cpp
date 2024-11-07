#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <string.h>

class Tag
{
    private:
        int data;
        std::string id;
        std::string parent; 

        std::map<std::string, std::string> attr;
    public:
        Tag(){};
        Tag(std::string i, std::string par_,int d ): id(i), parent(par_), data(d){};
        ~Tag(){};

        std::string get_parent() const {
            return this->parent;
        }

        std::string get_attr(std::string k){
            const auto& a = this->attr[k];
            if (a == "")
                return "Not Found!";
            else
                return a;
        }

        void set_parent(std::string str) {
            this->parent = str;
        }

        void set_att(std::string k, std::string v) {
            attr[k] = v;
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

std::string vn(std::stringstream &ss) {
    std::string word;
    ss >> word;
    ss >> word;
    return word.substr(1, word.rfind('\"') - 1);
}

void    att(Tag& t, std::string &word) {
    std::string key, value;
    key = word.substr(0, word.find('='));
    int a = word.find('\"');
    value = word.substr(a + 1, word.rfind('\"') - a - 1);
    t.set_att(key, value);
}

void    parse(Tag& t, const char *input) {
    
    std::stringstream ss(input);
    std::string word;

    ss >> word;
    while (ss >> word)
    {
        if (word.find('=') == std::string::npos)
            t.set_att(word, vn(ss));        
        else if (word != "") {
            att(t, word);
        }
    };
};


std::pair<std::string, std::string> Q_att(std::map<std::string, Tag> m, std::string str) {
    int pos = str.find('~');  // Find the position of '~'
    if (pos == std::string::npos) return {"", ""};  // If '~' not found, exit

    std::string lastTag = "";
    int start = 0;
    std::string currentTag = "";
    while (true) {
        int nextDot = str.find('.', start);
        if (nextDot == std::string::npos || nextDot > pos) break;
        currentTag = str.substr(start, nextDot - start);
        // std::cout << currentTag << " -> papa: " << lastTag << std::endl;
        if (m[currentTag].get_parent() != lastTag) {
            return {"", ""};
        }
        lastTag = currentTag;
        start = nextDot + 1;
    }

    currentTag = str.substr(start, pos - start);
        if (m[currentTag].get_parent() != lastTag) {
            return {"", ""};
        }

    std::string att = str.substr(pos + 1); 

    return {currentTag, att};
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

    // for(auto &x: m)
    //     std::cout << x.first <<  " " << x.second.get_parent() << std::endl;
    while (Q--) {
        std::cin.getline(input[0], 200);
        if (!input[0][0]) continue;

        std::pair<std::string, std::string> pair;

        pair = Q_att(m, std::string(input[0]));
        if (pair.first == "" && pair.second == "") {std:: cout << "Not Found!\n";}
        else std::cout << m[pair.first].get_attr(pair.second) << std::endl;
    }
    return 0;
}
