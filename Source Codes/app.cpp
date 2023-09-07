#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

bool readFile(const char *, BST *);
int menu();

int main() {

	int choice = 0;
	BST t1;
	if (!readFile("student.txt", &t1)) {
		cout << "Cannot open file student.txt\n";
		return 1;
	}

	// while (choice != 7) {
	// 	system("cls");
	// 	choice = menu();
	// 	cout << "\n";
	// 	system("pause");
	// }

	// t1.printLevelNodes();

	// test clone function
	BST t2;
	BST t3;
	Student stu;
	stu.id = 28; // take the root node for example
	t2.CloneSubtree(t1, stu);

	cout << "t1:" << endl;
	t1.printLevelNodes();
	cout << "t2:" << endl;
	t2.printLevelNodes();

	// modify t1:
	Student stu2;
	stu2.id = 1;
	t1.insert(stu2);

	// check if t2 is affected
	cout << "t1:" << endl;
	t1.printLevelNodes();
	cout << "t2:" << endl;
	t2.printLevelNodes();

	t1.printPath();

	return 0;
}

bool readFile(const char * filename, BST * t1) {
	ifstream input_file (filename); // open file

	if (!input_file) { // fail to open
		return false;
	}

	int stu_num = 0;

	Student student;
	string dummy;
	// file format:
	// Student Id = 28
	// Name = Matt Damon
	// Address = 465 Ripley Boulevard, Oscar Mansion, Malaysia 7666322
	// DOB = 10-10-1970
	// Phone Number = 790-3233
	// Course = CS
	// CGPA = 3.12076
	while (!input_file.eof()) {
		// read student info
		// student id
		input_file >> dummy >> dummy >> dummy;
		input_file >> student.id;
		// name
		input_file >> dummy >> dummy;
		input_file.ignore();
		input_file.getline(student.name, 30);
		// address
		input_file >> dummy >> dummy;
		input_file.ignore();
		input_file.getline(student.address, 100);
		// date of birth
		input_file >> dummy >> dummy;
		input_file.ignore();
		input_file.getline(student.DOB, 20);
		// phone number
		input_file >> dummy >> dummy >> dummy;
		input_file.ignore();
		input_file.getline(student.phone_no, 10);
		// course
		input_file >> dummy >> dummy;
		input_file >> student.course;
		// cgpa
		input_file >> dummy >> dummy;
		input_file >> student.cgpa;

		// insert student into BST
		t1->insert(student);
		stu_num++;
	}

	input_file.close(); // close file
	cout << "Read " << stu_num << " students from file.\n";

	return true;
}

int menu() {
	cout << "------------------MENU------------------\n";
	cout << "1. Read data to BST\n";
	cout << "2. Print deepest nodes\n";
	cout << "3. Display student\n";
	cout << "4. Clone Subtree\n";
	cout << "5. Print Level Nodes\n";
	cout << "6. Print Path\n";
	cout << "7. Exit\n";
	cout << "----------------------------------------\n";
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	return choice;
}