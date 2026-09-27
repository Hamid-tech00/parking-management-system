#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_SLOTS = 5;
const double PER_HOUR_RATE = 2.0;

class ParkingSystem {
private:
    string numberPlate[MAX_SLOTS];
    int entryTime[MAX_SLOTS];
    bool isOccupied[MAX_SLOTS];
    int totalVehicles;
    double totalRevenue;

public:
    ParkingSystem() {
        totalVehicles = 0;
        totalRevenue = 0.0;
        for (int i = 0; i < MAX_SLOTS; i++) {
            isOccupied[i] = false;
        }
    }

    bool isValidTime(int time) {
        return (time >= 0 && time < 2400 && time % 100 < 60);
    }

    void parkVehicle() {
        if (totalVehicles >= MAX_SLOTS) {
            cout << "Parking is full." << endl;
            return;
        }
        string plate;
        int time;
        cout << "Enter vehicle number plate: ";
        cin >> plate;
        cout << "Enter entry time (HHMM): ";
        cin >> time;
        while (!isValidTime(time)) {
            cout << "Invalid time. Enter entry time (HHMM): ";
            cin >> time;
        }
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (!isOccupied[i]) {
                numberPlate[i] = plate;
                entryTime[i] = time;
                isOccupied[i] = true;
                totalVehicles++;
                cout << "Vehicle parked in slot " << i + 1 << endl;
                return;
            }
        }
    }

    void exitVehicle() {
        string plate;
        int time;
        cout << "Enter vehicle number plate: ";
        cin >> plate;
        cout << "Enter exit time (HHMM): ";
        cin >> time;
        while (!isValidTime(time)) {
            cout << "Invalid time. Enter exit time (HHMM): ";
            cin >> time;
        }
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (isOccupied[i] && numberPlate[i] == plate) {
                int parkedHours = (time - entryTime[i]) / 100;
                double fee = (parkedHours + 1) * PER_HOUR_RATE;
                totalRevenue += fee;
                cout << "Vehicle exited. Parking fee: $" << fixed << setprecision(2) << fee << endl;
                isOccupied[i] = false;
                totalVehicles--;
                return;
            }
        }
        cout << "Vehicle not found." << endl;
    }

    void displayParkedVehicles() {
        cout << "Currently parked vehicles:" << endl;
        for (int i = 0; i < MAX_SLOTS; i++) {
            if (isOccupied[i]) {
                cout << "Slot " << i + 1 << ": " << numberPlate[i] << ", Entry Time: " << entryTime[i] << endl;
            }
        }
    }

    void showStatistics() {
        cout << "Total vehicles parked: " << totalVehicles << endl;
        cout << "Total revenue collected: $" << fixed << setprecision(2) << totalRevenue << endl;
    }
};

int main() {
    ParkingSystem parking;
    int choice;
    do {
        cout << "1. Park a vehicle" << endl;
        cout << "2. Exit a vehicle" << endl;
        cout << "3. Display currently parked vehicles" << endl;
        cout << "4. Show statistics" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: parking.parkVehicle(); break;
            case 2: parking.exitVehicle(); break;
            case 3: parking.displayParkedVehicles(); break;
            case 4: parking.showStatistics(); break;
            case 5: cout << "Exiting program." << endl; break;
            default: cout << "Invalid choice. Please try again." << endl; break;
        }
    } while (choice != 5);
    return 0;
}
