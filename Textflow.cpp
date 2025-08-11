#include <iostream>
#include <fstream>
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
        username = "";
        password = "";
        phoneNumber = "";
        status = "Offline";

    }

    User(string uname, string pwd, string phone)
    {
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = "Online";
        lastSeen = "Never";
    }

    string getUsername() const
    {
        return username;
    }

    string getPassword() const {

        return password;

    }

    string getPhoneNumber() const
    {
        return phoneNumber;
    }

    string getStatus() const
    {
        return status;
    }

    string getLastSeen() const
    {
        return lastSeen;
    }

    void setStatus(string newStatus)
    {
        if (newStatus != "Online" && newStatus != "Offline" &&
            newStatus != "Busy" && newStatus != "Away")
        {
            throw invalid_argument("Invalid status value");
        }
        status = newStatus;
    }

    void setPhoneNumber(string phone)
    {
        if (phone.empty())
        {
            throw invalid_argument("No phone number Entered");
        }
        phoneNumber = phone;
    }

    void updateLastSeen()
    {
        time_t current = time(0);

        string cur_time = ctime(&current);

        if (!lastSeen.empty() && lastSeen.back() == '\n')
        {
            lastSeen.pop_back();
        }
        lastSeen = cur_time;
    }

    bool checkPassword(string pwd) const
    {
        return password == pwd;
    }

    void changePassword(string newPwd)
    {
        password = newPwd;
    }

    void displayProfile() const
    {
        cout << "\nUser Profile:\n"
            << "Username: " << username << "\n"
            << "Phone: " << phoneNumber << "\n"
            << "Status: " << status << "\n"
            << "Last Seen: " << lastSeen << "\n";
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
    Message* replyTo;

    string getcurrentTime()
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
        timestamp = getcurrentTime();
        status = "Sent";
        replyTo = nullptr;
    }

    Message(string sndr, string cntnt)
    {
        sender = sndr;
        content = cntnt;
        timestamp = getcurrentTime();
        status = "Sent";
        replyTo = nullptr;
    }

    string getContent() const
    {
        return content;
    }

    string getSender() const
    {
        return sender;
    }

    string getTimestamp() const
    {
        return timestamp;
    }

    string getStatus() const
    {
        return status;
    }

    Message* getReplyTo() const
    {
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

    void setReplyTo(Message* msg)
    {
        if (msg != this && msg != nullptr)
        {
            // we will check about this condition.
            replyTo = msg;
        }
    }

    void updateTimestamp()
    {
        timestamp = getcurrentTime();
    }

    void display() const
    {
        cout << "Sender : " << sender << endl;
        cout << " Time : " << timestamp << endl;
        cout << " Status :" << status << endl;
        if (replyTo != nullptr)
        {
            cout << " Replying to :" << replyTo->getSender() << endl;
            cout << replyTo->getContent();
            cout << endl;
        }

        cout << " Content : " << content << endl;
    }

    string toString() const
    {
        string s = "[" + timestamp + "] " + sender + " (" + status + "): " + content;
        if (replyTo != nullptr)
        {
            s += " (reply to " + replyTo->getSender() + ": \"" + replyTo->getContent() + "\")";
        }
        return s;
    }

    void addEmoji(string emojiCode)
    {
        static map<string, string> EMOJIS = {
            {":joy:", u8"\U0001F602"},
            {":open_mouth:", u8"\U0001F62E"},
            {":cry:", u8"\U0001F622"},
            {":thumbsup:", u8"\U0001F44D"},
            {":facepunch:", u8"\U0001F44A"},
            {":green_heart:", u8"\U0001F49A"},
            {":wave:", u8"\U0001F44B"},
            {":thumbsdown:", u8"\U0001F44E"},
            {":worried:", u8"\U0001F61F"},
            {":world_map:", u8"\U0001F5FA"},

        };
        auto emoji = EMOJIS.find(emojiCode);
        if (emoji != EMOJIS.end())
        {
            content = content + " " + emoji->second;
        }
        else
        {
            cout << "Unknown emoji code " << endl;
        }
    }
};

// ========================
//    CHAT CLASS (BASE)
// ========================
class Chat
{
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat() : chatName("Untitled"), participants(), messages() {}

    Chat(vector<string> users, string name)
        : participants(users), chatName(name), messages() {
    }

    void addMessage(const Message& msg)
    {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username)
    {
        if (index >= 0 && index < messages.size())
        {
            if (messages[index].getSender() == username)
            {
                messages.erase(messages.begin() + index);
                return true;
            }
        }
        return false;
    }

    virtual void displayChat() const
    {
        cout << "Chat: " << chatName << endl;
        for (const auto& msg : messages)
        {
            msg.display();
        }
    }

