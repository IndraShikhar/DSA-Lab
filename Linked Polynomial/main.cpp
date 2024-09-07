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
                if (head->next->coef >= 0)
                    cout << "+";
            }
        }
        cout << endl;
    }
}

int main() {
    struct Node* node = nullptr;
    // insert(node, 12, 8);
    // insert(node, 18, 7);
    // insert(node, 26, 5);
    insert(node, 25, 3);
    insert(node, 32, 1);

    displayNode(node);

    struct Node* res = mulNode(node, node);
    displayNode(res);

    getchar();
    return 0;
}