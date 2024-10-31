#ifndef ATTRIBUTE_PARSER_HPP
#define ATTRIBUTE_PARSER_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>

class Tag {
    private:
        std::string value;
        std::string name;
        std::string id;
        std::map<std::string, std::string> attr;

    public:
        std::vector<Tag> children;

        // Constructors and Destructor
        Tag();
        ~Tag();
        Tag(std::string _v, std::string _n, std::string _id);

        // Getters
        std::string get_name() const;
        std::string get_value() const;
        std::string get_id() const;
        std::map<std::string, std::string> get_attri() const;

        // Setters
        void set_name(std::string _name);
        void set_value(std::string _value);
        void set_id(std::string& _id);
        void set_attr(std::string key, std::string value);

        // Utility
        std::string get_attr(std::string key);
        void print_tag() const;
};

// Function Prototypes
Tag get_tag(const char* line);
bool is_closed(const char* line);
void parse(std::vector<Tag>& root, int& index, char input[][200], int N);

#endif // ATTRIBUTE_PARSER_HPP
