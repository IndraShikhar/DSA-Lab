#include <iostream>

using namespace std;

struct Node {
    int coef, pow;
    struct Node* next;
};

void insert(struct Node*& head, int c, int p) {
    struct Node* newNode;
    newNode = new struct Node();
    newNode->coef = c;
    newNode->pow = p;
    newNode->next = nullptr;
    if (head == nullptr) {
        head = newNode;
    }
    else {
        struct Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayNode(struct Node*& head) {
    if (head == nullptr) {
        cout << "The node list is empty!" << endl;
    }
    else {
        struct Node* temp = head;
        while (true) {
            cout << temp->coef << "x^" << temp->pow << "->";
            if (temp->next == nullptr) {
                break;
            }
            else {
                temp = temp->next;
            }
        }cout << endl;
    }
}

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

int main() {
    struct Node* poly1;
    displayNode(poly1);
    insert(poly1, 12, 8);
    insert(poly1, 15, 3);
    displayNode(poly1);

    struct Node* poly2;
    displayNode(poly2);
    insert(poly2, 12, 7);
    insert(poly2, 18, 3);
    displayNode(poly2);

    struct Node* result;
    result = addNode(poly1, poly2);
    displayNode(result);
    getchar();
    return 0;
}