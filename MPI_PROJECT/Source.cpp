#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "mpi.h"
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

ofstream write;

struct PatientData {

    string P_id;
    int age;
    char sex;
    string b_group;
    string date;
    string illness;
};
class Node {
public:
    PatientData key;
    Node* left;
    Node* right;
    int height;
};

int max(int a, int b);

// Calculate height
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// New node creation
Node* newNode(PatientData key) {
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    return x;
}

// Rotate left
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
        height(N->right);
}

// Insert a node
Node* insertNode(Node* node, PatientData key) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key));
    if (key.P_id < node->key.P_id)
        node->left = insertNode(node->left, key);
    else if (key.P_id > node->key.P_id)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
        height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key.P_id < node->left->key.P_id) {
            return rightRotate(node);
        }
        else if (key.P_id > node->left->key.P_id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key.P_id > node->right->key.P_id) {
            return leftRotate(node);
        }
        else if (key.P_id < node->right->key.P_id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// Node with minimum value
Node* nodeWithMimumValue(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}




// Print the tree
void printTree(Node* root, string indent, bool last) {
    if (root != nullptr) {
        cout << indent;
        if (last) {
            cout << "R----";
            indent += "   ";
        }
        else {
            cout << "L----";
            indent += "|  ";
        }
        cout << root->key.P_id << endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}
bool Search(Node* root, string key, Node*& result) {
    if (root == NULL)
        return false;

    if (root->key.P_id == key) {
        result = root;
        return true;
    }

    if (key < root->key.P_id)
        return Search(root->left, key, result);
    else
        return Search(root->right, key, result);
}
bool Update(Node* root, string key,int world_rank) {
    Node* result;
    bool status1 = Search(root, key, result);
    MPI_Barrier(MPI_COMM_WORLD);

    int choice = 0;
    if (status1 == true) {
        do {
            cout << "Please enter your choice (1-5): ";
            cout << "Press 0 to exit!!" << endl;
            cout << "Press 1 for Age." << endl;
            cout << "Press 2 for Blood_group." << endl;
            cout << "Press 3 for sex." << endl;
            cout << "Press 4 for Date." << endl;
            cout << "Press 5 for illness." << endl;



            cin >> choice;
            if (choice == 0) {
                break;
            }
            if (choice == 1) {
                cout << "Enter new Age : ";
                int n_age;
                cin >> n_age;
                result->key.age = n_age;
            }
            else if (choice == 2) {
                cout << "Enter new BloodGroup : ";
                string n_bl;
                cin >> n_bl;
                result->key.b_group = n_bl;
            }

            else if (choice == 3)
            {
                cout << "Enter new Sex : ";
                char n_sex;
                cin >> n_sex;
                result->key.sex = n_sex;
            }

            else if (choice == 4) {
                cout << "Enter new Date : ";
                string n_date;
                cin >> n_date;
                result->key.date = n_date;
            }

            else if (choice == 5) {
                cout << "Enter new Illness : ";
                string n_illness;
                cin >> n_illness;
                result->key.illness = n_illness;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        } while (choice != 0);
        return true;
    }
    else {
        if ((world_rank == 0 && status1 == false) && (world_rank == 1 && status1 == false) && (world_rank == 2 && status1 == false)) {
            cout << "Data not found to be modified" << endl;
        }
    }
    return false;
}
void displaylog();
void exitfile(Node* root,int world_rank);
void logmod(string key, string operation);
void logmod(string key, string operation);
void printdataspecific(Node* root, string key);
bool deleteNode(Node*& root, string key);
bool callsearch(Node* root, string key, int world_size,int world_rank);
bool calldelNode(Node* root, string key, int world_size, int world_rank,int *local_size);
bool calladdnode(Node* root, PatientData p, int world_size, int world_rank, int *local_size);

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size < 2) {
        cerr << "This program requires at least 2 processes." << endl;
        MPI_Finalize();
        return 1;
    }

    // Root process reads the file
    vector<PatientData> all_data;
    for (int i = 0; i < world_size; i++) {
        if (world_rank == 0) {
            ifstream infile("D:/Semester6/PDC/MPI_PROJECT/MPI_PROJECT/f" + to_string(i+1) + ".txt");
            if (!infile.is_open()) {
                cerr << "Unable to open file." << endl;
                MPI_Finalize();
                return 1;
            }

            string line;
            while (getline(infile, line)) {
                stringstream ss(line);
                PatientData patient;
                getline(ss, patient.P_id, ',');
                ss >> patient.age;
                ss.ignore(1); // Ignore comma
                ss >> patient.sex;
                ss.ignore(1); // Ignore comma
                getline(ss, patient.b_group, ',');
                getline(ss, patient.date, ',');
                getline(ss, patient.illness);
                all_data.push_back(patient);
            }
            infile.close();
            //add recovery
        }
    }
    
    // Broadcast the size of the patient data to all processes
    int data_size = all_data.size();
    MPI_Bcast(&data_size, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process calculates its share of the data
    int local_size = data_size / world_size;
    if (world_rank == 0) {
        local_size += data_size % world_size; // Root process takes the remainder
    }

    // Allocate space for local data
    vector<PatientData> local_data(local_size);
    MPI_Scatter(all_data.data(), local_size * sizeof(PatientData), MPI_BYTE, local_data.data(), local_size * sizeof(PatientData), MPI_BYTE, 0, MPI_COMM_WORLD);
    Node* root = NULL;
    vector<PatientData>::iterator it = local_data.begin();
    for (it; it<local_data.end();it++) {
        root = insertNode(root, *it);
        if (world_rank == 2) {
            vector<PatientData>::iterator et = local_data.end();
            et -= 2;
            if (it ==et ) {
                break;
            }
        }
       
    }
    MPI_Barrier(MPI_COMM_WORLD);
    PatientData p;
    p.P_id = "P0001";
    bool st = calladdnode(root, p, world_size, world_rank, &local_size);
    cout << st << endl;
    
    MPI_Finalize();
    return 0;
}

bool calladdnode(Node* root,PatientData p,int world_size,int world_rank,int* local_size) {

    bool status1 = callsearch(root, p.P_id, world_size, world_rank);
    int minindex = 0;
            if (world_rank > 0) {
                int x = *local_size;
                MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
            if (world_rank == 0) {
                int arr[2];
                for (int i = 0; i < 2; i++) {
                    MPI_Recv(&arr[i], 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
                int minsize = *local_size;
                
                for (int i = 0; i < 2; i++) {
                    if (minsize > arr[i]) {
                        minsize = arr[i];
                        minindex = i+1;
                    }
                }
               
            }
            MPI_Bcast(&minindex, 1, MPI_INT, 0, MPI_COMM_WORLD);
           

            if (world_rank == minindex && status1==false) {
                *local_size += 1;
                insertNode(root, p);
                return true;
            }
            return false;
        
    
    
}
bool calldelNode(Node* root, string key,int world_size,int world_rank,int* local_size) {
    bool status1 = deleteNode(root, key);
    *local_size -= 1;
    MPI_Barrier(MPI_COMM_WORLD);
    Node* recv_result = new Node();
    MPI_Barrier(MPI_COMM_WORLD);
    if (world_rank > 0) {
        int x = 0;
        if (status1 == true) {
            x = 1;
        }
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (world_rank == 0) {
        int arr[2];
        for (int i = 0; i < 2; i++) {
            MPI_Recv(&arr[i], 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (arr[0] == 1) {
            status1 = true;
        }
        else if (arr[1] == 1) {
            status1 = true;
        }
    }


    if (world_rank == 0) {

        if (status1 == false) {
            cout << "Query not found" << endl;
            return false;
        }
        else {
            cout << "Pateient Recoed Delted Successfully" << endl;
            return true;
        }

    }
}
bool callsearch(Node* root, string key, int world_size, int world_rank) {
    Node* result;
    bool status1 = Search(root, key, result);
    Node* recv_result = new Node();
    MPI_Barrier(MPI_COMM_WORLD);
    if (world_rank > 0) {
        int x = 0;
        if (status1 == true) {
            x = 1;
        }
        MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (world_rank == 0) {
       int arr[2];
        for (int i = 0; i < 2; i++) {
           MPI_Recv(&arr[i], 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        if (arr[0] ==1 ) {
            status1 = true;
        }
        else if (arr[1] == 1) {
            status1 = true;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (world_rank == 0){

        if (status1==false) {
            return false;
        }
        else {
            return true;
        }

    }
}
bool deleteNode(Node*& root, string key) {
    // Find the node and delete it
    if (root == NULL)
        return false;
    if (key < root->key.P_id)
        return deleteNode(root->left, key);
    else if (key > root->key.P_id)
        return deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            Node* temp = nodeWithMimumValue(root->right);
            root->key = temp->key;
            deleteNode(root->right, temp->key.P_id);
        }
        return true;
    }
}
void printdataspecific(Node* root, string key) {
    Node* result;
    bool status1= Search(root, key, result);
    MPI_Barrier(MPI_COMM_WORLD);
    if (status1 == true) {
        cout << "The id is " << result->key.P_id << endl;
        cout << "The age is " << result->key.age << endl;
        cout << "The blood group is " << result->key.b_group << endl;
        cout << "The date is" << result->key.date << endl;
        cout << "The sex is " << result->key.sex << endl;
        cout << "The illness is " << result->key.illness << endl;
    }

}

void logmod(string key, string operation) {
    time_t current_time = time(nullptr);
    char time_str[26];
    ctime_s(time_str, sizeof(time_str), &current_time);

    string time = time_str;
    ofstream write;
    write.open("D:/Semester6/PDC/MPI_PROJECT/MPI_PROJECT/log.txt", ios::app);
    if (write.is_open()) {
        write << key;
        write << " , ";
        write << operation;
        write << " , ";
        write << time;
    }
    else {
        cout << "Log file not found" << endl;
    }
    write.close();
}
void displaylog() {
    ifstream read("D:\Semester6\PDC\MPI_PROJECT\MPI_PROJECT\log.txt");
    if (read.is_open()) {
        string line;
        while (getline(read, line)) {
            cout << line;
        }
        read.close();
    }
    else {
        cout << "Log File not Found" << endl;
    }
}

void exitfile(Node* root, int world_rank) {
    if (root == nullptr)
        return;

    // Open the file only once
    if (world_rank >= 0 && world_rank < 3) {
        write.open("D:/Semester6/PDC/MPI_PROJECT/MPI_PROJECT/f" + to_string(world_rank + 1) + ".txt", ios::app);
        if (!write.is_open()) {
            cout << "Error opening file f" << world_rank + 1 << ".txt" << endl;
            return;
        }
    }

    // Write data to the file
    write << root->key.P_id << ", " << root->key.age << ", " << root->key.sex << ", "
        << root->key.b_group << ", " << root->key.date << ", " << root->key.illness << endl;

    // Recursively call exitfile for left and right children
    exitfile(root->left, world_rank);
    exitfile(root->right, world_rank);

    // Close the file only once
    if (world_rank >= 0 && world_rank < 3) {
        write.close();
    }
}



