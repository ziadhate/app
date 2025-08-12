#include <algorithm> // For find( , , ) in void createGroup()
#include <iostream>
#include <sstream> // For getline( , , ) in void loadUsers_file()
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <map>

using namespace std;

const string USER_DATA_FILE = "accounts.txt";
const int GROUP_LIMIT = 1024; // Example limit, can be adjusted

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

    string getPassword() const
    {
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

    void setLastSeen(string ls)
    {
        lastSeen = ls;
    }

    void updateLastSeen()
    {
        time_t current = time(0);

        string cur_time = ctime(&current);

        if (!cur_time.empty() && cur_time.back() == '\n')
        {
            cur_time.pop_back();
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
    Message *replyTo;

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

    Message *getReplyTo() const
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

    void setReplyTo(Message *msg)
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
        : participants(users), chatName(name), messages() {}

    virtual ~Chat() {}

    void addMessage(const Message &msg)
    {
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string &username)
    {
        if (index >= 0 && index < (int)messages.size())
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
        for (const auto &msg : messages)
        {
            msg.display();
        }
    }

    vector<Message> searchMessages(string keyword) const
    {
        vector<Message> results;
        for (const auto &msg : messages)
        {
            if (msg.getContent().find(keyword) != string::npos)
            {
                results.push_back(msg);
            }
        }

        return results;
    }

    void exportToFile(const string &filename) const
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << "Chat: " << chatName << "\n";
            for (const auto &msg : messages)
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
            for (const auto &msg : messages)
            {
                msg.display();
                cout << "--------------------" << endl;
            }
        }
        cout << "***************************" << endl;
    }

    void showTypingIndicator(const string &username) const
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

    bool removeParticipant(const string &admin, const string &userToRemove)
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

    void sendJoinRequest(const string &username)
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

    void viewJoinRequests(const string &admin)
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
    vector<Chat *> chats;
    vector<int> pinnedChats;
    vector<int> archivedChats;
    int currentUserIndex;

    int findUserIndexInternal(const string &username) const
    {
        for (int i = 0; i < (int)users.size(); i++)
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

    string getCurrentUsernameInternal() const
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
        ofstream file(USER_DATA_FILE);
        if (!file)
        {
            cerr << "Unable to save account.\n";
            return;
        }

        for (const auto &us : users)
        {
            file << us.getUsername() << "|"
                 << us.getPhoneNumber() << "|"
                 << us.getPassword() << "|"
                 << us.getStatus() << "|"
                 << us.getLastSeen() << "\n\n";
        }
    }

    void loadUsers_file()
    {
        ifstream file(USER_DATA_FILE);
        if (!file)
        {
            cerr << "Unable to load account.\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string un, ph, pw, st, lt;

            getline(ss, un, '|');
            getline(ss, ph, '|');
            getline(ss, pw, '|');
            getline(ss, st, '|');
            getline(ss, lt, '|');

            while (!st.empty() && (st.back() == '\n' || st.back() == '\r' || st.back() == ' '))
            {
                st.pop_back();
            }
            while (!lt.empty() && (lt.back() == '\n' || lt.back() == '\r' || lt.back() == ' '))
            {
                lt.pop_back();
            }

            if (un.empty() || ph.empty() || pw.empty() || st.empty())
                continue;

            User u(un, pw, ph);
            u.setStatus(st);
            u.setLastSeen(lt);
            users.push_back(u);
        }
    }

public:
    WhatsApp() : currentUserIndex(-1) { loadUsers_file(); }

    ~WhatsApp()
    {
        for (auto c : chats)
            delete c;
        chats.clear();
    }

    string getCurrentUsername() const { return getCurrentUsernameInternal(); }
    int findUserIndex(const string &username) const { return findUserIndexInternal(username); }

    void signUp()
    {
        string username, password, phone;

        cout << "Enter username: ";
        cin >> username;

        if (findUserIndexInternal(username) != -1)
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

        int index = findUserIndexInternal(username);
        if (index != -1 && users[index].checkPassword(password))
        {
            currentUserIndex = index;
            users[currentUserIndex].setStatus("Online");
            saveUsers_file();
            cout << "Logged-in successfully. Welcome, " << username << " !\n";
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

        int otherIndex = findUserIndexInternal(otherUser);
        if (otherIndex == -1)
        {
            cout << "User not found.\n";
            return;
        }

        string currentUser = getCurrentUsername();
        Chat *chat = new PrivateChat(currentUser, otherUser);
        chats.push_back(chat);
        cout << "Private chat started between " << currentUser << " and " << otherUser << ".\n";
        sendMessageMenu(chat, currentUser);
    }

    void createGroup()
    {
        string groupName, creator, username;
        short int Mychoice;
        vector<string> groupMembers;

        cout << "Enter group name: ";
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // getline(cin, groupName);

        while (groupName.empty())
        {
            cin.ignore();
            getline(cin, groupName);
        }

        creator = getCurrentUsernameInternal();
        groupMembers.push_back(creator);

        while ((int)groupMembers.size() < GROUP_LIMIT)
        {
            cout << "Enter participant username : ";
            cin >> username;

            if (username == creator)
            {
                cout << "You are already added as the group creator.\n";
                continue;
            }

            if (find(groupMembers.begin(), groupMembers.end(), username) != groupMembers.end())
            {
                cout << username << " is already a group member.\n";
                continue;
            }

            if (findUserIndexInternal(username) != -1)
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

        Chat *group = new GroupChat(groupMembers, groupName, creator);
        chats.push_back(group);
        cout << creator << "created " << groupName << " group.\n";
        sendMessageMenu(group, creator);
    }

    void sendMessageMenu(Chat* chat, const string& sender)
{
    int choice;
    while (true)
    {
        cout << "\n--- Chat Menu ---\n";
        cout << "1. Send Message\n";
        cout << "2. View Chat\n";
        cout << "3. Exit Chat\n";
        cout << "Choice: ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
        {
            string msgText;
            cout << "Enter message: ";
            getline(cin, msgText);
            if (!msgText.empty())
            {
                Message msg(sender, msgText);
                chat->addMessage(msg);
                cout << "Message sent!\n";
            }
            break;
        }
        case 2:
            chat->displayChat();
            break;
        case 3:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

    void viewChats() const
    {
        if (chats.empty())
        {
            cout << "No chats to display.\n";
            return;
        }

        cout << "\n=== Pinned Chats ===\n";
        for (int idx : pinnedChats)
        {
            if (idx >= 0 && idx < (int)chats.size())
            {
                cout << "\n--- Chat #" << (idx + 1) << " (Pinned) ---\n";
                chats[idx]->displayChat();
            }
        }

        cout << "\n=== Regular Chats ===\n";
        for (size_t i = 0; i < chats.size(); ++i)
        {
            if (find(pinnedChats.begin(), pinnedChats.end(), (int)i) == pinnedChats.end() &&
                find(archivedChats.begin(), archivedChats.end(), (int)i) == archivedChats.end())
            {
                cout << "\n--- Chat #" << (i + 1) << " ---\n";
                chats[i]->displayChat();
            }
        }
    }

    void viewArchivedChats() const
    {
        if (archivedChats.empty())
        {
            cout << "No archived chats.\n";
            return;
        }
        cout << "\n=== Archived Chats ===\n";
        for (int idx : archivedChats)
        {
            if (idx >= 0 && idx < (int)chats.size())
            {
                cout << "\n--- Chat #" << (idx + 1) << " ---\n";
                chats[idx]->displayChat();
            }
        }
    }

    void pinChat()
    {
        int chatNum;
        cout << "Enter chat number to PIN: ";
        cin >> chatNum;
        chatNum--;
        if (chatNum >= 0 && chatNum < (int)chats.size())
        {
            if (find(pinnedChats.begin(), pinnedChats.end(), chatNum) == pinnedChats.end())
            {
                pinnedChats.push_back(chatNum);
                cout << "Chat pinned successfully.\n";
            }
            else
                cout << "Chat is already pinned.\n";
        }
        else
            cout << "Invalid chat number.\n";
    }

    void unpinChat()
    {
        int chatNum;
        cout << "Enter chat number to UNPIN: ";
        cin >> chatNum;
        chatNum--;
        auto it = find(pinnedChats.begin(), pinnedChats.end(), chatNum);
        if (it != pinnedChats.end())
        {
            pinnedChats.erase(it);
            cout << "Chat unpinned.\n";
        }
        else
            cout << "Chat is not pinned.\n";
    }

    void archiveChat()
    {
        int chatNum;
        cout << "Enter chat number to ARCHIVE: ";
        cin >> chatNum;
        chatNum--;
        if (chatNum >= 0 && chatNum < (int)chats.size())
        {
            if (find(archivedChats.begin(), archivedChats.end(), chatNum) == archivedChats.end())
            {
                archivedChats.push_back(chatNum);
                cout << "Chat archived successfully.\n";
            }
            else
                cout << "Chat is already archived.\n";
        }
        else
            cout << "Invalid chat number.\n";
    }

    void unarchiveChat()
    {
        int chatNum;
        cout << "Enter chat number to UNARCHIVE: ";
        cin >> chatNum;
        chatNum--;
        auto it = find(archivedChats.begin(), archivedChats.end(), chatNum);
        if (it != archivedChats.end())
        {
            archivedChats.erase(it);
            cout << "Chat unarchived.\n";
        }
        else
            cout << "Chat is not archived.\n";
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
                // cin >> choice;
                if (!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 1)
                    login();
                else if (choice == 2)
                    signUp();
                else if (choice == 3)
                    break;
            }
            else
            {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. View Archived Chats\n5. PIN Chat\n6. Unpin Chat\n7. Archive Chat\n8. Unarchive Chat\n9. Logout\nChoice: ";
                int choice;
                // cin >> choice;
                if (!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 1)
                    startPrivateChat();
                else if (choice == 2)
                    createGroup();
                else if (choice == 3)
                    viewChats();
                else if (choice == 4)
                    viewArchivedChats();
                else if (choice == 5)
                    pinChat();
                else if (choice == 6)
                    unpinChat();
                else if (choice == 7)
                    archiveChat();
                else if (choice == 8)
                    unarchiveChat();
                else if (choice == 9)
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
    cout << "Welcome to Text Flow App (demo). Use Sign Up to create account.\n";
    whatsapp.run();
    return 0;
}
