# patient-record-management-system]

# Patient Record Management System in C

## About the Project
The Patient Record Management System is a menu-driven application developed using the C programming language. It manages patient information using a dynamic singly linked list.

The project demonstrates fundamental data structure operations and helps organize patient records efficiently.

## Features
- Add new patient records
- Display all patient records
- Search for a patient using registration number
- Update patient information
- Delete patient records
- Sort patient records by registration number
- Check for duplicate registration numbers

## Patient Information
Each record contains:
- Registration Number
- Patient Name
- Guardian Name
- Gender
- Age
- Blood Group
- Phone Number
- Address
- City
- State
- Disease or Problem
- Referred Doctor
- Medical History

## Data Structure Used
**Singly Linked List**

Each patient is stored in a dynamically allocated node. Each node contains patient details and a pointer to the next node.

## Algorithms Used
- **Linear Search:** Finds a patient by registration number.
- **Insertion Sort:** Sorts patient records by registration number.
- **Dynamic Memory Allocation:** Uses `malloc()` and `free()` to manage memory.

## Technologies Used
- C Programming Language
- GCC Compiler
- GitHub Codespaces

## How to Compile and Run

Compile the program:
```bash
gcc patient_record.c -o patient_record
```

Run on Codespaces:

```bash
./patient_record
```

## Limitations
- Records are stored in memory only while the program is running.
- Records are not permanently saved to a file or database.

## Future Improvements
- Store records permanently using file handling.
- Add more patient information update options.
- Develop a graphical user interface.

