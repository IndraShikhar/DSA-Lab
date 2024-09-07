#include <iostream>
using namespace std;
struct Node {
    int coffi;
    int expo;
    Node* next;
};
void append(Node*& head, int coffi, int expo) {
    Node* newNode = new Node();
    newNode->coffi = coffi;
    newNode->expo = expo;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    }
    else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void ShowPoly(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->coffi << "x^" << temp->expo << "->";
        temp = temp->next;
    }
}
Node* AddPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->expo == poly2->expo) {
            int coffi = poly1->coffi + poly2->coffi;
            append(result, coffi, poly2->expo);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        else if (poly1->expo > poly2->expo) {
            append(result, poly1->coffi, poly1->expo);
            poly1 = poly1->next;
        }
        else {
            append(result, poly2->coffi, poly2->expo);
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        append(result, poly1->coffi, poly1->expo);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        append(result, poly1->coffi, poly1->expo);
        poly1 = poly1->next;
    }
    return result;
}
int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    append(poly1, 12, 8);
    append(poly1, 15, 3);
    // append(poly1, 3, 0);
    append(poly2, 12, 7);
    append(poly2, 18, 3);
    // append(poly2, 2, 0);

    cout << "Polynomial 1 : ";
    ShowPoly(poly1);
    cout << endl;
    cout << "Polynomial 2 : ";
    ShowPoly(poly2);
    cout << endl;
    cout << "Result = ";
    Node* sum = AddPoly(poly1, poly2);
    ShowPoly(sum);

    getchar();
    return 0;
}