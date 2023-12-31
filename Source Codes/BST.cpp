#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}



bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

bool BST::display(int order, int source) {
	if (this->empty()) {
		cout << "The tree is empty." << endl;
		return false;
	}

	if (source == 1) { // console
		if (order == 1) {
			ascendingPrint(this->root, cout);
		}
		else {
			descendingPrint(this->root, cout);
		}
	}
	else { // file
		ofstream out("student-info.txt");
		if (!out) {
			cout << "Cannot open file student-info.txt" << endl;
			return false;
		}
		if (order == 1) {
			ascendingPrint(this->root, out);
		}
		else {
			descendingPrint(this->root, out);
		}
		cout << "The tree has been printed to student-info.txt" << endl;
	}
	return true;
}

void BST::ascendingPrint(BTNode *cur, ostream &out) {

	if (cur == NULL) return;

	ascendingPrint(cur->left, out);
	cur->item.print(out);
	ascendingPrint(cur->right, out);
}

void BST::descendingPrint(BTNode *cur, ostream &out) {

	if (cur == NULL) return;

	descendingPrint(cur->right, out);
	cur->item.print(out);
	descendingPrint(cur->left, out);
}

bool BST::printLevelNodes() {
    if (empty()) {
        cout << "The tree is empty." << endl;
        return false;
    }

    BTNode* cur;
    Queue q;
    int level = 1; // Initialize the level

    q.enqueue(root); // Enqueue the root node

    while (!q.empty()) {
        int nodesInLevel = q.size(); // Get the number of nodes at the current level

        cout << "Level " << level << " nodes: ";

        for (int i = 0; i < nodesInLevel; ++i) {
            q.dequeue(cur);

            if (cur != NULL) {
                cout << cur->item.id << " "; // Print the student ID (adjust this according to your Student class)

                if (cur->left != NULL)
                    q.enqueue(cur->left);

                if (cur->right != NULL)
                    q.enqueue(cur->right);
            }
        }

        cout << endl;
        level++; // Move to the next level
    }

    return true;
}

// Function to clone a subtree in t1 where the root of the subtree contains value item
bool BST::CloneSubtree(BST t1, type item) {
    if (t1.root == nullptr) {
        // t1 is empty, return false
        std::cout << "Cannot clone subtree: Tree t1 is empty." << std::endl;
        return false;
    }

    BTNode* targetNode = nullptr;
    // Search for the node with the specified item in t1
    BTNode* current = t1.root;
    while (current != nullptr) {
        if (item.id == current->item.id) {
			targetNode = current;
            break;
        } else if (item.id < current->item.id) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (targetNode == nullptr) {
        // Item not found in t1, return false
        std::cout << "Cannot clone subtree: Student ID " << item.id << " not found in t1." << std::endl;
        return false;
    }

    // Clone the subtree rooted at targetNode into t2 (current tree)
    this->cloneSubtreeHelper(targetNode);

    return true;
}

// Helper function to recursively clone a subtree rooted at a given node
void BST::cloneSubtreeHelper(BTNode* currentNode) {
    if (currentNode == nullptr) {
        return;
    }

    // Create a new node with the same data
    this->insert(currentNode->item);
    
    // Recursively clone the left and right subtrees
    cloneSubtreeHelper(currentNode->left);
    cloneSubtreeHelper(currentNode->right);
}

bool BST::deepestNodes()// print deepest nodes
{
	int count = 0;

	if (root == NULL) {
		cout << "The tree is empty." << endl;
		return false;
	}
	else
	{
		count = MaxDepth(root);
		cout << "The deepest node is: ";
		deepestNodes2(root, count);
		cout << endl;
		return true;
	}
}

void BST::deepestNodes2(BTNode *cur, int count) 
{

	if (cur == NULL) {
		return;
	}
	if (count == 1) {

		cout << cur->item.id << " ";
	}
	//searching for he deepest nodes
	deepestNodes2(cur->left, count - 1);
	deepestNodes2(cur->right, count - 1);
}

int BST::MaxDepth(BTNode* cur) //check for the maximum depth
{
	int LeftDepth, RightDepth;

	if (cur == NULL)
		return 0;
	else
	{
		LeftDepth = MaxDepth(cur->left);
		RightDepth = MaxDepth(cur->right);
		if (LeftDepth > RightDepth)
			return (LeftDepth + 1);
		else
			return (RightDepth + 1);

	}
}

#include <string>

bool BST::printPath() {
    if (empty()) {
        cout << "The tree is empty." << endl;
        return false;
    }

    cout << "Below are all the external paths for the tree:" << endl;

    printExternalPaths(root, ""); // Call the helper function

    return true;
}

// Helper function to print external paths recursively
void BST::printExternalPaths (BTNode* node, string path) {
	if (node == nullptr) {
		return;
	}

	// Append the current node's ID to the path
	path += to_string(node->item.id) + " ";

	// If it's a leaf node (external node), print the path
	if (node->left == nullptr && node->right == nullptr) {
		cout << path << endl;
		return;
	}

	// Continue traversing the left and right subtrees
	printExternalPaths(node->left, path);
	printExternalPaths(node->right, path);
};