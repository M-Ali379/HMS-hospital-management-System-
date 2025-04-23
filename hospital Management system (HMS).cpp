#include<iostream>
#include<string>

using namespace std;

class Person {
public:
    string name;
    int age;

    Person(string name = "", int age = 0) : name(name), age(age) {}

    string getName()
	 {
        return name;
    }

    int getAge()
	 {
        return age;
    }

    void setName(string newName)
	 {
        name = newName;
    }

    void setAge(int newAge) 
	{
        age = newAge;
    }
};

class Doctor : public Person
 {
public:
    string slots[6];

    Doctor(string name = "", int age = 0) : Person(name, age) 
	{
        for (int i = 0; i < 6; ++i)
		 {
            slots[i] = "Open";
        }
    }

    void displaySlots() {
        cout << "Doctor " << name << " slots: ";
        for (int i = 0; i < 6; ++i) 
		{
            cout << (i + 1) << "(" << slots[i] << ") ";
        }
        cout << endl;
    }

    bool bookSlot(int slot)
	 {
        if (slot < 1 || slot > 6) return false;
        if (slots[slot - 1] == "Open") {
            slots[slot - 1] = "Booked";
            return true;
        }
        return false;
    }

    bool cancelSlot(int slot) {
        if (slot < 1 || slot > 6) return false;
        if (slots[slot - 1] == "Booked") {
            slots[slot - 1] = "Open";
            return true;
        }
        return false;
    }
};

class Nurse : public Person 
{
public:
    bool isAvailable;

    Nurse(string name = "", int age = 0) : Person(name, age), isAvailable(true) {}

    bool allocate() 
	{
        if (isAvailable)
		 {
            isAvailable = false;
            return true;
        }
        return false;
    }

    void deallocate() {
        isAvailable = true;
    }
};

class Patient : public Person {
public:
    int patientID;
    bool emergencyStatus;

    Patient(string name = "", int age = 0, int id = 0, bool e = false) : Person(name, age), patientID(id), emergencyStatus(e) {}

    int getPatientID() { return patientID; }
    void setPatientID(int id) { patientID = id; }
    bool isEmergency() { return emergencyStatus; }
    void setEmergencyStatus(bool e) { emergencyStatus = e; }
};

class Billing {
public:
    int patientID;
    double charges;
    double payments;

    Billing(int id = 0, double c = 0.0, double p = 0.0) : patientID(id), charges(c), payments(p) {}

    void addCharge(double amount) { charges += amount; }
    void makePayment(double amount) { payments += amount; }
    double calculateBalance() { return charges - payments; }

    void displayBill()
	 {
        cout << "Bill for patient ID " << patientID << ":\n";
        cout << "Total Charges: " << charges << "\n";
        cout << "Total Payments: " << payments << "\n";
        cout << "Balance: " << calculateBalance() << "\n";
    }
};

