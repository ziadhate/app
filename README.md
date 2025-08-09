# 📱 WhatsApp-like Chat Application

A simple **WhatsApp-inspired chat application** implemented in C++ with **Object-Oriented Programming (OOP)** principles.  
The application allows users to register, log in, send private and group messages, manage conversations, and track message statuses.

---

## 🚀 Features

- **User Registration & Authentication**
  - Sign up with a username, password, and phone number.
  - Secure login with credentials validation.
  - Online/Offline status updates.

- **Private Chat**
  - 1-to-1 messaging between registered users.
  - View private chat history with sender, timestamp, and status.

- **Group Chat**
  - Create and name groups.
  - Add participants and assign admin privileges.
  - Send group messages visible to all members.
  - View group details including admins and message history.

- **Message Features**
  - Sent / Delivered / Read message statuses.
  - Search messages in a chat by keyword.

---

## 📂 System Architecture

The application follows **Object-Oriented Design** with the following classes:

| Class Name    | Responsibility |
|---------------|---------------|
| **User**      | Manages user data (username, password, phone number, status). |
| **Message**   | Stores message content, sender, timestamp, and status. |
| **Chat** *(Base Class)* | Handles common chat functionalities (message storage, display). |
| **PrivateChat** *(Derived from Chat)* | Implements 1-to-1 messaging. |
| **GroupChat** *(Derived from Chat)* | Manages group conversations with admin controls. |
| **WhatsApp** *(Main App Class)* | Handles authentication, chat creation, and navigation. |

---

## 📌 Functional Requirements Summary

| ID     | Feature | Description |
|--------|---------|-------------|
| FR1.1  | User Registration | Register with username, password, phone number. |
| FR1.2  | User Login | Authenticate user before granting access. |
| FR1.3  | User Status | Show Online/Offline status. |
| FR2.1  | Start Private Chat | Initiate chat with another registered user. |
| FR2.2  | Send Private Message | Store sender, content, timestamp, and status. |
| FR2.3  | View Private Chat | Display private chat history. |
| FR3.1  | Create Group | Name and add participants. |
| FR3.2  | Add Admins | Assign admin privileges. |
| FR3.3  | Send Group Message | Visible to all group members. |
| FR3.4  | View Group Chat | Show group name, admins, and messages. |
| FR4.1  | Message Status | Sent/Delivered/Read states. |
| FR4.2  | Search Messages | Search chat messages by keyword. |

---
