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
        if (temp != head && temp->coffi > 0) {
            cout << "+";
        }
        cout << temp->coffi << "x^" << temp->expo << " ";
        temp = temp->next;
    }
    cout << endl;
}

Node* AddPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->expo == poly2->expo) {
            int coffi = poly1->coffi + poly2->coffi;
            if (coffi != 0) {
                append(result, coffi, poly1->expo);
            }
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
        append(result, poly2->coffi, poly2->expo);
        poly2 = poly2->next;
    }

    return result;
}

Node* CombineLikeTerms(Node* head) {
    Node* result = NULL;
    Node* temp = head;

    while (temp != NULL) {
        Node* current = result;
        bool found = false;

        while (current != NULL) {
            if (current->expo == temp->expo) {
                current->coffi += temp->coffi;
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            append(result, temp->coffi, temp->expo);
        }

        temp = temp->next;
    }

    return result;
}

Node* Multi_Poly(Node* poly1, Node* poly2) {
    if (!poly1 || !poly2) {
        return NULL;
    }
    Node* result = NULL;
    Node* ptr1 = poly1;
    Node* ptr2 = poly2;
    while (ptr1 != NULL) {
        Node* subresult = NULL;
        ptr2 = poly2;
        while (ptr2 != NULL) {
            int coffi = ptr1->coffi * ptr2->coffi;
            int expo = ptr1->expo + ptr2->expo;
            append(subresult, coffi, expo);
            ptr2 = ptr2->next;
        }
        result = AddPoly(result, subresult);
        result = CombineLikeTerms(result); // Combine like terms after each addition
        ptr1 = ptr1->next;
    }
    return result;
}

void DeleteList(Node*& head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    append(poly1, 3, 2);
    append(poly1, 3, 1);
    append(poly1, 3, 0);
    append(poly2, 23, 2);
    append(poly2, 13, 1);
    append(poly2, 2, 0);

    cout << "Polynomial 1 : ";
    ShowPoly(poly1);

    cout << "Polynomial 2 : ";
    ShowPoly(poly2);

    Node* multi = Multi_Poly(poly1, poly2);

    cout << "Result : ";
    ShowPoly(multi);

    DeleteList(poly1);
    DeleteList(poly2);
    DeleteList(multi);

    getchar();
    return 0;
}