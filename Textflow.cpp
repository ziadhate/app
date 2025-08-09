#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <map>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User
{
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

public:
    User()
    {
        // TODO: Implement default constructor
    }

    User(string uname, string pwd, string phone)
    {
        // TODO: Implement parameterized constructor
    }

    string getUsername() const
    {
        // TODO: Implement getter
        return "";
    }

    string getPhoneNumber() const
    {
        // TODO: Implement getter
        return "";
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return "";
    }

    string getLastSeen() const
    {
        // TODO: Implement getter
        return "";
    }

    void setStatus(string newStatus)
    {
        // TODO: Implement setter
    }

    void setPhoneNumber(string phone)
    {
        // TODO: Implement setter
    }

    void updateLastSeen()
    {
        // TODO: Implement last seen update
    }

    bool checkPassword(string pwd) const
    {
        // TODO: Implement password check
        return false;
    }

    void changePassword(string newPwd)
    {
        // TODO: Implement password change
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message
{
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message *replyTo;

    string getCurrentTime()
    {
        time_t current = time(0);
        string cur_Time = ctime(&current);
        return cur_Time;
    }

public:
    Message()
    {
        sender = "";
        content = "";
        timestamp = getCurrentTime();
        status = "Sent";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt)
    {
        sender = sndr;
        content = cntnt;
        timestamp = getCurrentTime();
        status = "Sent";
        replyTo = nullptr;
    }

    string getContent() const
    {
        // TODO: Implement getter

        return content;
    }

    string getSender() const
    {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const
    {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const
    {
        // TODO: Implement getter
        return status;
    }

    Message *getReplyTo() const
    {
        // TODO: Implement getter
        return replyTo;
    }

    void setStatus(string newStatus)
    {
        if (status == "Sent" && (newStatus == "Delivered" || newStatus == "Read"))
        {
            status = newStatus;
        }
        else if (status == "Delivered" && newStatus == "Read")
        {
            status = newStatus;
        }
        else
        {
        }
    }

    void setReplyTo(Message *msg)
    {
        if (msg != this && msg != nullptr)
        {
            // we will check about this condition.
            replyTo = msg;
        }
        else
        {
        }
    }

    void updateTimestamp()
    {
        timestamp = getCurrentTime();
    }

    void display() const
    {
        cout << "From: " << sender << endl;
        cout << "Time: " << timestamp << endl;
        cout << "Status: " << status << endl;
        if (replyTo != nullptr)
        {
            cout << "Replying to " << replyTo->getSender() << endl;
            cout << replyTo->getContent() << "\n";
            cout << endl;
        }
        else
        {
        }
        cout << "\n"
             << content << "\n"
             << endl;
    }

    void addEmoji(string emojiCode)
    {
        static const map<string, string> EMOJIS = {
            {":joy:", u8"😂"},
            {":open_mouth:", u8"😮"},
            {":cry:", u8"😢"},
            {":thumbsup:", u8"👍"},
            {":facepunch:", u8"👊"},
            {":green_heart:", u8"💚"},
            {":wave:", u8"👋"},
            {":thumbsdown:", u8"👎"},
            {":worried:", u8"😟"},
            {":world_map:", u8"🗺"}};

        auto emoji = EMOJIS.find(emojiCode);
        if (emoji != EMOJIS.end())
        {
            content += " " + emoji->second;
        }
        else
        {
            cout << "Unknown emoji code: " << emojiCode << endl;
        }
    }
};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat()
    {
        // TODO: Implement default constructor
    }

    Chat(vector<string> users, string name)
    {
        // TODO: Implement parameterized constructor
    }

    void addMessage(const Message &msg)
    {
        // TODO: Implement message addition
    }

    bool deleteMessage(int index, const string &username)
    {
        // TODO: Implement message deletion
        return false;
    }

    virtual void displayChat() const
    {
        // TODO: Implement chat display
    }

    vector<Message> searchMessages(string keyword) const
    {
        // TODO: Implement message search
        return {};
    }

    void exportToFile(const string &filename) const
    {
        // TODO: Implement export to file
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        // TODO: Implement constructor
    }

    void displayChat() const override
    {
        // TODO: Implement private chat display
    }

    void showTypingIndicator(const string &username) const
    {
        // TODO: Implement typing indicator
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat
{
private:
    vector<string> admins;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        // TODO: Implement constructor
    }

    void addAdmin(string newAdmin)
    {
        // TODO: Implement add admin
    }

    bool removeParticipant(const string &admin, const string &userToRemove)
    {
        // TODO: Implement remove participant
        return false;
    }

    bool isAdmin(string username) const
    {
        // TODO: Implement admin check
        return false;
    }

    bool isParticipant(string username) const
    {
        // TODO: Implement participant check
        return false;
    }

    void setDescription(string desc)
    {
        // TODO: Implement set description
    }

    void displayChat() const override
    {
        // TODO: Implement group chat display
    }

    void sendJoinRequest(const string &username)
    {
        // TODO: Implement join request
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat *> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        // TODO: Implement user search
        return -1;
    }

    bool isLoggedIn() const
    {
        // TODO: Implement login check
        return false;
    }

    string getCurrentUsername() const
    {
        // TODO: Implement get current user
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp()
    {
        // TODO: Implement user registration
    }

    void login()
    {
        // TODO: Implement user login
    }

    void startPrivateChat()
    {
        // TODO: Implement private chat creation
    }

    void createGroup()
    {
        // TODO: Implement group creation
    }

    void viewChats() const
    {
        // TODO: Implement chat viewing
    }

    void logout()
    {
        // TODO: Implement logout
    }

    void run()
    {
        while (true)
        {
            if (!isLoggedIn())
            {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main()
{
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}