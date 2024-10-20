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
bool current_user; // Tracks if the current user is an admin
string name_current_user; // Stores the username of the current user
// Predefined user credentials for login
vector<vector<string>> use_pass = {{"admin", "admin@123"}}; 
int flag = 0; // Flag for control flow
// List of available rooms
vector<string> rooms = {"LHC_CR-211.", "Academic_Building-1.", "Academic_Building-2.", "Central_Library_TC-1."};
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
             << res.roomName << "\t\t"
             << res.startTime << "\t\t\t\t"
             << res.endTime << "\t\t\t\t"
             << res.date << endl;
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

    if (username == "admin") {
        current_user = true; // Set as admin user
    } else {
        current_user = false; // Set as normal user
    }

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
    cout << "This is a Conference Hall Booking Individual Project For Engineering And Design Course.\nName: Atharva Bhosale.\nRoll No: ME24B005.\n\n";
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

// Function to add new rooms
void addRoom(vector<string>& rooms) {
    clearScreen();
    // Display user type
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Add Rooms.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Add Rooms.\n\n";
    }
    int no_room_add; // Number of rooms to add
    string new_room; // Variable to hold new room name
    cout << "Enter Number Of Rooms To Add: ";
    cin >> no_room_add; // Get number of rooms
    cout << "Enter Name Of Rooms Separated By Spaces: ";
    while (no_room_add--) {
        cin >> new_room; // Get room names
        rooms.push_back(new_room); // Add to rooms vector
    }
}

// Function to display all rooms
void displayRooms(vector<string>& rooms) {
    clearScreen();
    // Display user type
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Display Rooms.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Display Rooms.\n\n";
    }
    int counter = 1;
    for (const auto& room : rooms) {
        cout << counter << "." << room << endl; // Print room names
        counter++;
    }
}

// Function to remove existing rooms
void removeRoom(vector<string>& rooms) {
    clearScreen();
    // Display user type
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Remove Rooms.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Remove Rooms.\n\n";
    }
    displayRooms(rooms); // Show current rooms
    int no_room_remove; // Number of rooms to remove
    string remove_room; // Room name to remove
    cout << "\nEnter Number Of Rooms To Remove: " << endl;
    cin >> no_room_remove; // Get number of rooms to remove
    
    while (no_room_remove--) {
        cout << "Enter Which Room To Remove: ";
        cin >> remove_room; // Get room name to remove
        auto remov = find(rooms.begin(), rooms.end(), remove_room); // Find the room
        rooms.erase(remov); // Remove the room from the list
    }
}

// Function to reserve a room
void reserveRoom() {
    clearScreen();
    // Display user type
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Reserve Room.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Reserve Room.\n\n";
    }
    for (int i = 1; i <= rooms.size(); i++) {
        cout << i << "." << rooms[i - 1] << endl; // Display available rooms
    }
    
    print_data(reservations); // Show existing reservations
    Reservation newReservation; // Create a new reservation
    newReservation.userName = name_current_user; // Set the username
    newReservation.sr = reservations.size() + 1; // Set serial number
    cout << "Enter Room Name (Replace ' ' with '_'): ";
    cin >> newReservation.roomName; // Get room name
    cout << "Enter Start Time (24 hrs format): ";
    cin >> newReservation.startTime; // Get start time
    cout << "Enter End Time (24 hrs format): ";
    cin >> newReservation.endTime; // Get end time
    cout << "Enter Date (DD-MM-YYYY): ";
    cin >> newReservation.date; // Get reservation date

    reservations.push_back(newReservation); // Add reservation to list
}

// Function to cancel a room reservation
void cancleRoom() {
    clearScreen();
    // Display user type
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Cancel Room.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Cancel Room.\n\n";
    }
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
    if (current_user) {
        cout << "Home Screen. > Login. > Admin. > Display Reserved Time Slots.\n\n";
    } else {
        cout << "Home Screen. > Login. > Normal User. > Display Reserved Time Slots.\n\n";
    }
    print_data(reservations); // Show all reservations
}

// Main menu function for logged in users
void main_menu(vector<string>& rooms) {
    clearScreen();
    int exit; // Variable to control exiting to home screen
    int choice_menue; // Variable for user choice
    if (current_user) {
        cout << "Home Screen. > Login. > Admin.\n\n" << endl;
        cout << "1. Add Room.\n2. Remove Room\n3. Reserve Room.\n4. Cancel Room.\n5. Display Rooms.\n6. Display Reserved Time Slots.\n7. Return To Home Screen.\n\nEnter Your Choice:" << endl;
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
                    if (choice_menue == 7) {
                        // home_screen(use_pass); // Uncomment to return to home screen
                    }
                    break;

                default:
                    cout << "Invalid choice. Try again." << endl;
                    flag = 1; // Set flag to indicate an error
            }
        } while (flag); // Loop until a valid choice is made

    } else {
        cout << "Home Screen. > Login. > Normal User.\n\n" << endl;
        cout << "1. Reserve Room.\n2. Cancel Room.\n3. Display Rooms.\n4. Display Reserved Time Slots.\n5. Return To Home Screen.\n\nEnter Your Choice:" << endl;
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
                    if (choice_menue == 5) {
                        // home_screen(use_pass); // Uncomment to return to home screen
                    }
                    break;
                default:
                    cout << "Invalid choice. Try again." << endl;
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

    return 0; // End of program
}
