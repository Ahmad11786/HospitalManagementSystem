
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ============================================================
// HOSPITAL MANAGEMENT SYSTEM
// C++ OOP PROJECT - BSCS 3RD SEMESTER
//
// Concepts:
// Classes, Objects, Encapsulation, Inheritance,
// Abstraction, Polymorphism, Virtual Functions,
// Function Overloading, Constructors, Composition,
// Arrays and File Handling
// ============================================================

const int MAX_PATIENTS = 200;
const int MAX_DOCTORS = 100;
const int MAX_APPOINTMENTS = 500;
const int MAX_RECORDS = 500;
const int MAX_BILLS = 500;
const int MAX_ROOMS = 30;

// ============================================================
// INPUT AND DISPLAY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

int getInteger(string message)
{
    int value;

    while (true)
    {
        cout << message;

        if (cin >> value)
        {
            clearInput();
            return value;
        }

        cout << "\nInvalid input! Enter a valid number.\n";
        clearInput();
    }
}

string getText(string message)
{
    string value;

    cout << message;
    getline(cin, value);

    while (value.empty())
    {
        cout << "This field cannot be empty. Try again: ";
        getline(cin, value);
    }

    // Prevent breaking the text-file record format.
    for (int i = 0; i < (int)value.length(); i++)
    {
        if (value[i] == '|')
            value[i] = '/';
    }

    return value;
}

void heading(string title)
{
    cout << "\n";
    cout << "============================================================\n";
    cout << "                 " << title << "\n";
    cout << "============================================================\n";
}

void line()
{
    cout << "------------------------------------------------------------\n";
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.get();
}

// ============================================================
// ABSTRACT PERSON CLASS
// ============================================================

class Person
{
protected:

    string name;
    int age;
    string gender;
    string phone;

public:

    Person()
    {
        name = "";
        age = 0;
        gender = "";
        phone = "";
    }

    Person(string n, int a, string g, string p)
    {
        name = n;
        age = a;
        gender = g;
        phone = p;
    }

    virtual void display() = 0;

    virtual ~Person()
    {
    }
};

// ============================================================
// PATIENT CLASS - INHERITANCE
// ============================================================

class Patient : public Person
{
private:

    int patientID;
    string address;
    string bloodGroup;

public:

    Patient() : Person()
    {
        patientID = 0;
        address = "";
        bloodGroup = "";
    }

    Patient(int id, string n, int a, string g,
            string p, string ad, string bg)
        : Person(n, a, g, p)
    {
        patientID = id;
        address = ad;
        bloodGroup = bg;
    }

    int getID()
    {
        return patientID;
    }

    string getName()
    {
        return name;
    }

    void display() override
    {
        cout << left
             << setw(10) << patientID
             << setw(22) << name.substr(0, 20)
             << setw(8) << age
             << setw(12) << gender
             << setw(15) << phone.substr(0, 13)
             << setw(12) << bloodGroup
             << "\n";
    }

    void save(ofstream &file)
    {
        file << patientID << "|"
             << name << "|"
             << age << "|"
             << gender << "|"
             << phone << "|"
             << address << "|"
             << bloodGroup << "\n";
    }

    void load(string data)
    {
        stringstream ss(data);
        string value;

        getline(ss, value, '|');
        patientID = stoi(value);

        getline(ss, name, '|');

        getline(ss, value, '|');
        age = stoi(value);

        getline(ss, gender, '|');
        getline(ss, phone, '|');
        getline(ss, address, '|');
        getline(ss, bloodGroup, '|');
    }
};

// ============================================================
// DOCTOR CLASS - INHERITANCE
// ============================================================

class Doctor : public Person
{
private:

    int doctorID;
    string specialization;
    double consultationFee;

public:

    Doctor() : Person()
    {
        doctorID = 0;
        specialization = "";
        consultationFee = 0;
    }

    Doctor(int id, string n, int a, string g,
           string p, string s, double fee)
        : Person(n, a, g, p)
    {
        doctorID = id;
        specialization = s;
        consultationFee = fee;
    }

    int getID()
    {
        return doctorID;
    }

    string getName()
    {
        return name;
    }

    string getSpecialization()
    {
        return specialization;
    }

    double getFee()
    {
        return consultationFee;
    }

    void display() override
    {
        cout << left
             << setw(10) << doctorID
             << setw(22) << name.substr(0, 20)
             << setw(22) << specialization.substr(0, 20)
             << setw(8) << age
             << setw(15) << phone.substr(0, 13)
             << "Rs. " << consultationFee
             << "\n";
    }

    void save(ofstream &file)
    {
        file << doctorID << "|"
             << name << "|"
             << age << "|"
             << gender << "|"
             << phone << "|"
             << specialization << "|"
             << consultationFee << "\n";
    }

    void load(string data)
    {
        stringstream ss(data);
        string value;

        getline(ss, value, '|');
        doctorID = stoi(value);

        getline(ss, name, '|');

        getline(ss, value, '|');
        age = stoi(value);

        getline(ss, gender, '|');
        getline(ss, phone, '|');
        getline(ss, specialization, '|');

        getline(ss, value, '|');
        consultationFee = stod(value);
    }
};

// ============================================================
// APPOINTMENT CLASS
// ============================================================

class Appointment
{
private:

