#include "FileManager.h"
#include <fstream>

void docFile(Node*& head)
{
    ifstream fin("sinhvien.txt");

    string mssv;
    string ten;
    int tc;

    while(getline(fin, mssv, ','))
    {
        getline(fin, ten, ',');

        fin >> tc;
        fin.ignore();

        SinhVien sv;
        sv.mssv = mssv;
        sv.hoTen = ten;
        sv.tinChi = tc;

        themCuoi(head, sv);
    }

    fin.close();
}

void ghiFile(Node* head)
{
    ofstream fout("sinhvien.txt");

    Node* temp = head;

    while(temp != NULL)
    {
        fout
            << temp->data.mssv << ","
            << temp->data.hoTen << ","
            << temp->data.tinChi
            << endl;

        temp = temp->next;
    }

    fout.close();
}