
Single Responsibility Principle (SRP)
A class should have only one responsibility (one reason to change).

Bad Example (Violates SRP)
One class is doing too many things:

#include <iostream>
#include <string>
using namespace std;

class User {
public:
    string name;

    User(string n) : name(n) {}

    void saveToDatabase() {
        cout << "Saving user to database...\n";
    }

    void sendWelcomeEmail() {
        cout << "Sending welcome email...\n";
    }
};
Problem:
User is doing 3 jobs:

Storing user data

Database work

Email sending

If email logic changes → modify class
If database logic changes → modify class
If user behaviour changes → modify class

Too many reasons to change → SRP broken
-----------------------------------------
Good Example (Follows SRP)
Break the responsibilities into three separate classes:

#include <iostream>
#include <string>
using namespace std;

// 1. Only stores data
class User {
public:
    string name;
    User(string n) : name(n) {}
};

// 2. Only handles saving user
class UserRepository {
public:
    void save(const User& user) {
        cout << "Saving " << user.name << " to database...\n";
    }
};

// 3. Only handles email
class EmailService {
public:
    void sendWelcome(const User& user) {
        cout << "Sending welcome email to " << user.name << "...\n";
    }
};

int main() {
    User user("Alice");

    UserRepository repo;
    EmailService email;

    repo.save(user);
    email.sendWelcome(user);

    return 0;
}