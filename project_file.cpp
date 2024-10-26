#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

// Function to clear the console screen
void clearScreen() {
    this_thread::sleep_for(chrono::seconds(1)); // Delay of 1 second
#ifdef _WIN32
    system("CLS"); // Windows command to clear screen
#else
    system("clear"); // Unix/Linux command to clear screen
#endif
}

// Variables And Data Storage
string name_current_user; // Stores the username of the current user
// Predefined user credentials for login
vector<vector<string>> use_pass = {{"admin", "admin@123"},{"demo_user","demo_user"}}; 
int flag = 0; // Flag for control flow
// List of available rooms
vector<string> rooms = {"lhc", "ab-1", "ab-2", "tc-1"};
vector<int> time_slots; // Time slots for reservations
    
// Structure to store reservation details
struct Reservation {
    int sr; // Serial number of the reservation
    string userName; // Username of the person making the reservation
    string roomName; // Name of the room reserved
    int startTime; // Start time of the reservation
    int endTime; // End time of the reservation
    string date; // Date of the reservation
};

// Vector to store all reservations
vector<Reservation> reservations;

// Function to print all reservations
void print_data(const vector<Reservation>& reservations) {
    cout << "Sr No.\tUsername\tRoom Name\tStart Time (24 hrs format)\tEnd Time (24 hrs format)\tDate" << endl;
    for (const auto& res : reservations) {
        cout << res.sr << "\t"
             << res.userName << "\t\t"
             << res.roomName << ".\t\t"
             << res.startTime << "\t\t\t\t"
             << res.endTime << "\t\t\t\t"
             << res.date << endl;
    }
}

// Function to display all rooms
void displayRooms(vector<string>& rooms) {
    clearScreen();
    // Display user type
    cout << "Home Screen. > Login. > "<<name_current_user<<". "<<" > Display Rooms Available.\n\n";
    int counter = 1;
    for (const auto& room : rooms) {
        cout << counter << "." << room << endl; // Print room names
        counter++;
    }
}
// Function for user sign up
void sign_up(vector<vector<string>>& use_pass) {
    clearScreen();
    cout << "Home Screen. > Sign Up.\n\n";
    string username, password;
    cout << "Enter Your Username: ";
    cin >> username; // Get username
    cout << "Enter Your Password: ";
    cin >> password; // Get password
    use_pass.push_back({username, password}); // Store new credentials
}

// Function for user login
void login(const vector<vector<string>>& use_pass) {
    clearScreen();
    cout << "Home Screen. > Login.\n\n";
    string username, password;
    cout << "Enter Your Username: ";
    cin >> username; // Get username
    cout << "Enter Your Password: ";
    cin >> password; // Get password

    bool found = false;
    for (const auto& entry : use_pass) {
        // Check if credentials match
        if (entry[0] == username && entry[1] == password) {
            found = true;
            break;
        }
    }

    if (found) {
        name_current_user = username; // Store current username
        cout << "Login successful!" << endl;
    } else {
        cout << "Login failed. Try again." << endl;
        login(use_pass); // Retry login
    }
}

// Function to display the home screen
void home_screen(vector<vector<string>>& use_pass) {
    int choice_login; // Variable to store user choice
    clearScreen();
    cout << "Welcome To Indian Institute Of Technology Tirupati!!!\n\n";
    cout << "This is a Conference Hall Booking Group Project For Engineering And Design Course.\nName & Roll No: Anushree (CH24B005), Tirza (CE24B006), AtharvaB (ME24B005), Varshith (CS24B006), Arnav (EE24B005), Yash (EE24B060).\n\n";
    cout << "Home Screen.\n\n";
    cout << "1. Sign Up.\n2. Login.\nEnter your choice: ";
    cin >> choice_login; // Get user choice

    switch (choice_login) {
        case 1:
            sign_up(use_pass); // Call sign up function
            home_screen(use_pass); // Go back to home screen
            break;

        case 2:
            login(use_pass); // Call login function
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
            exit(0); // Exit on invalid choice
    }
}
//Function to change string in lowercase.
void toLowerCase(string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}
// Function to add new rooms
void addRoom(vector<string>& rooms) {
    clearScreen();
    // Display user type
    cout << "Home Screen. > Login. > "<<name_current_user<<". "<<" > Add Room.\n\n";
    int no_room_add; // Number of rooms to add
    string new_room; // Variable to hold new room name
    int counter=1;
    for (const auto& room_name:rooms)
    {
        cout<<counter<<"."<<room_name<<endl;
        counter++;
    }
    counter=1;
    cout << "Enter No_Of_Rooms_To_Add Names(Separated By ' '): ";
    cin >> no_room_add; // Get number of rooms
    while (no_room_add--) {
        cin >> new_room; // Get room names
        toLowerCase(new_room);
        rooms.push_back(new_room); // Add to rooms vector
    }
    for (const auto& room_name:rooms)
    {
        cout<<counter<<"."<<room_name<<endl;
        counter++;
    }
    
    
}



// Function to remove existing rooms
void removeRoom(vector<string>& rooms) {
    clearScreen();
    // Display user type
    cout << "Home Screen. > Login. > "<<name_current_user<<". "<<"Display Reserved Time Slots.\n\n";
    displayRooms(rooms); // Show current rooms
    int no_room_remove; // Number of rooms to remove
    string remove_room; // Room name to remove
    cout << "\nEnter No_Of_Rooms Name(Separated By ' '): " << endl;
    cin >> no_room_remove; // Get number of rooms to remove
    
    while (no_room_remove--) {
        cin >> remove_room; // Get room name to remove
        auto remov = find(rooms.begin(), rooms.end(), remove_room); // Find the room
        rooms.erase(remov); // Remove the room from the list
    }
}
int inputcheck(int num,string timecheck){
    while (1)
    {
        cout<<"Entre Time between 0-24 (both including.) "<<timecheck<<":";
        cin>>num;
        if(num>=0 && num<25){
            break;
        }
    }
    return num;
    
}

