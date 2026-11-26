# 🏥 Hospital Management System

A console-based **Hospital Management System** developed using C++ and Object-Oriented Programming (OOP). This project provides an organized way to manage hospital operations, including patient registration, doctor management, appointments, medical records, billing, and room allocation.

## 🚀 Features

### 👨‍⚕️ Patient Management
- Register new patients.
- View all registered patients.
- Search patients by ID.
- Update patient information.

### 🩺 Doctor Management
- Add new doctors.
- View doctor information.
- Search doctors by ID.
- Update doctor details.
- Manage consultation fees and specializations.

### 📅 Appointment Management
- Book appointments.
- View appointment records.
- Cancel appointments.
- Prevent scheduling conflicts for doctors and patients.

### 📋 Medical Records
- Record patient diagnoses.
- Store prescriptions.
- View patient medical history.
- Maintain doctor and patient references.

### 💰 Billing Management
- Generate patient bills.
- Calculate total charges.
- Receive partial and full payments.
- Track outstanding balances.

### 🛏️ Room Management
- View available and occupied rooms.
- Admit registered patients.
- Assign hospital rooms.
- Discharge patients.
- Prevent double room assignments.

### 📊 Hospital Dashboard
- Total registered patients.
- Total registered doctors.
- Appointment statistics.
- Room availability.
- Payments received.
- Outstanding balances.

### 💾 File Handling
- Automatically save records.
- Load existing records when the application starts.
- Maintain separate files for different modules.

## 🛠️ Technologies Used

- C++
- C++17
- Object-Oriented Programming
- File Handling
- Fixed-Size Arrays
- Standard C++ Libraries

## 🧠 OOP Concepts Implemented

- Classes and Objects
- Encapsulation
- Inheritance
- Abstraction
- Polymorphism
- Virtual Functions
- Function Overriding
- Constructors
- Composition

## ⚙️ How to Run

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR-USERNAME/Hospital-Management-System.git
```

### 2. Navigate to the Project Directory

```bash
cd Hospital-Management-System
```

### 3. Compile the Program

```bash
g++ -std=c++17 HospitalManagementSystem.cpp -o HospitalManagementSystem
```

### 4. Run the Application

On Windows:

```bash
.\HospitalManagementSystem.exe
```

## 📁 Project Structure

```text
Hospital-Management-System/
│
├── HospitalManagementSystem.cpp
├── patients.txt
├── doctors.txt
├── appointments.txt
├── medical_records.txt
├── bills.txt
├── rooms.txt
├── README.md
└── .gitignore
```

The text files are automatically generated when the application runs.

## 📌 System Rules

- Only registered patients can book appointments.
- Only registered doctors can receive appointments.
- Doctors and patients cannot have overlapping appointments at the same day and time.
- Cancelled appointments cannot be cancelled again.
- A patient cannot be assigned multiple rooms.
- An occupied room cannot be assigned to another patient.
- Patients with outstanding bills cannot be discharged.
- Partial payments are supported.
- All records are saved using file handling.

## 🎯 Project Objective

The objective of this project is to apply fundamental C++ programming and Object-Oriented Programming concepts to develop a practical hospital management application with organized workflows, record management, validation, and persistent storage.

## 👨‍💻 Developer

**Muhammad Ahmad**

BS Computer Science Student | 3rd Semester

Interested in C++, Object-Oriented Programming, Software Development, and AI.

---

⭐ If you find this project useful, consider giving the repository a star.

**Developed as an academic C++ OOP project.**