    int appointmentID;
    int patientID;
    int doctorID;
    int day;
    string time;
    string status;

public:

    Appointment()
    {
        appointmentID = 0;
        patientID = 0;
        doctorID = 0;
        day = 0;
        time = "";
        status = "";
    }

    Appointment(int id, int pid, int did, int d, string t)
    {
        appointmentID = id;
        patientID = pid;
        doctorID = did;
        day = d;
        time = t;
        status = "Booked";
    }

    int getID()
    {
        return appointmentID;
    }

    int getPatientID()
    {
        return patientID;
    }

    int getDoctorID()
    {
        return doctorID;
    }

    int getDay()
    {
        return day;
    }

    string getTime()
    {
        return time;
    }

    string getStatus()
    {
        return status;
    }

    bool isBooked()
    {
        return status == "Booked";
    }

    void cancel()
    {
        status = "Cancelled";
    }

    void complete()
    {
        status = "Completed";
    }

    void display()
    {
        cout << left
             << setw(10) << appointmentID
             << setw(12) << patientID
             << setw(12) << doctorID
             << setw(12) << day
             << setw(15) << time
             << setw(15) << status
             << "\n";
    }

    void save(ofstream &file)
    {
        file << appointmentID << "|"
             << patientID << "|"
             << doctorID << "|"
             << day << "|"
             << time << "|"
             << status << "\n";
    }

    void load(string data)
    {
        stringstream ss(data);
        string value;

        getline(ss, value, '|');
        appointmentID = stoi(value);

        getline(ss, value, '|');
        patientID = stoi(value);

        getline(ss, value, '|');
        doctorID = stoi(value);

        getline(ss, value, '|');
        day = stoi(value);

        getline(ss, time, '|');
        getline(ss, status, '|');
    }
};

// ============================================================
// MEDICAL RECORD CLASS
// ============================================================

class MedicalRecord
{
private:

    int recordID;
    int patientID;
    int doctorID;
    int day;
    string diagnosis;
    string prescription;

public:

    MedicalRecord()
    {
        recordID = 0;
        patientID = 0;
        doctorID = 0;
        day = 0;
        diagnosis = "";
        prescription = "";
    }

    MedicalRecord(int id, int pid, int did, int d,
                  string diagnosisText, string prescriptionText)
    {
        recordID = id;
        patientID = pid;
        doctorID = did;
        day = d;
        diagnosis = diagnosisText;
        prescription = prescriptionText;
    }

    int getID()
    {
        return recordID;
    }

    int getPatientID()
    {
        return patientID;
    }

    void display()
    {
        cout << "\nRecord ID      : " << recordID;
        cout << "\nPatient ID     : " << patientID;
        cout << "\nDoctor ID      : " << doctorID;
        cout << "\nDay Number     : " << day;
        cout << "\nDiagnosis      : " << diagnosis;
        cout << "\nPrescription   : " << prescription;
        cout << "\n";
    }

    void save(ofstream &file)
    {
        file << recordID << "|"
             << patientID << "|"
             << doctorID << "|"
             << day << "|"
             << diagnosis << "|"
             << prescription << "\n";
    }

    void load(string data)
    {
        stringstream ss(data);
        string value;

        getline(ss, value, '|');
        recordID = stoi(value);

        getline(ss, value, '|');
        patientID = stoi(value);

        getline(ss, value, '|');
        doctorID = stoi(value);

        getline(ss, value, '|');
        day = stoi(value);

        getline(ss, diagnosis, '|');
        getline(ss, prescription, '|');
    }
};

// ============================================================
// BILL CLASS
// ============================================================

class Bill
{
private:

    int billID;
    int patientID;
    double consultationCharge;
    double roomCharge;
    double otherCharges;
    double totalAmount;
    double paidAmount;
    double balance;

public:

    Bill()
    {
        billID = 0;
        patientID = 0;
        consultationCharge = 0;
        roomCharge = 0;
        otherCharges = 0;
        totalAmount = 0;
        paidAmount = 0;
        balance = 0;
    }

    Bill(int id, int pid, double consultation,
         double room, double other)
    {
        billID = id;
        patientID = pid;

        consultationCharge = consultation;
        roomCharge = room;
        otherCharges = other;

        totalAmount = consultation + room + other;
        paidAmount = 0;
        balance = totalAmount;
    }

    int getID()
    {
        return billID;
    }

    int getPatientID()
    {
        return patientID;
    }

    double getTotal()
    {
        return totalAmount;
    }

    double getBalance()
    {
        return balance;
    }

    void makePayment(double amount)
    {
        paidAmount += amount;
        balance = totalAmount - paidAmount;
    }

    void display()
    {
        cout << fixed << setprecision(2);

        cout << "\nBill ID              : " << billID;
        cout << "\nPatient ID           : " << patientID;
        cout << "\nConsultation Charge  : Rs. " << consultationCharge;
        cout << "\nRoom Charge          : Rs. " << roomCharge;
        cout << "\nOther Charges        : Rs. " << otherCharges;
        cout << "\nTotal Amount         : Rs. " << totalAmount;
        cout << "\nPaid Amount          : Rs. " << paidAmount;
        cout << "\nRemaining Balance    : Rs. " << balance;

        if (balance == 0)
            cout << "\nPayment Status       : PAID";
        else
            cout << "\nPayment Status       : PENDING";

        cout << "\n";
    }