    vector<Message> searchMessages(string keyword) const
    {
        vector<Message> results;
        for (const auto& msg : messages)
        {
            if (msg.getContent().find(keyword) != string::npos)
            {
                results.push_back(msg);
                return results;
            }
        }

        return {};
    }

    void exportToFile(const string& filename) const
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << "Chat: " << chatName << "\n";
            for (const auto& msg : messages)
            {
                file << msg.toString() << "\n";
            }
            file.close();
            cout << "Chat exported to " << filename << endl;
        }
        else
        {
            cerr << "Failed to open file for writing: " << filename << endl;
        }
    };
};

// ========================
//    PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat
{
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2)
    {
        user1 = u1;
        user2 = u2;
        participants.push_back(u1);
        participants.push_back(u2);
        chatName = u1 + "and" + u2;
    }

    void displayChat() const override
    {

        cout << "private chat Started Between: " << user1 << " " << " and " << " " << user2 << " ..." << endl;

        if (messages.empty())
        {
            cout << "Chat is empty" << endl;
        }
        else
        {
            for (const auto& msg : messages)
            {
                msg.display();
                cout << "--------------------" << endl;
            }
        }
        cout << "***************************" << endl;
    }

    void showTypingIndicator(const string& username) const
    {
        if (username == user1 || username == user2)
        {
            cout << username << " is typing..." << endl;
        }
        else
        {
            cout << "Error: " << username << " is not part of this private chat." << endl;
        }
    }
};

// ========================
//    GROUP CHAT CLASS
// ========================
class GroupChat : public Chat
{
private:
    vector<string> admins;
    vector<string> joinRequests;
    string description;

public:
    GroupChat(vector<string> users, string name, string creator)
    {
        admins.push_back(creator);
        users.push_back(creator);
        participants = users;
        chatName = name;
        description = "Welcome to the group chat!";
    }

    void addAdmin(string newAdmin)
    {
        if (isAdmin(newAdmin))
        {
            cout << newAdmin << " is already an admin." << endl;
        }
        else
        {
            if (isParticipant(newAdmin))
            {
                admins.push_back(newAdmin);
                cout << newAdmin << " is now an admin." << endl;
            }
            else
            {
                cout << "User not found." << endl;
            }
        }
    }

    bool removeParticipant(const string& admin, const string& userToRemove)
    {
        if (!isAdmin(admin))
        {
            return false;
        }
        else
        {
            for (int i = 0; i < participants.size(); i++)
            {
                if (participants[i] == userToRemove)
                {
                    participants.erase(participants.begin() + i);
                    return true;
                }
            }
            return false;
        }
    }

    bool isAdmin(string username) const
    {
        for (int i = 0; i < admins.size(); i++)
        {
            if (admins[i] == username)
            {
                return true;
            }
        }
        return false;
    }

    bool isParticipant(string username) const
    {
        for (int i = 0; i < participants.size(); i++)
        {
            if (participants[i] == username)
            {
                return true;
            }
        }
        return false;
    }

    void setDescription(string desc)
    {
        description = desc;
    }

