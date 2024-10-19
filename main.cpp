#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;
void clearScreen() {
    this_thread::sleep_for(chrono::seconds(1)); // Delay of 1 second
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}
bool exit_completely=1;
bool current_user;
vector<vector<string>> use_pass={{"admin","admin@123"}};
int flag=0;
vector<string> rooms={"Abheri","Basant","Kedar","Sahana","Malhar","Des","Bhairav"};
vector<int> time_slots;
void sign_up(vector<vector<string>> &use_pass) {
    clearScreen();
    cout << "Home Screen. > Sign Up.\n\n";
    string username, password;
    cout << "Enter Your Username: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;
    use_pass.push_back({username, password});
}

void login(const vector<vector<string>> &use_pass) {
    clearScreen();
    cout << "Home Screen. > Login.\n\n";
    string username, password;
    cout << "Enter Your Username: ";
    cin >> username;
    cout << "Enter Your Password: ";
    cin >> password;

    if (username == "admin") {
        current_user = true; // Admin user
    } else {
        current_user = false; // Normal user
    }

    bool found = false;
    for (const auto &entry : use_pass) {
        if (entry[0] == username && entry[1] == password) {
            found = true;
            break;
        }
    }

    if (found) {
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed. Try again."<<endl;
        login(use_pass);
    }
    
}

void home_screen(int flag,vector<vector<string>> &use_pass){
    int choice_login;
    do {
        clearScreen();
        cout<<"Welcome To Indian Insitute Of Technology Tirupati!!!\n\nThis is a Conference Hall Booking Individual Project For Engineering And Design Course.\nName:Atharva Bhosale.\nRoll No: ME24B005.\n\n";
        cout<<"Home Screen.\n\n";
        cout << "1. Sign Up\n2. Login\n3. Exit\nEnter your choice: ";
        cin >> choice_login;

        switch(choice_login) {
            case 1:
                sign_up(use_pass);
                flag=1;
                break;

            case 2:
                login(use_pass);
                flag=0;
                break;
            case 3:
                cout << "Exiting..." << endl;
                exit_completely=0;
                flag=0;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                flag=1;
        }
    } while (flag);
}
void addRoom(vector<string> &rooms){
    clearScreen();
    if (current_user)
    {
        cout<<"Home Screen. > Login. > Admin. > Add Rooms.\n\n";
    }else{
        cout<<"Home Screen. > Login. > Normal User. > Add Rooms.\n\n";
    }
    int no_room_add;
    string new_room;
    cout<<"Entre Number Of Rooms To Add:";
    cin>>no_room_add;
    cout<<"Entre Name Of Rooms Separated By Spaces:";
    while (no_room_add--)
    {
        cin>>new_room;
        rooms.push_back(new_room);
    }
    

}
void displayRooms(vector<string> &rooms){
    clearScreen();
    if (current_user)
    {
        cout<<"Home Screen. > Login. > Admin. > Display Rooms.\n\n";
    }else{
        cout<<"Home Screen. > Login. > Normal User. > Display Rooms.\n\n";
    }
    int counter=1;
    for (const auto &room : rooms)
    {
        cout<<counter<<"."<<room<<endl;
        counter++;
    }
    
}
void removeRoom(vector<string> &rooms){
    clearScreen();
    if (current_user)
    {
        cout<<"Home Screen. > Login. > Admin. > Remove Rooms.\n\n";
    }else{
        cout<<"Home Screen. > Login. > Normal User. > Remove Rooms.\n\n";
    }
    displayRooms(rooms);
    int no_room_remove;
    string remove_room;
    cout<<"\nEntre Number Of Rooms To Remove: "<<endl;
    cin>>no_room_remove;
    
    while (no_room_remove--)
    {
        cout<<"Entre Which Room To Remove: ";
        cin>>remove_room;
        auto remov =find(rooms.begin(),rooms.end(),remove_room);
        rooms.erase(remov);

    }
    
}
void reserveRoom(){
    clearScreen();
}
void cancleRoom(){
    clearScreen();
}
void displayTimeSlots(){
    clearScreen();
}
void main_menu(int flag,vector<string> &rooms){
    clearScreen();
    int exit;
    int choice_menue;
    if (current_user)
    {
        cout<<"Hoeme Screen. > Login. > Admin.\n\n"<<endl;
        cout<<"1.Add Room.\n2.Remove Room\n3.Reserve Room.\n4.Cancle Room.\n5.Display Rooms.\n6.Display Time Slots.\n\nEntre Your Choice:"<<endl;
        cin>>choice_menue;
        do{
            switch (choice_menue)
            {
            case 1:
                addRoom(rooms);
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 2:
                removeRoom(rooms);
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 3:
                reserveRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 4:
                cancleRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 5:
                displayRooms(rooms);
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 6:
                displayTimeSlots();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;
            case 7:
                if (choice_menue==7)
                {
                    home_screen(flag,use_pass);
                }
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                flag=1;
            }
        }while (flag);
        
    }else
    {
        
        cout<<"Home Screen. > Login. > Normal User.\n\n"<<endl;
        cout<<"1.Reserve Room.\n2.Cancle Room.\n3.Display Rooms.\n4.Display Time Slots.\n5.Return To Home Screen.\n\nEntre Your Choice:"<<endl;
        cin>>choice_menue;
        do{
            switch (choice_menue)
            {
            case 1:
                reserveRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 2:
                cancleRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;

            case 3:
                displayRooms(rooms);
                
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                

                break;

            case 4:
                displayTimeSlots();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(flag,rooms);
                }
                break;
            case 5:
                if (choice_menue==5)
                {
                    home_screen(flag,use_pass);
                }
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
                flag=1;
            }
        }while (flag);
        
    }
}
int main() {
    home_screen(flag,use_pass);
    if (exit_completely)
    {
        main_menu(0,rooms);
    }
    
    
    return 0;
}
