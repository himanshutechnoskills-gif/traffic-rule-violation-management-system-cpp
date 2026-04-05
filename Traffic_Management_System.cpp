#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Vehicle {
protected:
    string type;
    string numberPlate;
    int speedLimit;
    int speedFine;
    int noiseFine;
    int footpathFine;
    int drunkFine;
    int docFine;
    int actualSpeed;
    bool speedFined;
    bool noiseFined;
    bool footpathCrossed;
    bool drunkDriving;
    bool docViolation;

public:
    Vehicle(string t, int limit, int sFine, int nFine, int fFine, int dFine, int docFine) {
        this->type = t;
        this->speedLimit = limit;
        this->speedFine = sFine;
        this->noiseFine = nFine;
        this->footpathFine = fFine;
        this->drunkFine = dFine;
        this->docFine = docFine;
        this->actualSpeed = 0;
        this->speedFined = false;
        this->noiseFined = false;
        this->footpathCrossed = false;
        this->drunkDriving = false;
        this->docViolation = false;
    }

    void setNumberPlate(string plate) { numberPlate = plate; }
    string getType() const { return type; }
    string getNumberPlate() const { return numberPlate; }
    int getSpeedLimit() const { return speedLimit; }
    int getSpeedFine() const { return speedFine; }
    int getNoiseFine() const { return noiseFine; }
    int getFootpathFine() const { return footpathFine; }
    int getDrunkFine() const { return drunkFine; }
    int getDocFine() const { return docFine; }

    void setSpeed(int speed) {
        actualSpeed = speed;
        if (actualSpeed > speedLimit) {
            speedFined = true;
        }
    }
    void setNoiseViolation() { noiseFined = true; }
    void setFootpathCrossed() { footpathCrossed = true; }
    void setDrunkDriving() { drunkDriving = true; }
    void setDocViolation() { docViolation = true; }

    // NEW setter functions to modify fines
    void setSpeedFine(int fine) { speedFine = fine; }
    void setNoiseFine(int fine) { noiseFine = fine; }
    void setFootpathFine(int fine) { footpathFine = fine; }
    void setDrunkFine(int fine) { drunkFine = fine; }
    void setDocFine(int fine) { docFine = fine; }

    void displaySpeedFine() const {
        if (speedFined) {
            cout << type << " | Plate: " << numberPlate << " | Speed: " << actualSpeed << " | Fine: $" << speedFine << endl;
        }
    }
    void displayNoiseFine() const {
        if (noiseFined) {
            cout << type << " | Plate: " << numberPlate << " | Fine: $" << noiseFine << endl;
        }
    }
    void displayFootpathFine() const {
        if (footpathCrossed) {
            cout << type << " | Plate: " << numberPlate << " | Fine: $" << footpathFine << endl;
        }
    }
    void displayDrunkFine() const {
        if (drunkDriving) {
            cout << type << " | Plate: " << numberPlate << " | Fine: $" << drunkFine << endl;
        }
    }
    void displayDocFine() const {
        if (docViolation) {
            cout << type << " | Plate: " << numberPlate << " | Fine: $" << docFine << endl;
        }
    }
};

class Car : public Vehicle {
public:
    Car() : Vehicle("Car", 100, 200, 150, 500, 1000, 300) {}
};

class Bike : public Vehicle {
public:
    Bike() : Vehicle("Bike", 80, 100, 80, 300, 600, 150) {}
};

class Truck : public Vehicle {
public:
    Truck() : Vehicle("Truck", 70, 300, 400, 700, 1500, 500) {}
};

class Bus : public Vehicle {
public:
    Bus() : Vehicle("Bus", 90, 250, 300, 600, 1200, 400) {}
};

Vehicle* createVehicle(int type) {
    switch (type) {
        case 1: return new Car();
        case 2: return new Bike();
        case 3: return new Truck();
        case 4: return new Bus();
        default: return nullptr;
    }
}

void showFineTable(const string& title, const string& column, const vector<Vehicle*>& types) {
    cout << "\n----- " << title << " Fine Table -----\n";
    cout << left << setw(10) << "Vehicle" << setw(20) << column << "Fine\n";
    cout << "---------------------------------------------\n";
    for (auto v : types) {
        cout << left << setw(10) << v->getType()
             << setw(20) << (column == "Speed Limit" ? to_string(v->getSpeedLimit()) : "")
             << "$" << (column == "Speed Limit" ? v->getSpeedFine() :
                       column == "Noise Pollution" ? v->getNoiseFine() :
                       column == "Footpath Violation" ? v->getFootpathFine() :
                       column == "Drunk Driving Violation" ? v->getDrunkFine() :
                       v->getDocFine()) << endl;
    }
    cout << "---------------------------------------------\n";
}

void displayRecords(const vector<Vehicle*>& records) {
    int choice;
    cout << "\nWhich fine records would you like to see?\n";
    cout << "1. Speed Limit Fines\n2. Noise Pollution Fines\n3. Footpath Violation Fines\n4. Drunk Driving Fines\n5. Document Violation Fines\nYour Choice: ";
    cin >> choice;
    cout << "\n---- RECORDS ----\n";
    for (auto v : records) {
        if (choice == 1) v->displaySpeedFine();
        else if (choice == 2) v->displayNoiseFine();
        else if (choice == 3) v->displayFootpathFine();
        else if (choice == 4) v->displayDrunkFine();
        else if (choice == 5) v->displayDocFine();
    }
    cout << "-----------------\n";
}

