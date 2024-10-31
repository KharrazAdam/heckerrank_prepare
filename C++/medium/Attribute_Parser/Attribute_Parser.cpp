using namespace std;

#include "Attribute_Parser.hpp"

// Constructors and Destructor
Tag::Tag() : value("Not Found!"), name("Not Found!"), id("Not Found!") {}

Tag::~Tag() {}

Tag::Tag(std::string _v, std::string _n, std::string _id) : value(_v), name(_n), id(_id) {}

// Getters
std::string Tag::get_name() const {
    return this->name;
}

std::string Tag::get_value() const {
    return this->value;
}

std::string Tag::get_id() const {
    return this->id;
}

std::map<std::string, std::string> Tag::get_attri() const {
    return this->attr;
}

// Setters
void Tag::set_name(std::string _name) {
    this->name = _name;
}

void Tag::set_value(std::string _value) {
    this->value = _value;
}

void Tag::set_id(std::string& _id) {
    this->id = _id;
}

void Tag::set_attr(std::string key, std::string value) {
    this->attr[key] = value;
}

// Utility
std::string Tag::get_attr(std::string key) {
    return this->attr[key];
}

void Tag::print_tag() const {
    std::cout << "id: " << get_id() << " - value: " << get_value() << " - name: " << get_name();
    auto att = get_attri();
    for (auto& x : att) {
        std::cout << " - " << x.first << ": " << x.second;
    }
    std::cout << std::endl;
}


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
            tag.set_attr(word.substr(0, word.find('=')), word.substr(word.find('=') + 2, word.length()));
        }
    }
    tag.print_tag();
    return tag;
};


bool    is_closed(const char *line) {
    return (line [1]== '/');
};


void parse(std::vector<Tag>& root, int& index, char input[][200], int N) {
    // Loop until all lines are processed
    while (index < N) {
        // Check if the current line is a closing tag
        if (is_closed(input[index])) {
            // Reached a closing tag, exit the current recursion level
            return;
        }
        
        // Get the new tag from the current line
        Tag new_tag = get_tag(input[index]);
        
        // If this is the root level (initial call), add directly to root
        if (root.empty()) {
            root.push_back(new_tag);
        } else {
            // Otherwise, add it as a child of the last tag in root
            root.back().children.push_back(new_tag);
        }
        
        // Move to the next line (increasing level)
        index++;
        
        // Recursive call to parse children for the last tag added
        parse(root.back().children, index, input, N);
        
        // After recursion returns, increment index again to process the next tag
        index++;
    }
}