    void save(ofstream &file)
    {
        file << billID << "|"
             << patientID << "|"
             << consultationCharge << "|"
             << roomCharge << "|"
             << otherCharges << "|"
             << totalAmount << "|"
             << paidAmount << "|"
             << balance << "\n";
    }

    void load(string data)
    {
        stringstream ss(data);
        string value;

        getline(ss, value, '|');
        billID = stoi(value);

        getline(ss, value, '|');
        patientID = stoi(value);

        getline(ss, value, '|');
        consultationCharge = stod(value);

        getline(ss, value, '|');
        roomCharge = stod(value);

        getline(ss, value, '|');
        otherCharges = stod(value);

        getline(ss, value, '|');
        totalAmount = stod(value);

        getline(ss, value, '|');
        paidAmount = stod(value);

        getline(ss, value, '|');
        balance = stod(value);
    }
};

// ============================================================
// ROOM CLASS
// ============================================================

class Room
{
private:

    int roomNumber;
    string roomType;
    double dailyCharge;
    int patientID;
    bool occupied;

public:

    Room()
    {
        roomNumber = 0;
        roomType = "";
        dailyCharge = 0;
        patientID = 0;
        occupied = false;
    }

    Room(int number, string type, double charge)
    {
        roomNumber = number;
        roomType = type;
        dailyCharge = charge;
        patientID = 0;
        occupied = false;
    }

    int getNumber()
    {
        return roomNumber;
    }

    int getPatientID()
    {
        return patientID;
    }

    bool isOccupied()
    {
        return occupied;
    }

    double getDailyCharge()
    {
        return dailyCharge;
    }

    string getType()
    {
        return roomType;
    }

    void assignPatient(int id)
    {
        patientID = id;
        occupied = true;
    }

    void releaseRoom()
    {
        patientID = 0;
        occupied = false;
    }

    void display()
    {
        cout << left
             << setw(12) << roomNumber
             << setw(18) << roomType
             << setw(18) << dailyCharge
             << setw(15) << patientID
             << setw(15) << (occupied ? "Occupied" : "Available")
             << "\n";
    }

    void save(ofstream &file)
    {
        file << roomNumber << "|"
             << roomType << "|"
             << dailyCharge << "|"
             << patientID << "|"
             << occupied << "\n";
    }

    void load(string data)
    {
        stringstream ss(data);
        string value;

        getline(ss, value, '|');
        roomNumber = stoi(value);

        getline(ss, roomType, '|');

        getline(ss, value, '|');
        dailyCharge = stod(value);

        getline(ss, value, '|');
        patientID = stoi(value);

        getline(ss, value, '|');
        occupied = (value == "1");
    }
};

// ============================================================
// HOSPITAL CLASS - COMPOSITION
// ============================================================

class Hospital
{
private:

    Patient patients[MAX_PATIENTS];
    Doctor doctors[MAX_DOCTORS];
    Appointment appointments[MAX_APPOINTMENTS];
    MedicalRecord records[MAX_RECORDS];
    Bill bills[MAX_BILLS];
    Room rooms[MAX_ROOMS];

    int patientCount;
    int doctorCount;
    int appointmentCount;
    int recordCount;
    int billCount;
    int roomCount;

    // ========================================================
    // SEARCH FUNCTIONS
    // ========================================================

    int findPatient(int id)
    {
        for (int i = 0; i < patientCount; i++)
        {
            if (patients[i].getID() == id)
                return i;
        }

        return -1;
    }