void deleteRecord(vector<Vehicle*>& records) {
    string plate;
    cout << "Enter the number plate of the vehicle to delete: ";
    cin >> plate;

    bool found = false;
    for (auto it = records.begin(); it != records.end(); ++it) {
        if ((*it)->getNumberPlate() == plate) {
            delete *it;
            records.erase(it);
            found = true;
            cout << "Record deleted successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "No matching record found to delete.\n";
    }
}

void modifyRecord(vector<Vehicle*>& records) {
    int choice;
    cout << "\nWhich fine record would you like to modify?\n";
    cout << "1. Speed Limit Fines\n2. Noise Pollution Fines\n3. Footpath Violation Fines\n4. Drunk Driving Fines\n5. Document Violation Fines\nYour Choice: ";
    cin >> choice;

    string plate;
    cout << "Enter the number plate of the vehicle you want to modify: ";
    cin >> plate;

    bool found = false;
    for (auto v : records) {
        if (v->getNumberPlate() == plate) {
            found = true;
            cout << "Record found!\n";

            cout << "Enter new number plate (or enter same if no change): ";
            string newPlate;
            cin >> newPlate;
            v->setNumberPlate(newPlate);

            if (choice == 1) {
                int newSpeed, newFine;
                cout << "Enter new actual speed: ";
                cin >> newSpeed;
                v->setSpeed(newSpeed);
                cout << "Enter new fine for speeding: ";
                cin >> newFine;
                v->setSpeedFine(newFine);
            } else if (choice == 2) {
                v->setNoiseViolation();
                int newFine;
                cout << "Enter new fine for noise pollution: ";
                cin >> newFine;
                v->setNoiseFine(newFine);
            } else if (choice == 3) {
                v->setFootpathCrossed();
                int newFine;
                cout << "Enter new fine for footpath violation: ";
                cin >> newFine;
                v->setFootpathFine(newFine);
            } else if (choice == 4) {
                v->setDrunkDriving();
                int newFine;
                cout << "Enter new fine for drunk driving: ";
                cin >> newFine;
                v->setDrunkFine(newFine);
            } else if (choice == 5) {
                v->setDocViolation();
                int newFine;
                cout << "Enter new fine for document violation: ";
                cin >> newFine;
                v->setDocFine(newFine);
            }

            cout << "Record modified successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "No matching record found.\n";
    }
}

int main() {
    vector<Vehicle*> records;
    vector<Vehicle*> types = {new Car(), new Bike(), new Truck(), new Bus()};

    cout << "-------------------------------------------\n";
    cout << " Welcome to the Traffic Rule Violation App \n";
    cout << "-------------------------------------------\n";

    while (true) {
        cout << "\nPlease select an option:\n";
        cout << "1. Add Speed Limit Violation\n";
        cout << "2. Add Noise Pollution Violation\n";
        cout << "3. Add Footpath Violation\n";
        cout << "4. Add Drunk Driving Violation\n";
        cout << "5. Add Document Verification Violation\n";
        cout << "6. Display All Records\n";
        cout << "7. Modify a Record\n";
        cout << "8. Delete a Record\n";
        cout << "9. Exit the System\n";
        cout << "Your Choice: ";

        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            if (choice == 1) showFineTable("Speed Limit", "Speed Limit", types);
            else if (choice == 2) showFineTable("Noise Pollution", "Noise Pollution", types);
            else if (choice == 3) showFineTable("Footpath Violation", "Footpath Violation", types);
            else if (choice == 4) showFineTable("Drunk Driving", "Drunk Driving Violation", types);

            int vtype;
            cout << "\nEnter vehicle type (1. Car, 2. Bike, 3. Truck, 4. Bus): ";
            cin >> vtype;

            Vehicle* v = createVehicle(vtype);
            if (!v) {
                cout << "Invalid vehicle type selected.\n";
                continue;
            }

            string plate;
            cout << "Enter vehicle number plate: ";
            cin >> plate;
            v->setNumberPlate(plate);

            if (choice == 1) {
                int speed;
                cout << "Enter actual speed: ";
                cin >> speed;
                v->setSpeed(speed);
            } else if (choice == 2) {
                v->setNoiseViolation();
            } else if (choice == 3) {
                v->setFootpathCrossed();
            } else if (choice == 4) {
                v->setDrunkDriving();
            }

            records.push_back(v);
            cout << "Record added successfully!\n";

        } else if (choice == 5) {
            showFineTable("Document Verification", "Document Verification Violation", types);
            int vtype;
            cout << "\nEnter vehicle type (1. Car, 2. Bike, 3. Truck, 4. Bus): ";
            cin >> vtype;

            Vehicle* v = createVehicle(vtype);
            if (!v) {
                cout << "Invalid vehicle type selected.\n";
                continue;
            }

            string plate;
            cout << "Enter vehicle number plate: ";
            cin >> plate;
            v->setNumberPlate(plate);
            v->setDocViolation();
            records.push_back(v);
            cout << "Record added for document verification violation!\n";

        } else if (choice == 6) {
            displayRecords(records);

        } else if (choice == 7) {
            modifyRecord(records);

        } else if (choice == 8) {
            deleteRecord(records);

        } else if (choice == 9) {
            cout << "Exiting system. Stay safe on the road!\n";
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    for (auto v : records) delete v;
    for (auto t : types) delete t;
    return 0;
}