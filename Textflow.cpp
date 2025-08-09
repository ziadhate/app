#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include<map>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User() {
        // TODO: Implement default constructor
    }

    User(string uname, string pwd, string phone) {
        // TODO: Implement parameterized constructor
    }

    string getUsername() const {
        // TODO: Implement getter
        return "";
    }

    string getPhoneNumber() const {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const {
        // TODO: Implement getter
        return "";
    }

    string getLastSeen() const {
        // TODO: Implement getter
        return "";
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
    }

    void setPhoneNumber(string phone) {
        // TODO: Implement setter
    }

    void updateLastSeen() {
        // TODO: Implement last seen update
    }

    bool checkPassword(string pwd) const {
        // TODO: Implement password check
        return false;
    }

    void changePassword(string newPwd) {
        // TODO: Implement password change
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;

    string getcurrentTime(){
        time_t current = time(0);
        string cur_Time = ctime(&current);

    return cur_Time;
    }

public:
    Message() {
       sender = "";
       content = "";
       timestamp = getcurrentTime();
       status = "Sent";
       replyTo = nullptr;
    }

    Message(string sndr, string cntnt) {
       sender = sndr;
       content = cntnt;
    }

    string getContent() const {

        return content;
    }

    string getSender() const {
        return sender;
    }

    string getTimestamp() const {

        return timestamp;
    }

    string getStatus() const {

        return status;
    }

    Message* getReplyTo() const {

        return replyTo;
    }

    void setStatus(string newStatus) {
        if (status == "Sent" && (newStatus == "Delivered" || newStatus == "Read"))
        {
            status = newStatus;
        }
        else if (status == "Delivered" && newStatus == "Read")
        {
            status = newStatus;
        } else {

        }

    }

    void setReplyTo(Message* msg) {
        if ( msg != this &&msg != nullptr){
                // we will check about this condition.
            replyTo = msg;
        }
    }

    void updateTimestamp() {
       timestamp = getcurrentTime();
    }

    void display() const {
       cout<< "Sender : "<< sender << endl;
       cout << " Time : "<< timestamp << endl;
       cout << " Status :" << status << endl;
       if ( replyTo != nullptr){
        cout << " Replying to :"<< replyTo ->getSender() << endl;
        cout << replyTo ->getContent();
        cout << endl;
       }

       cout << " Content : "<< content << endl;

    }

    void addEmoji(string emojiCode) {

         static map<string, string> EMOJIS = {
         {":joy:" , u8"\U0001F602"},
          {":open_mouth:" , u8"\U0001F62E"},
          {":cry:" , u8"\U0001F622"},
          {":thumbsup:" , u8"\U0001F44D"},
           {":facepunch:" , u8"\U0001F44A"},
            {":green_heart:" , u8"\U0001F49A"},
            {":wave:" , u8"\U0001F44B"},
            {":thumbsdown:" , u8"\U0001F44E"},
            {":worried:" , u8"\U0001F61F"},
            {":world_map:" , u8"\U0001F5FA"},

         };
         auto emoji = EMOJIS.find(emojiCode);
        if (emoji != EMOJIS.end()){
            content = content + " " + emoji->second ;
        }
        else {
            cout<< "Unknown emoji code "<< endl;
        }
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
 
    Chat() : chatName("Untitled"), participants(), messages() {}

    Chat(vector<string> users, string name)
        : participants(users), chatName(name), messages() {
    }

    void addMessage(const Message& msg) {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username) {
        if (index >= 0 && index < messages.size()) {
            if (messages[index].getSender() == username) {
                messages.erase(messages.begin() + index);
                return true;

            }
       }
        return false;
    }

    virtual void displayChat() const {
        virtual void displayChat() const {
            cout << "Chat: " << chatName << endl;
            for (const auto& msg : messages) {
                msg.display();
            }
        }
    }

    vector<Message> searchMessages(string keyword) const {
        vector<Message> searchMessages(string keyword) const {
            vector<Message> results;
            for (const auto& msg : messages) {
                if (msg.getContent().find(keyword) != string::npos) {
                    results.push_back(msg);
                }
            }
            return results;
        }
        return {};
    }

    void exportToFile(const string& filename) const {
        void exportToFile(const string & filename) const {
            ofstream file(filename);
            if (file.is_open()) {
                file << "Chat: " << chatName << "\n";
                for (const auto& msg : messages) {
                    file << msg.toString() << "\n";
                }
                file.close();
                cout << "Chat exported to " << filename << endl;
            }
            else {
                cerr << "Failed to open file for writing: " << filename << endl;
            }
        }
    };
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2) {
        // TODO: Implement constructor
    }

    void displayChat() const override {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator) {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc) {
        // TODO: Implement set description
    }

    void displayChat() const override {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const {
        // TODO: Implement user search
        return -1;
    }

    bool isLoggedIn() const {
        // TODO: Implement login check
        return false;
    }

    string getCurrentUsername() const {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp() {
        // TODO: Implement user registration
    }

    void login() {
        // TODO: Implement user login
    }

    void startPrivateChat() {
        // TODO: Implement private chat creation
    }

    void createGroup() {
        // TODO: Implement group creation
    }

    void viewChats() const {
        // TODO: Implement chat viewing
    }

    void logout() {
        // TODO: Implement logout
    }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