    int findDoctor(int id)
    {
        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].getID() == id)
                return i;
        }

        return -1;
    }

    int findAppointment(int id)
    {
        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].getID() == id)
                return i;
        }

        return -1;
    }

    int findBill(int id)
    {
        for (int i = 0; i < billCount; i++)
        {
            if (bills[i].getID() == id)
                return i;
        }

        return -1;
    }

    int findRoom(int number)
    {
        for (int i = 0; i < roomCount; i++)
        {
            if (rooms[i].getNumber() == number)
                return i;
        }

        return -1;
    }

    bool hasActiveRoom(int patientID)
    {
        for (int i = 0; i < roomCount; i++)
        {
            if (rooms[i].isOccupied() &&
                rooms[i].getPatientID() == patientID)
                return true;
        }

        return false;
    }

    bool hasPendingBill(int patientID)
    {
        for (int i = 0; i < billCount; i++)
        {
            if (bills[i].getPatientID() == patientID &&
                bills[i].getBalance() > 0)
                return true;
        }

        return false;
    }

    // ========================================================
    // ID GENERATION
    // ========================================================

    int nextPatientID()
    {
        int maximum = 1000;

        for (int i = 0; i < patientCount; i++)
        {
            if (patients[i].getID() > maximum)
                maximum = patients[i].getID();
        }

        return maximum + 1;
    }

    int nextDoctorID()
    {
        int maximum = 200;

        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].getID() > maximum)
                maximum = doctors[i].getID();
        }

        return maximum + 1;
    }

    int nextAppointmentID()
    {
        int maximum = 0;

        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].getID() > maximum)
                maximum = appointments[i].getID();
        }

        return maximum + 1;
    }

    int nextRecordID()
    {
        int maximum = 0;

        for (int i = 0; i < recordCount; i++)
        {
            if (records[i].getID() > maximum)
                maximum = records[i].getID();
        }

        return maximum + 1;
    }

    int nextBillID()
    {
        int maximum = 0;

        for (int i = 0; i < billCount; i++)
        {
            if (bills[i].getID() > maximum)
                maximum = bills[i].getID();
        }

        return maximum + 1;
    }

    // ========================================================
    // FILE HANDLING
    // ========================================================

    void savePatients()
    {
        ofstream file("patients.txt");

        for (int i = 0; i < patientCount; i++)
            patients[i].save(file);

        file.close();
    }

    void saveDoctors()
    {
        ofstream file("doctors.txt");

        for (int i = 0; i < doctorCount; i++)
            doctors[i].save(file);

        file.close();
    }

    void saveAppointments()
    {
        ofstream file("appointments.txt");

        for (int i = 0; i < appointmentCount; i++)
            appointments[i].save(file);

        file.close();
    }

    void saveRecords()
    {
        ofstream file("medical_records.txt");

        for (int i = 0; i < recordCount; i++)
            records[i].save(file);

        file.close();
    }

    void saveBills()
    {
        ofstream file("bills.txt");

        for (int i = 0; i < billCount; i++)
            bills[i].save(file);

        file.close();
    }

    void saveRooms()
    {
        ofstream file("rooms.txt");

        for (int i = 0; i < roomCount; i++)
            rooms[i].save(file);

        file.close();
    }

    void saveAll()
    {
        savePatients();
        saveDoctors();
        saveAppointments();
        saveRecords();
        saveBills();
        saveRooms();
    }

    void loadPatients()
    {
        ifstream file("patients.txt");
        string data;

        while (getline(file, data))
        {
            if (patientCount < MAX_PATIENTS && !data.empty())
            {
                patients[patientCount].load(data);
                patientCount++;
            }
        }

        file.close();
    }

    void loadDoctors()
    {
        ifstream file("doctors.txt");
        string data;

        while (getline(file, data))
        {
            if (doctorCount < MAX_DOCTORS && !data.empty())
            {
                doctors[doctorCount].load(data);
                doctorCount++;
            }
        }

        file.close();
    }

    void loadAppointments()
    {
        ifstream file("appointments.txt");
        string data;

        while (getline(file, data))
        {
            if (appointmentCount < MAX_APPOINTMENTS && !data.empty())
            {
                appointments[appointmentCount].load(data);
                appointmentCount++;
            }
        }

        file.close();
    }

    void loadRecords()
    {
        ifstream file("medical_records.txt");
        string data;

        while (getline(file, data))
        {
            if (recordCount < MAX_RECORDS && !data.empty())
            {
                records[recordCount].load(data);
                recordCount++;
            }
        }

        file.close();
    }

    void loadBills()
    {
        ifstream file("bills.txt");
        string data;

        while (getline(file, data))
        {
            if (billCount < MAX_BILLS && !data.empty())
            {
                bills[billCount].load(data);
                billCount++;
            }
        }

        file.close();
    }

    void loadRooms()
    {
        ifstream file("rooms.txt");
        string data;

        while (getline(file, data))
        {
            if (roomCount < MAX_ROOMS && !data.empty())
            {
                rooms[roomCount].load(data);
                roomCount++;
            }
        }

        file.close();

        // Create default rooms on first launch.
        if (roomCount == 0)
        {
            for (int i = 0; i < 10; i++)
                rooms[roomCount++] = Room(101 + i, "General", 1500);

            for (int i = 0; i < 10; i++)
                rooms[roomCount++] = Room(201 + i, "Private", 3000);

            for (int i = 0; i < 5; i++)
                rooms[roomCount++] = Room(301 + i, "ICU", 6000);

            saveRooms();
        }
    }

    // ========================================================
    // PATIENT MANAGEMENT
    // ========================================================

    void addPatient()
    {
        heading("REGISTER NEW PATIENT");

        if (patientCount >= MAX_PATIENTS)
        {
            cout << "Patient storage is full!\n";
            return;
        }

        string name = getText("Patient Name: ");
        int age = getInteger("Patient Age: ");

        if (age <= 0 || age > 120)
        {
            cout << "\nInvalid age!\n";
            return;
        }

        string gender = getText("Gender: ");
        string phone = getText("Phone Number: ");
        string address = getText("Address: ");
        string blood = getText("Blood Group: ");

        int id = nextPatientID();

        patients[patientCount] =
            Patient(id, name, age, gender, phone, address, blood);

        patientCount++;

        savePatients();

        cout << "\nPatient registered successfully!\n";
        cout << "Generated Patient ID: " << id << "\n";
    }

    void viewPatients()
    {
        heading("ALL REGISTERED PATIENTS");

        if (patientCount == 0)
        {
            cout << "No patients registered.\n";
            return;
        }

        cout << left
             << setw(10) << "ID"
             << setw(22) << "NAME"
             << setw(8) << "AGE"
             << setw(12) << "GENDER"
             << setw(15) << "PHONE"
             << setw(12) << "BLOOD"
             << "\n";

        line();

        for (int i = 0; i < patientCount; i++)
            patients[i].display();
    }

    void searchPatient()
    {
        heading("SEARCH PATIENT");

        int id = getInteger("Enter Patient ID: ");
        int index = findPatient(id);

        if (index == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        cout << "\nPatient found:\n";

        // Runtime polymorphism
        Person* person = &patients[index];
        person->display();

        cout << "\nPatient ID: " << patients[index].getID() << "\n";
    }

    void updatePatient()
    {
        heading("UPDATE PATIENT");

        int id = getInteger("Enter Patient ID: ");
        int index = findPatient(id);

        if (index == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        cout << "\nEnter updated information:\n";

        string name = getText("New Name: ");
        int age = getInteger("New Age: ");

        if (age <= 0 || age > 120)
        {
            cout << "\nInvalid age!\n";
            return;
        }

        string gender = getText("New Gender: ");
        string phone = getText("New Phone: ");
        string address = getText("New Address: ");
        string blood = getText("New Blood Group: ");

        patients[index] =
            Patient(id, name, age, gender, phone, address, blood);

        savePatients();

        cout << "\nPatient information updated successfully!\n";
    }

    // ========================================================
    // DOCTOR MANAGEMENT
    // ========================================================

    void addDoctor()
    {
        heading("ADD NEW DOCTOR");

        if (doctorCount >= MAX_DOCTORS)
        {
            cout << "Doctor storage is full!\n";
            return;
        }

        string name = getText("Doctor Name: ");
        int age = getInteger("Doctor Age: ");

        if (age < 18 || age > 100)
        {
            cout << "\nInvalid age!\n";
            return;
        }

        string gender = getText("Gender: ");
        string phone = getText("Phone Number: ");
        string specialization = getText("Specialization: ");

        double fee = getInteger("Consultation Fee (Rs.): ");

        if (fee <= 0)
        {
            cout << "\nInvalid consultation fee!\n";
            return;
        }

        int id = nextDoctorID();

        doctors[doctorCount] =
            Doctor(id, name, age, gender, phone, specialization, fee);

        doctorCount++;

        saveDoctors();

        cout << "\nDoctor added successfully!\n";
        cout << "Generated Doctor ID: " << id << "\n";
    }

    void viewDoctors()
    {
        heading("HOSPITAL DOCTORS");

        if (doctorCount == 0)
        {
            cout << "No doctors registered.\n";
            return;
        }

        cout << left
             << setw(10) << "ID"
             << setw(22) << "NAME"
             << setw(22) << "SPECIALIZATION"
             << setw(8) << "AGE"
             << setw(15) << "PHONE"
             << "CONSULTATION FEE\n";

        line();

        for (int i = 0; i < doctorCount; i++)
            doctors[i].display();
    }

    void searchDoctor()
    {
        heading("SEARCH DOCTOR");

        int id = getInteger("Enter Doctor ID: ");
        int index = findDoctor(id);

        if (index == -1)
        {
            cout << "\nDoctor not found!\n";
            return;
        }

        cout << "\nDoctor found:\n";

        Person* person = &doctors[index];
        person->display();

        cout << "\nDoctor ID: " << doctors[index].getID();
        cout << "\nSpecialization: " << doctors[index].getSpecialization();
        cout << "\nConsultation Fee: Rs. " << doctors[index].getFee() << "\n";
    }

    void updateDoctor()
    {
        heading("UPDATE DOCTOR");

        int id = getInteger("Enter Doctor ID: ");
        int index = findDoctor(id);

        if (index == -1)
        {
            cout << "\nDoctor not found!\n";
            return;
        }

        string name = getText("New Name: ");
        int age = getInteger("New Age: ");

        if (age < 18 || age > 100)
        {
            cout << "\nInvalid age!\n";
            return;
        }

        string gender = getText("New Gender: ");
        string phone = getText("New Phone: ");
        string specialization = getText("New Specialization: ");

        double fee = getInteger("New Consultation Fee: ");

        if (fee <= 0)
        {
            cout << "\nInvalid fee!\n";
            return;
        }

        doctors[index] =
            Doctor(id, name, age, gender, phone, specialization, fee);

        saveDoctors();

        cout << "\nDoctor updated successfully!\n";
    }

    // ========================================================
    // APPOINTMENT MANAGEMENT
    // ========================================================

    void bookAppointment()
    {
        heading("BOOK APPOINTMENT");

        if (appointmentCount >= MAX_APPOINTMENTS)
        {
            cout << "Appointment storage is full!\n";
            return;
        }

        int pid = getInteger("Enter Patient ID: ");
        int pIndex = findPatient(pid);

        if (pIndex == -1)
        {
            cout << "\nPatient not registered!\n";
            return;
        }

        int did = getInteger("Enter Doctor ID: ");
        int dIndex = findDoctor(did);

        if (dIndex == -1)
        {
            cout << "\nDoctor not found!\n";
            return;
        }

        int day = getInteger("Enter Appointment Day Number: ");

        if (day <= 0)
        {
            cout << "\nInvalid day number!\n";
            return;
        }

        string time = getText("Enter Appointment Time (e.g. 10:30 AM): ");

        // Check doctor and patient availability.
        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].isBooked() &&
                appointments[i].getDay() == day &&
                appointments[i].getTime() == time)
            {
                if (appointments[i].getDoctorID() == did)
                {
                    cout << "\nDoctor already has an appointment at this time!\n";
                    return;
                }

                if (appointments[i].getPatientID() == pid)
                {
                    cout << "\nPatient already has an appointment at this time!\n";
                    return;
                }
            }
        }

        int id = nextAppointmentID();

        appointments[appointmentCount] =
            Appointment(id, pid, did, day, time);

        appointmentCount++;

        saveAppointments();

        cout << "\nAppointment booked successfully!\n";
        cout << "Appointment ID : " << id << "\n";
        cout << "Patient Name   : " << patients[pIndex].getName() << "\n";
        cout << "Doctor Name    : " << doctors[dIndex].getName() << "\n";
        cout << "Day Number     : " << day << "\n";
        cout << "Time           : " << time << "\n";
    }

    void viewAppointments()
    {
        heading("ALL APPOINTMENTS");

        if (appointmentCount == 0)
        {
            cout << "No appointments found.\n";
            return;
        }

        cout << left
             << setw(10) << "APPT ID"
             << setw(12) << "PATIENT ID"
             << setw(12) << "DOCTOR ID"
             << setw(12) << "DAY"
             << setw(15) << "TIME"
             << setw(15) << "STATUS"
             << "\n";

        line();

        for (int i = 0; i < appointmentCount; i++)
            appointments[i].display();
    }

    void cancelAppointment()
    {
        heading("CANCEL APPOINTMENT");

        int id = getInteger("Enter Appointment ID: ");
        int index = findAppointment(id);

        if (index == -1)
        {
            cout << "\nAppointment not found!\n";
            return;
        }

        if (!appointments[index].isBooked())
        {
            cout << "\nThis appointment is not active.\n";
            return;
        }

        appointments[index].cancel();

        saveAppointments();

        cout << "\nAppointment cancelled successfully!\n";
    }

    // ========================================================
    // MEDICAL RECORD MANAGEMENT
    // ========================================================

    void addMedicalRecord()
    {
        heading("ADD MEDICAL RECORD");

        if (recordCount >= MAX_RECORDS)
        {
            cout << "Medical record storage is full!\n";
            return;
        }

        int pid = getInteger("Enter Patient ID: ");

        if (findPatient(pid) == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        int did = getInteger("Enter Doctor ID: ");

        if (findDoctor(did) == -1)
        {
            cout << "\nDoctor not found!\n";
            return;
        }

        int day = getInteger("Enter Record Day Number: ");

        if (day <= 0)
        {
            cout << "\nInvalid day number!\n";
            return;
        }

        string diagnosis = getText("Enter Diagnosis: ");
        string prescription = getText("Enter Prescription: ");

        int id = nextRecordID();

        records[recordCount] =
            MedicalRecord(id, pid, did, day, diagnosis, prescription);

        recordCount++;

        // Complete the corresponding appointment if it exists.
        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].getPatientID() == pid &&
                appointments[i].getDoctorID() == did &&
                appointments[i].isBooked())
            {
                appointments[i].complete();
                break;
            }
        }

        saveRecords();
        saveAppointments();

        cout << "\nMedical record saved successfully!\n";
        cout << "Generated Record ID: " << id << "\n";
    }

    void viewMedicalRecords()
    {
        heading("MEDICAL RECORDS");

        if (recordCount == 0)
        {
            cout << "No medical records available.\n";
            return;
        }

        int pid = getInteger("Enter Patient ID: ");

        if (findPatient(pid) == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        bool found = false;

        for (int i = 0; i < recordCount; i++)
        {
            if (records[i].getPatientID() == pid)
            {
                records[i].display();
                line();
                found = true;
            }
        }

        if (!found)
            cout << "\nNo medical records found for this patient.\n";
    }

    // ========================================================
    // BILLING MANAGEMENT
    // ========================================================

    void generateBill()
    {
        heading("GENERATE PATIENT BILL");

        if (billCount >= MAX_BILLS)
        {
            cout << "Bill storage is full!\n";
            return;
        }

        int pid = getInteger("Enter Patient ID: ");

        if (findPatient(pid) == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        double consultation = getInteger("Consultation Charges (Rs.): ");
        double room = getInteger("Room Charges (Rs.): ");
        double other = getInteger("Other Charges (Rs.): ");

        if (consultation < 0 || room < 0 || other < 0 ||
            (consultation + room + other) <= 0)
        {
            cout << "\nInvalid bill amounts!\n";
            return;
        }

        int id = nextBillID();

        bills[billCount] = Bill(id, pid, consultation, room, other);

        billCount++;

        saveBills();

        cout << "\nBill generated successfully!\n";
        bills[billCount - 1].display();
    }

    void viewBills()
    {
        heading("PATIENT BILLING RECORDS");

        if (billCount == 0)
        {
            cout << "No bills found.\n";
            return;
        }

        int pid = getInteger("Enter Patient ID: ");

        if (findPatient(pid) == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        bool found = false;

        for (int i = 0; i < billCount; i++)
        {
            if (bills[i].getPatientID() == pid)
            {
                bills[i].display();
                line();
                found = true;
            }
        }

        if (!found)
            cout << "\nNo bills found for this patient.\n";
    }

    void receivePayment()
    {
        heading("RECEIVE PATIENT PAYMENT");

        int id = getInteger("Enter Bill ID: ");
        int index = findBill(id);

        if (index == -1)
        {
            cout << "\nBill not found!\n";
            return;
        }

        bills[index].display();

        if (bills[index].getBalance() <= 0)
        {
            cout << "\nThis bill is already fully paid.\n";
            return;
        }

        double amount = getInteger("\nEnter Payment Amount (Rs.): ");

        if (amount <= 0 || amount > bills[index].getBalance())
        {
            cout << "\nInvalid payment amount!\n";
            return;
        }

        bills[index].makePayment(amount);

        saveBills();

        cout << "\nPayment received successfully!\n";
        bills[index].display();
    }

    // ========================================================
    // ROOM MANAGEMENT
    // ========================================================

    void viewRooms()
    {
        heading("HOSPITAL ROOM STATUS");

        cout << left
             << setw(12) << "ROOM NO."
             << setw(18) << "ROOM TYPE"
             << setw(18) << "DAILY CHARGE"
             << setw(15) << "PATIENT ID"
             << setw(15) << "STATUS"
             << "\n";

        line();

        for (int i = 0; i < roomCount; i++)
            rooms[i].display();
    }

    void admitPatient()
    {
        heading("ADMIT PATIENT");

        int pid = getInteger("Enter Patient ID: ");

        if (findPatient(pid) == -1)
        {
            cout << "\nPatient not registered!\n";
            return;
        }

        if (hasActiveRoom(pid))
        {
            cout << "\nPatient already has an assigned room!\n";
            return;
        }

        viewRooms();

        int number = getInteger("\nEnter Room Number: ");
        int index = findRoom(number);

        if (index == -1)
        {
            cout << "\nRoom not found!\n";
            return;
        }

        if (rooms[index].isOccupied())
        {
            cout << "\nRoom is already occupied!\n";
            return;
        }

        rooms[index].assignPatient(pid);

        saveRooms();

        cout << "\nPatient admitted successfully!\n";
        cout << "Patient ID : " << pid << "\n";
        cout << "Room No.   : " << number << "\n";
        cout << "Room Type  : " << rooms[index].getType() << "\n";
        cout << "Daily Rate : Rs. "
             << rooms[index].getDailyCharge() << "\n";
    }

    void dischargePatient()
    {
        heading("DISCHARGE PATIENT");

        int pid = getInteger("Enter Patient ID: ");

        if (findPatient(pid) == -1)
        {
            cout << "\nPatient not found!\n";
            return;
        }

        int index = -1;

        for (int i = 0; i < roomCount; i++)
        {
            if (rooms[i].isOccupied() &&
                rooms[i].getPatientID() == pid)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "\nThis patient does not have an assigned room.\n";
            return;
        }

        if (hasPendingBill(pid))
        {
            cout << "\nDischarge blocked! This patient has an unpaid bill.\n";
            cout << "Please clear all outstanding bills first.\n";
            return;
        }

        cout << "\nAssigned Room: " << rooms[index].getNumber();
        cout << "\nDaily Charge: Rs. " << rooms[index].getDailyCharge();

        string confirm = getText("\nType YES to confirm discharge: ");

        if (confirm != "YES")
        {
            cout << "\nDischarge cancelled.\n";
            return;
        }

        rooms[index].releaseRoom();

        saveRooms();

        cout << "\nPatient discharged successfully!\n";
        cout << "Room has been released and is now available.\n";
    }

    // ========================================================
    // DASHBOARD
    // ========================================================

    void dashboard()
    {
        heading("HOSPITAL DASHBOARD");

        int booked = 0;
        int completed = 0;
        int cancelled = 0;

        int occupiedRooms = 0;
        int availableRooms = 0;

        double totalRevenue = 0;
        double pendingBalance = 0;

        for (int i = 0; i < appointmentCount; i++)
        {
            if (appointments[i].getStatus() == "Booked")
                booked++;
            else if (appointments[i].getStatus() == "Completed")
                completed++;
            else if (appointments[i].getStatus() == "Cancelled")
                cancelled++;
        }

        for (int i = 0; i < roomCount; i++)
        {
            if (rooms[i].isOccupied())
                occupiedRooms++;
            else
                availableRooms++;
        }

        for (int i = 0; i < billCount; i++)
        {
            totalRevenue += bills[i].getTotal() - bills[i].getBalance();
            pendingBalance += bills[i].getBalance();
        }

        cout << "\n";
        cout << "                  HOSPITAL STATISTICS\n";
        line();

        cout << left << setw(38) << "Total Registered Patients:"
             << patientCount << "\n";

        cout << left << setw(38) << "Total Registered Doctors:"
             << doctorCount << "\n";

        cout << left << setw(38) << "Total Appointments:"
             << appointmentCount << "\n";

        cout << left << setw(38) << "Booked Appointments:"
             << booked << "\n";

        cout << left << setw(38) << "Completed Appointments:"
             << completed << "\n";

        cout << left << setw(38) << "Cancelled Appointments:"
             << cancelled << "\n";

        cout << left << setw(38) << "Total Hospital Rooms:"
             << roomCount << "\n";

        cout << left << setw(38) << "Occupied Rooms:"
             << occupiedRooms << "\n";

        cout << left << setw(38) << "Available Rooms:"
             << availableRooms << "\n";

        cout << left << setw(38) << "Total Generated Bills:"
             << billCount << "\n";

        cout << fixed << setprecision(2);

        cout << left << setw(38) << "Payments Received:"
             << "Rs. " << totalRevenue << "\n";

        cout << left << setw(38) << "Outstanding Balance:"
             << "Rs. " << pendingBalance << "\n";

        line();
    }

    // ========================================================
    // MENUS
    // ========================================================

    void patientMenu()
    {
        int choice;

        do
        {
            heading("PATIENT MANAGEMENT");

            cout << "1. Register New Patient\n";
            cout << "2. View All Patients\n";
            cout << "3. Search Patient\n";
            cout << "4. Update Patient\n";
            cout << "0. Back to Main Menu\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: addPatient(); break;
                case 2: viewPatients(); break;
                case 3: searchPatient(); break;
                case 4: updatePatient(); break;
                case 0: break;
                default: cout << "\nInvalid choice!\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }

    void doctorMenu()
    {
        int choice;

        do
        {
            heading("DOCTOR MANAGEMENT");

            cout << "1. Add New Doctor\n";
            cout << "2. View All Doctors\n";
            cout << "3. Search Doctor\n";
            cout << "4. Update Doctor\n";
            cout << "0. Back to Main Menu\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: addDoctor(); break;
                case 2: viewDoctors(); break;
                case 3: searchDoctor(); break;
                case 4: updateDoctor(); break;
                case 0: break;
                default: cout << "\nInvalid choice!\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }

    void appointmentMenu()
    {
        int choice;

        do
        {
            heading("APPOINTMENT MANAGEMENT");

            cout << "1. Book Appointment\n";
            cout << "2. View All Appointments\n";
            cout << "3. Cancel Appointment\n";
            cout << "0. Back to Main Menu\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: bookAppointment(); break;
                case 2: viewAppointments(); break;
                case 3: cancelAppointment(); break;
                case 0: break;
                default: cout << "\nInvalid choice!\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }

    void medicalMenu()
    {
        int choice;

        do
        {
            heading("MEDICAL RECORD MANAGEMENT");

            cout << "1. Add Medical Record\n";
            cout << "2. View Patient Medical History\n";
            cout << "0. Back to Main Menu\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: addMedicalRecord(); break;
                case 2: viewMedicalRecords(); break;
                case 0: break;
                default: cout << "\nInvalid choice!\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }

    void billingMenu()
    {
        int choice;

        do
        {
            heading("BILLING MANAGEMENT");

            cout << "1. Generate Patient Bill\n";
            cout << "2. View Patient Bills\n";
            cout << "3. Receive Payment\n";
            cout << "0. Back to Main Menu\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: generateBill(); break;
                case 2: viewBills(); break;
                case 3: receivePayment(); break;
                case 0: break;
                default: cout << "\nInvalid choice!\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }

    void roomMenu()
    {
        int choice;

        do
        {
            heading("ROOM MANAGEMENT");

            cout << "1. View All Rooms\n";
            cout << "2. Admit Patient\n";
            cout << "3. Discharge Patient\n";
            cout << "0. Back to Main Menu\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: viewRooms(); break;
                case 2: admitPatient(); break;
                case 3: dischargePatient(); break;
                case 0: break;
                default: cout << "\nInvalid choice!\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }

public:

    // ========================================================
    // HOSPITAL CONSTRUCTOR
    // ========================================================

    Hospital()
    {
        patientCount = 0;
        doctorCount = 0;
        appointmentCount = 0;
        recordCount = 0;
        billCount = 0;
        roomCount = 0;

        loadPatients();
        loadDoctors();
        loadAppointments();
        loadRecords();
        loadBills();
        loadRooms();
    }

    // ========================================================
    // MAIN APPLICATION
    // ========================================================

    void run()
    {
        int choice;

        do
        {
            cout << "\n\n";
            cout << "============================================================\n";
            cout << "                 HOSPITAL MANAGEMENT SYSTEM\n";
            cout << "============================================================\n";
            cout << "                  Welcome, Administrator!\n";
            cout << "\n";
            cout << "                       MAIN MENU\n";

            line();

            cout << "  1. Patient Management\n";
            cout << "  2. Doctor Management\n";
            cout << "  3. Appointment Management\n";
            cout << "  4. Medical Records\n";
            cout << "  5. Billing Management\n";
            cout << "  6. Room Management\n";
            cout << "  7. View All Patients\n";
            cout << "  8. Hospital Dashboard\n";
            cout << "  0. Exit Application\n";

            line();

            choice = getInteger("Enter Your Choice: ");

            switch (choice)
            {
                case 1: patientMenu(); break;
                case 2: doctorMenu(); break;
                case 3: appointmentMenu(); break;
                case 4: medicalMenu(); break;
                case 5: billingMenu(); break;
                case 6: roomMenu(); break;
                case 7: viewPatients(); break;
                case 8: dashboard(); break;

                case 0:
                    saveAll();

                    cout << "\n";
                    cout << "============================================================\n";
                    cout << "       THANK YOU FOR USING HOSPITAL MANAGEMENT SYSTEM\n";
                    cout << "             All records saved successfully!\n";
                    cout << "============================================================\n";
                    break;

                default:
                    cout << "\nInvalid choice! Please try again.\n";
            }

            if (choice != 0)
                pauseScreen();

        } while (choice != 0);
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    Hospital hospital;

    hospital.run();

    return 0;
}
