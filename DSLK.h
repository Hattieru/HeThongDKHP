#ifndef DSLK_H
#define DSLK_H

#include <iostream>
#include "SinhVien.h"

using namespace std;

struct Node
{
    SinhVien data;
    Node* next;
};

void themCuoi(Node*& head, SinhVien sv);
void hienThi(Node* head);
Node* timSinhVien(Node* head, string mssv);

#endif