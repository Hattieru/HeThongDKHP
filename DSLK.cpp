#include "DSLK.h"

void themCuoi(Node*& head, SinhVien sv)
{
    Node* p = new Node;

    p->data = sv;
    p->next = NULL;

    if(head == NULL)
    {
        head = p;
        return;
    }

    Node* temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = p;
}

void hienThi(Node* head)
{
    Node* temp = head;

    while(temp != NULL)
    {
        cout
            << temp->data.mssv
            << " - "
            << temp->data.hoTen
            << " - "
            << temp->data.tinChi
            << endl;

        temp = temp->next;
    }
}

Node* timSinhVien(Node* head, string mssv)
{
    Node* temp = head;

    while(temp != NULL)
    {
        if(temp->data.mssv == mssv)
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}