    void displayChat() const override
    {
        cout << "\n===== Group Name: " << chatName << " =====\n";
        cout << "Description: " << description << endl;

        cout << "Admins: ";
        for (int i = 0; i < admins.size(); i++)
        {
            cout << admins[i];
            if (i < admins.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;

        cout << "\n--- Message History ---\n";
        if (messages.empty())
        {
            cout << "No messages yet." << endl;
        }
        else
        {
            for (int i = 0; i < messages.size(); i++)
            {
                messages[i].display();
            }
        }
        cout << "========================\n";
    }

    void sendJoinRequest(const string& username)
    {
        if (isParticipant(username))
        {
            cout << username << " is already a participant." << endl;
        }
        else
        {
            cout << username << " has requested to join " << chatName << endl;
            joinRequests.push_back(username);
        }
    }

    void viewJoinRequests(const string& admin)
    {
        if (!isAdmin(admin))
        {
            cout << "Only admins can view join requests." << endl;
            return;
        }

        if (joinRequests.empty())
        {
            cout << "No join requests." << endl;
            return;
        }

        short int choice = 0;
        int i = 0;

        while (i < joinRequests.size())
        {
            cout << joinRequests[i] << " has sent a join request." << endl;
            cout << "1. Approve\n2. Decline\n3. Ignore\nChoice: ";
            cin >> choice;

            while (choice < 1 || choice > 3)
            {
                cout << "\nInvalid choice. Please enter 1, 2, or 3: ";
                cin >> choice;
            }

            if (choice == 1)
            {
                cout << "Request from " << joinRequests[i] << " is approved." << endl;
                participants.push_back(joinRequests[i]);
                joinRequests.erase(joinRequests.begin() + i);
            }
            else if (choice == 2)
            {
                cout << "Request from " << joinRequests[i] << " is declined." << endl;
                joinRequests.erase(joinRequests.begin() + i);
            }
            else if (choice == 3)
            {
                cout << "Ignoring request from " << joinRequests[i] << endl;
                i++;
            }
        }
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp
{
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getUsername() == username)
            {
                return i;
            }
        }
        return -1;
    }

    bool isLoggedIn() const
    {
        return currentUserIndex != -1;
    }

    string getCurrentUsername() const
    {
        if (isLoggedIn())
        {
            return users[currentUserIndex].getUsername();
        }
        else
        {
            return "";
        }
    }

    void saveUsers_file() const
    {
        ofstream file("accounts.txt");
        if (!file)
        {
            cerr << "Unable to save acccount.\n";
            return;
        }
        for (const auto& us : users)
        {
            file << us.getUsername() << " "
                << us.getPhoneNumber() << " "
                << us.getPassword() << " "
                << us.getStatus() << " "
                << us.getLastSeen() << "\n";
        }
    }
    void loadUsers_file()
    {
        ifstream file("accounts.txt");
        if (!file)
        {
            cerr << "Unable to load acccount.\n";
            return;
        }
        string un, ph, pw, st, lt;
        while (file >> un >> ph >> pw >> st)
        {

            users.push_back(User(un, pw, ph));


        }
    }

public:
    WhatsApp() : currentUserIndex(-1) { loadUsers_file(); }

    void signUp()
    {
        string username, password, phone;

        cout << "Enter username: ";
        cin >> username;

        if (findUserIndex(username) != -1)
        {
            cout << "Username already taken. Try a different one.\n";
            return;
        }

        cout << "Enter password: ";
        cin >> password;

        cout << "Enter phone number: ";
        cin >> phone;

        users.push_back(User(username, password, phone));
        saveUsers_file();
        cout << "User registered successfully.\n";
    }

    void login()
    {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        int index = findUserIndex(username);
        if (index != -1 && users[index].checkPassword(password))
        {
            currentUserIndex = index;
            users[currentUserIndex].setStatus("Online");
            saveUsers_file();
            cout << "Login successful. Welcome, " << username << "!\n";

        }
        else
        {
            cout << "Invalid username or password.\n";
        }
    }

    void startPrivateChat()
    {
        string otherUser;
        cout << "Enter the username to chat with: ";
        cin >> otherUser;

        int otherIndex = findUserIndex(otherUser);
        if (otherIndex == -1)
        {
            cout << "User not found.\n";
            return;
        }

        string currentUser = getCurrentUsername();
        Chat* chat = new PrivateChat(currentUser, otherUser);
        chats.push_back(chat);
        cout << "Private chat started between " << currentUser << " and " << otherUser << ".\n";
    }

    void createGroup()
    {
        string groupName, creator, username;
        int groupLimit = 1024, Mychoice;
        vector<string> groupMembers;

        cout << "Enter group name: ";
        while (groupName.empty())
        {
            cin.ignore();
            getline(cin, groupName);
        }

        creator = getCurrentUsername();
        groupMembers.push_back(creator);

        while (groupMembers.size() < groupLimit)
        {
            cout << "Enter participant username : ";
            cin >> username;

            if (username == creator)
            {
                cout << "You are already added as the group creator.\n";
                continue;
            }

            if (findUserIndex(username) != -1)
            {
                groupMembers.push_back(username);
            }
            else
            {
                cout << "User '" << username << "' does not exist.\n";
                continue;
            }

            cout << username << " is added successfully.\n";
            cout << "Add another participant? (1.Yes / 2.No): ";
            cin >> Mychoice;
            if (Mychoice != 1)
            {
                break;
            }
        }

        Chat* group = new GroupChat(groupMembers, groupName, creator);
        chats.push_back(group);
        cout << creator << "created " << groupName << " group.\n";
    }

    void viewChats() const
    {
        if (chats.empty())
        {
            cout << "No chats to display.\n";
            return;
        }

        for (size_t i = 0; i < chats.size(); ++i)
        {
            cout << "\n--- Chat #" << (i + 1) << " ---\n";
            chats[i]->displayChat();
        }
    }

    void logout()
    {
        users[currentUserIndex].updateLastSeen();
        users[currentUserIndex].setStatus("Offline");
        saveUsers_file();
        currentUserIndex = -1;
        cout << "Logged-out successfully.\n";
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
