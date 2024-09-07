#include <iostream>

using namespace std;

struct Node {
    int coef, pow;
    struct Node* next;
};

void insert(struct Node*&, int, int);
void displayNode(struct Node*);
struct Node* mulNode(struct Node*, struct Node*);
void deleteDuplicate(struct Node*);
struct Node* addNode(struct Node*, struct Node*);
void update(struct Node*&);
void deleteNode(struct Node*&);

struct Node* addNode(struct Node* node1, struct Node* node2) {
    struct Node* temp = nullptr;
    int c, p;
    while (true) {
        if (node1->pow == node2->pow) {
            c = node1->coef + node2->coef;
            p = node1->pow;
            node1 = node1->next;
            node2 = node2->next;
            insert(temp, c, p);
        }
        else if (node1->pow > node2->pow) {
            insert(temp, node1->coef, node1->pow);
            node1 = node1->next;
        }
        else {
            insert(temp, node2->coef, node2->pow);
            node2 = node2->next;
        }
        if (node2 == nullptr)
            break;
    }
    while (node1 != nullptr) {
        insert(temp, node1->coef, node1->pow);
        node1 = node1->next;
    }
    return temp;
}

struct Node* mulNode(struct Node* node1, struct Node* node2) {
    struct Node* result = nullptr;
    struct Node* temp = node2;
    while (node1) {
        node2 = temp;
        while (node2) {
            int c = node1->coef * node2->coef;
            int p = node1->pow + node2->pow;
            insert(result, c, p);
            node2 = node2->next;
        }
        node1 = node1->next;
    }
    deleteDuplicate(result);
    return result;
}

void deleteNode(struct Node*& node) {
    while (node) {
        struct Node* temp = node;
        node = node->next;
        delete temp;
    }
}

void deleteDuplicate(struct Node* node) {
    if (node == nullptr)
        return;
    else {
        while (node) {
            struct Node* temp = node;
            while (temp->next) {
                struct Node* tmp = temp->next;
                if (tmp->pow == node->pow) {
                    int c = tmp->coef + node->coef;
                    node->coef = c;
                    temp->next = tmp->next;
                    delete tmp;
                }
                temp = temp->next;
            }
            node = node->next;
        }
    }
}

void insert(struct Node*& node, int c, int p) {
    struct Node* temp = new struct Node();
    temp->coef = c;
    temp->pow = p;
    temp->next = nullptr;
    if (node == nullptr) {
        node = temp;
    }
    else {
        struct Node* temp2 = node;
        while (true) {
            if (temp2->next == nullptr)
                break;
            else
                temp2 = temp2->next;
        }
        temp2->next = temp;
    }
}

void update(struct Node*& node) {
    deleteNode(node);
    char c;
    do {
        cout << "Enter the coefficient of the term:";
        int a;
        cin >> a;
        cout << "Enter the power of x in the term:";
        int b;
        cin >> b;
        cout << "Is there any other term(y/n):";
        cin >> c;
        insert(node, a, b);
    } while (c == 'y' || c == 'Y');
}

void displayNode(struct Node* head) {
    if (head == nullptr) {
        cout << "The Node list is empty!" << endl;
    }
    else {
        while (true) {
            cout << head->coef << "x^" << head->pow;
            if (head->next == nullptr)
                break;
            else {
                head = head->next;
                cout << "+";
            }
        }
        cout << endl;
    }
}

void displayMenu() {
    cout << "What do wanna do??" << endl;
    cout << "1.Update the polynomial." << endl;
    cout << "2.Add both the polynomials." << endl;
    cout << "3.Multiply both the polynomials." << endl;
    cout << "4.QUIT" << endl;
}

int main() {
    struct Node* node1 = nullptr, * node2 = nullptr, * result;
    int choice;
    insert(node1, 0, 0);
    insert(node2, 0, 0);
    do {
        result = nullptr;
        displayMenu();
        cout << "Enter your choice:";
        cin >> choice;
        switch (choice) {
        case 1:
            int c;
            cout << "Which polynomial you want to update (1 or 2):";
            cin >> c;
            switch (c) {
            case 1:
                update(node1);
                cout << "Updated Polynomial 1:" << endl;
                displayNode(node1);
                break;
            case 2:
                update(node2);
                cout << "Updated Polynomial 2:" << endl;
                displayNode(node2);
            default:
                cout << "Invalid choice" << endl << "Exiting to Main menu..." << endl;
                break;
            }
            break;
        case 2:
            cout << "Polynomial 1:" << endl;
            displayNode(node1);
            cout << "Polynomial 2:" << endl;
            displayNode(node2);
            result = addNode(node1, node2);
            cout << "Result:" << endl;
            displayNode(result);
            break;
        case 3:
            cout << "Polynomial 1:" << endl;
            displayNode(node1);
            cout << "Polynomial 2:" << endl;
            displayNode(node2);
            result = mulNode(node1, node2);
            cout << "Result:" << endl;
            displayNode(result);
            break;
        case 4:
            cout << "Quiting ...." << endl;
            break;
        default:
            cout << "Invalid choice." << "Exiting to Main menu..." << endl;
            break;
        }
        deleteNode(result);
    } while (choice != 4);

    getchar();
    getchar();
    return 0;
}