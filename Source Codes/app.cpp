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

	BST t1;
	int choice = 0;
	while (choice != 7) {
		system("cls");
		choice = menu();
		cout << "\n==========================================\n";
		switch (choice)
		{
		case 1:
		{
			readFile("student.txt", &t1);
			break;
		}
		case 2:
		{
			t1.deepestNodes();
			break;
		}
		case 3:
		{
			cout << "Please select the order to display student:\n";
			cout << "1. Ascending order\n";
			cout << "2. Descending order\n";
			cout << ">> ";
			int order;
			cin >> order;
			cout << "Please select the output stream:\n";
			cout << "1. Console\n";
			cout << "2. File\n";
			cout << ">> ";
			int stream;
			cin >> stream;
			t1.display(order, stream);
			break;
		}
		case 4:
		{
			BST t2;
			Student stu;
			cout << "Enter student id to clone subtree\n";
			cout << ">> ";
			cin >> stu.id;
			if(!t2.CloneSubtree(t1, stu)) {
				break;
			}
			// Print t1 and t2 using preOrderPrint after cloning
			std::cout << "Original Tree (t1):" << std::endl;
			t1.preOrderPrint();
			cout << "==========================================\n";
			std::cout << "Cloned Subtree (t2):" << std::endl;
			t2.preOrderPrint();
			break;
		}
		case 5:
		{
			t1.printLevelNodes();
			break;
		}
		case 6:
		{
			t1.printPath();
			break;
		}
		case 7:
		{
			cout << "Exiting...\n";
			break;
		}
		default:
		{
			cout << "Invalid choice\n";
			break;
		}
		}
		system("pause");
	}

	return 0;
}

bool readFile(const char * filename, BST * t1) {
	ifstream input_file (filename); // open file

	if (!input_file) { // fail to open
		cout << "Cannot open file " << filename << endl;
		return false;
	}

	int stu_num = 0;

	Student student;
	string dummy;
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
	cout << "------------------ MENU ------------------\n";
	cout << "1. Read data to BST\n";
	cout << "2. Print deepest nodes\n";
	cout << "3. Display student\n";
	cout << "4. Clone Subtree\n";
	cout << "5. Print Level Nodes\n";
	cout << "6. Print Path\n";
	cout << "7. Exit\n";
	cout << "------------------------------------------\n";
	cout << "Enter your choice\n";
	cout << ">> ";
	int choice;
	cin >> choice;
	return choice;
}