class AppointmentSystem
 {
    Doctor doctors[3];
    Nurse nurses[2];
    Patient patients[2];
    Billing bills[10];
    int billCount;

public:
    AppointmentSystem() : billCount(0)
	 {
        doctors[0] = Doctor("Dr. Ali", 45);
        doctors[1] = Doctor("Dr. Hanan", 50);
        doctors[2] = Doctor("Dr. Abdullah", 40);
        nurses[0] = Nurse("Nurse A", 30);
        nurses[1] = Nurse("Nurse B", 28);
        patients[0] = Patient("rihana", 30, 1001, false);
        patients[1] = Patient("farzana", 25, 1002, true);
    }

    void bookAppointment()
	 {
        int docIndex, slot;
        cout << "Select Doctor (0-2): ";
        cin >> docIndex;
        if (docIndex < 0 || docIndex >= 3) 
		{
            cout << "Invalid Doctor Index. Try again." << endl;
            return;
        }
        doctors[docIndex].displaySlots();
        cout << "Select Slot (1-6): ";
        cin >> slot;
        if (doctors[docIndex].bookSlot(slot))
		 {
            cout << "Appointment Booked with " << doctors[docIndex].name << " at Slot " << slot << "." << endl;
        }
		 else
		  {
            cout << "Slot Occupied or Invalid. Try again." << endl;
        }
    }

    void cancelAppointment()
	 {
        int docIndex, slot;
        cout << "Select Doctor (0-2): ";
        cin >> docIndex;
        if (docIndex < 0 || docIndex >= 3) {
            cout << "Invalid Doctor Index. Try again." << endl;
            return;
        }
        doctors[docIndex].displaySlots();
        cout << "Select Slot to cancel (1-6): ";
        cin >> slot;
        if (doctors[docIndex].cancelSlot(slot)) 
		{
            cout << "Appointment with " << doctors[docIndex].name << " at Slot " << slot << " has been cancelled." << endl;
        }
		 else 
		{
            cout << "No appointment found at this slot. Try again." << endl;
        }
    }

    void displayStatus()
	 {
        cout << "\n--- Doctors Status ---" << endl;
        for (int i = 0; i < 3; ++i) 
		{
            doctors[i].displaySlots();
        }

        cout << "\n--- Nurses Status ---" << endl;
        for (int i = 0; i < 2; ++i) 
		{
            cout << nurses[i].name << ": " << (nurses[i].isAvailable ? "Available" : "Not Available") << endl;
        }

        cout << "\n--- Patients Status ---" << endl;
        for (int i = 0; i < 2; ++i) 
		{
            cout << "Patient ID: " << patients[i].getPatientID() << ", Name: " << patients[i].getName() << ", Emergency: " << (patients[i].isEmergency() ? "Yes" : "No") << endl;
        }
    }

    void generateBill(int patientID, double charge)
	 {
        for (int i = 0; i < billCount; ++i)
		 {
            if (bills[i].patientID == patientID)
			 {
                bills[i].addCharge(charge);
                return;
            }
        }
        if (billCount < 10) 
		{
            bills[billCount] = Billing(patientID, charge, 0.0);
            billCount++;
        } 
		else
		 {
            cout << "Billing system is full. Cannot add more bills." << endl;
        }
    }

    void handleEmergency(int patientID) 
	{
        for (int i = 0; i < 2; ++i) 
		{
            if (patients[i].getPatientID() == patientID)
			 {
                patients[i].setEmergencyStatus(true);
                cout << "Emergency for Patient ID " << patientID << " handled." << endl;
                return;
            }
        }
        cout << "Patient ID not found." << endl;
    }

    void displayAllBills() 
	{
        for (int i = 0; i < billCount; ++i) 
		{
            bills[i].displayBill();
        }
    }

    void menu() 
	{
        int choice;
        while (true)
		 {
            cout << "\n--- Appointment System Menu ---" << endl;
            cout << "1. Book Appointment" << endl;
            cout << "2. Cancel Appointment" << endl;
            cout << "3. Display Status" << endl;
            cout << "4. Generate Bill" << endl;
            cout << "5. Handle Emergency" << endl;
            cout << "6. Display All Bills" << endl;
            cout << "7. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
			 {
                case 1: bookAppointment(); break;
                case 2: cancelAppointment(); break;
                case 3: displayStatus(); break;
                case 4: {
                    int patientID;
                    double charge;
                    cout << "Enter Patient ID: ";
                    cin >> patientID;
                    cout << "Enter Charge: ";
                    cin >> charge;
                    generateBill(patientID, charge);
                    break;
                }
                case 5: {
                    int patientID;
                    cout << "Enter Patient ID: ";
                    cin >> patientID;
                    handleEmergency(patientID);
                    break;
                }
                case 6: displayAllBills(); break;
                case 7: return;
                default: cout << "Invalid choice. Try again." << endl;
            }
        }
    }
};

int main()
 {
    AppointmentSystem system;
    system.menu();
    return 0;
}