// Function to reserve a room
void reserveRoom() {
    clearScreen();
    // Display user type
    cout << "Home Screen. > Login. > "<<name_current_user<<". "<<"> Reserve Room.\n\n";
    for (int i = 1; i <= rooms.size(); i++) {
        cout << i << "." << rooms[i - 1] << endl; // Display available rooms
    }
    
    print_data(reservations); // Show existing reservations
    Reservation newReservation; // Create a new reservation
    newReservation.userName = name_current_user; // Set the username
    newReservation.sr = reservations.size() + 1; // Set serial number
    cout << "Enter 'Room_Name Start_Time End_Time Date(DD-MM-YY): ";
    cin >> newReservation.roomName; // Get room name
    toLowerCase(newReservation.roomName);
    cin >> newReservation.startTime; // Get start time
    cin >> newReservation.endTime; // Get end time
    cin >> newReservation.date; // Get reservation date
    while (1)
    {
        if(newReservation.date.length()!=8){
        cout<<"Entre the date again:";
        cin>>newReservation.date;
        }else
        {
            break;
        }
        
    }
    
    
    //Time Check
    if (!(newReservation.startTime>=0 &&newReservation.startTime<25))
    {
        newReservation.startTime=inputcheck(newReservation.startTime,"Start Time");
    }
    if (!(newReservation.endTime>=0 &&newReservation.endTime<25))
    {
        newReservation.endTime=inputcheck(newReservation.endTime,"End Time");
    }

    if (newReservation.startTime > newReservation.endTime)
    {
        newReservation.startTime=inputcheck(newReservation.startTime,"Start Time");   
    }
    
    

    reservations.push_back(newReservation); // Add reservation to list
}

// Function to cancel a room reservation
void cancleRoom() {
    clearScreen();
    // Display user type
    cout << "Home Screen. > Login. > "<<name_current_user<<". "<<"Display Reserved Time Slots.\n\n";
    print_data(reservations); // Show current reservations
    int cancle; // Serial number to cancel
    cout << "\n\nEnter Sr No To Cancel Reservation: ";
    cin >> cancle; // Get serial number
    auto it1 = find_if(reservations.begin(), reservations.end(), [cancle](const Reservation& res) { return res.sr == cancle; }); // Find reservation
    if (it1 != reservations.end()) {
        reservations.erase(it1); // Remove reservation
    }
    // Update serial numbers after cancellation
    for (int i = 1; i <= reservations.size(); i++) {
        reservations[i - 1].sr = i; // Reassign serial numbers
    }
    cout << "\n\n";
    print_data(reservations); // Show updated reservations
}

// Function to display all reserved time slots
void displayTimeSlots() {
    clearScreen();
    // Display user type
    cout << "Home Screen. > Login. > "<<name_current_user<<". "<<"Display Reserved Time Slots.\n\n";
    print_data(reservations); // Show all reservations
}

// Main menu function for logged in users
void main_menu(vector<string>& rooms) {
    clearScreen();
    int exit; // Variable to control exiting to home screen
    int choice_menue; // Variable for user choice
    if (name_current_user=="admin") {
        cout << "Home Screen. > Login. > "<<name_current_user<<".\n\n" << endl;
        cout << "1. Add Room.\n2. Remove Room\n3. Reserve Room.\n4. Cancel Room.\n5. Display Rooms.\n6. Display Reserved Time Slots.\n7. Return To Home Screen.\n\nEnter Your Choice:";
        cin >> choice_menue; // Get user choice
        do {
            switch (choice_menue) {
                case 1:
                    addRoom(rooms); // Call add room function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 2:
                    removeRoom(rooms); // Call remove room function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 3:
                    reserveRoom(); // Call reserve room function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 4:
                    cancleRoom(); // Call cancel room function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 5:
                    displayRooms(rooms); // Call display rooms function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 6:
                    displayTimeSlots(); // Call display time slots function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 7:
                    break;

                default:
                    cout << "Invalid choice. Try again." << endl;
                    break;
                    flag = 1; // Set flag to indicate an error
            }
        } while (flag); // Loop until a valid choice is made

    } else {
        cout << "Home Screen. > Login. > "<<name_current_user<<".\n\n" << endl;
        cout << "1. Reserve Room.\n2. Cancel Room.\n3. Display Rooms.\n4. Display Reserved Time Slots.\n5. Return To Home Screen.\n\nEnter Your Choice:";
        cin >> choice_menue; // Get user choice
        do {
            switch (choice_menue) {
                case 1:
                    reserveRoom(); // Call reserve room function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 2:
                    cancleRoom(); // Call cancel room function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 3:
                    displayRooms(rooms); // Call display rooms function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;

                case 4:
                    displayTimeSlots(); // Call display time slots function
                    cout << "\nEnter 1 for Home Screen:";
                    cin >> exit; // Check for exit
                    if (exit) {
                        main_menu(rooms); // Go back to main menu
                    }
                    break;
                case 5:
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
                    break;
                    flag = 1; // Set flag to indicate an error
            }
        } while (flag); // Loop until a valid choice is made
    }
}

// Main function
int main() {
    while (1) {
        home_screen(use_pass); // Display home screen
        main_menu(rooms); // Display main menu
    }

    return 0;
}
