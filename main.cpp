#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;
void clearScreen() {
    this_thread::sleep_for(chrono::seconds(1)); // Delay of 1 second
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}
//Variables And Data Storage
bool current_user;
string name_current_user;
vector<vector<string>> use_pass={{"admin","admin@123"}};
int flag=0;
vector<string> rooms={"LHC_CR-211.","Academic_Building-1.","Academic_Building-2.","Central_Library_TC-1."};
vector<int> time_slots;
struct Reservation {
    int sr;
    string userName;
    string roomName;
    int startTime;
    int endTime;
    string date;
};
vector<Reservation> reservations ;
void print_data(const vector<Reservation>& reservations) {
    cout << "Sr No.\tUsername\tRoom Name\tStart Time (24 hrs format)\tEnd Time (24 hrs format)\tDate" << endl;
    for (const auto& res : reservations) {
        cout << res.sr << "\t"
             << res.userName << "\t\t"
             << res.roomName << "\t\t"
             << res.startTime << "\t\t\t\t"
             << res.endTime << "\t\t\t\t"
             << res.date << endl;
    }
}
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
        name_current_user=username;
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed. Try again."<<endl;
        login(use_pass);
    }
    
}
void home_screen(vector<vector<string>> &use_pass){
    int choice_login;
        clearScreen();
        cout<<"Welcome To Indian Insitute Of Technology Tirupati!!!\n\nThis is a Conference Hall Booking Individual Project For Engineering And Design Course.\nName:Atharva Bhosale.\nRoll No: ME24B005.\n\n";
        cout<<"Home Screen.\n\n";
        cout << "1. Sign Up.\n2. Login.\nEnter your choice: ";
        cin >> choice_login;

        switch(choice_login) {
            case 1:
                sign_up(use_pass);
                home_screen(use_pass);
                break;

            case 2:
                login(use_pass);
                break;
            default:
                cout << "Invalid choice. Try again." <<endl;
                exit(0);
                
        }
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
void reserveRoom() {
    clearScreen();
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Reserve Room.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Reserve Room.\n\n";
    }
    for (int i = 1; i <=rooms.size(); i++)
    {
        cout<<i<<"."<<rooms[i-1]<<endl;
    }
    
    print_data(reservations);
    Reservation newReservation;
    newReservation.userName = name_current_user;
    newReservation.sr = reservations.size()+1;
    cout << "Enter Room Name (Replace ' ' with '_'): ";
    cin >> newReservation.roomName;
    cout << "Enter Start Time (24 hrs format): ";
    cin >> newReservation.startTime;
    cout << "Enter End Time (24 hrs format): ";
    cin >> newReservation.endTime;
    cout << "Enter Date (DD-MM-YYYY): ";
    cin >> newReservation.date;

    reservations.push_back(newReservation);
}
void cancleRoom(){
    clearScreen();
    if (current_user)
    {
        cout<<"Home Screen. > Login. > Admin. > Cancle Room.\n\n";
    }else{
        cout<<"Home Screen. > Login. > Admin. > Cancle Room.\n\n";
    }
    print_data(reservations);
    int cancle;
    cout<<"\n\nEntre Sr No To Cancle Reservation:";
    cin>>cancle;
    auto it1 = find_if(reservations.begin(), reservations.end(), [cancle](const Reservation& res) { return res.sr == cancle; });
    if (it1 != reservations.end()) {
        reservations.erase(it1);
    }
    for (int i = 1; i <=reservations.size(); i++) {
        reservations[i-1].sr = i;
    }
    cout<<"\n\n";
    print_data(reservations);
}
void displayTimeSlots(){
    clearScreen();
    if (current_user)
    {
        cout<<"Home Screen. > Login. > Admin. > Display Reserved Time Slots.\n\n";
    }else{
        cout<<"Home Screen. > Login. > Normal User. > Display Reserved Time Slots.\n\n";
    }
    print_data(reservations);
    
}
void main_menu(vector<string> &rooms){
    clearScreen();
    int exit;
    int choice_menue;
    if (current_user)
    {
        cout<<"Hoeme Screen. > Login. > Admin.\n\n"<<endl;
        cout<<"1.Add Room.\n2.Remove Room\n3.Reserve Room.\n4.Cancle Room.\n5.Display Rooms.\n6.Display Reserved Time Slots.\n7.Return To Home Screen.\n\nEntre Your Choice:"<<endl;
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
                    main_menu(rooms);
                }
                break;

            case 2:
                removeRoom(rooms);
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;

            case 3:
                reserveRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;

            case 4:
                cancleRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;

            case 5:
                displayRooms(rooms);
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;

            case 6:
                displayTimeSlots();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;
            case 7:
                if (choice_menue==7)
                {
                    // home_screen(use_pass);
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
        cout<<"1.Reserve Room.\n2.Cancle Room.\n3.Display Rooms.\n4.Display Reserved Time Slots.\n5.Return To Home Screen.\n\nEntre Your Choice:"<<endl;
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
                    main_menu(rooms);
                }
                break;

            case 2:
                cancleRoom();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;

            case 3:
                displayRooms(rooms);
                
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                

                break;

            case 4:
                displayTimeSlots();
                cout<<"\nEntre 1 for Home Screen:";
                cin>>exit;
                if (exit)
                {
                    main_menu(rooms);
                }
                break;
            case 5:
                if (choice_menue==5)
                {
                    // home_screen(use_pass);
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
    while (1)
    {
        home_screen(use_pass);
        main_menu(rooms);
    }
    
    
    
    
    return 0;
}
