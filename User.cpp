#include <iostream>

using namespace std;

class HomeWindow
{
public:
    void display()
    {
        cout << "==================================" << endl;
        cout << "         SecureVault              " << endl;
        cout << "==================================" << endl;
        cout << endl;
        cout << "1. Login" << endl;
        cout << "2. Sign Up" << endl;
        cout << "3. Exit" << endl;
        cout << endl;
    }

    int getChoice()
    {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }
};
class SignupWindow
{
    public:
    void display(){
    cin.ignore();

    string name;
    string email;
    string password;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your password: ";
    getline(cin, password);
    }
};
class User{
    private:
    string name;
    string email;
    string password;

    public:
    void setName(string name){
        this->name = name;
    }
    void setEmail(string email){
        this->email = email;
    }
    void setPassword(string password){
        this->password = password;
    }
    string getName(){
        return name;
    }
    string getEmail(){
        return email;
    }
    string getPassword(){
        return password;
    }
    User(string name, string email, string password){
        this->name = name;
        this->email = email;
        this->password = password;
    }
};

int main(){

    HomeWindow home;

    home.display();

    int choice = home.getChoice();

    cout << "You selected option: " << choice << endl;

    return 0;
}