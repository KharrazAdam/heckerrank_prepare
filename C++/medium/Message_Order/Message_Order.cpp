#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Message {
    public: 
        Message() {}
        Message(const std::string &str, int id_): text(str), id(id_){} ;

        const   string& get_text() const {
            return text;
        }

        const   int& get_id() const {
            return this->id;
        }
        bool operator<(const Message &a) const {
            return this->get_id() < a.get_id();
        }
    private:
        std::string text;
        int id;
};

class MessageFactory {
public:
    MessageFactory() {}
    Message create_message(const std::string& text) {
        set_id(this->id + 1);
        return Message(text, get_id());
    }
    private:

    void set_id(const int& _id) {
        this->id = _id;
    }

    const int& get_id() const{
        return this->id;
    }
    int id;
};

class Recipient {
public:
    Recipient() {}
    void receive(const Message& msg) {
        messages_.push_back(msg);
    }
    void print_messages() {
        fix_order();
        for (auto& msg : messages_) {
            cout << msg.get_text() << endl;
        }
        messages_.clear();
    }
private:
    void fix_order() {
        sort(messages_.begin(), messages_.end());
    }
    vector<Message> messages_;
};

class Network {
public:
    static void send_messages(vector<Message> messages, Recipient& recipient) {
    // simulates the unpredictable network, where sent messages might arrive in unspecified order
        random_shuffle(messages.begin(), messages.end());         
        for (auto msg : messages) {
            recipient.receive(msg);
        }
    }
};



int main() {
    MessageFactory message_factory;
    Recipient recipient;
    vector<Message> messages;
    string text;
    while (getline(cin, text)) {
        messages.push_back(message_factory.create_message(text));
    }
    Network::send_messages(messages, recipient);
    recipient.print_messages();
}
