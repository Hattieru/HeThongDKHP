#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

// ========================
// Sinh Vien
// ========================

void docFile(Node*& head)
{
    ifstream fin("sinhvien.txt");

    if(!fin)
    {
        cout << "Khong mo duoc file sinhvien.txt\n";
        return;
    }

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

    if(!fout)
    {
        cout << "Khong ghi duoc file sinhvien.txt\n";
        return;
    }

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


// ========================
// Lop Hoc Phan
// ========================

void docLopHocPhan(vector<LopHocPhan>& dsLop)
{
    ifstream fin("lophocphan.txt");

    if(!fin)
    {
        cout << "Khong mo duoc file lophocphan.txt\n";
        return;
    }

    string line;

    while(getline(fin, line))
    {
        if(line.empty())
            continue;

        stringstream ss(line);

        LopHocPhan lop;
        string temp;

        getline(ss, lop.maMon, ',');
        getline(ss, lop.tenMon, ',');

        getline(ss, temp, ',');
        lop.soTinChi = stoi(temp);

        getline(ss, temp, ',');
        lop.sucChua = stoi(temp);

        dsLop.push_back(lop);
    }

    fin.close();
}

void ghiLopHocPhan(vector<LopHocPhan>& dsLop)
{
    ofstream fout("lophocphan.txt");

    if(!fout)
    {
        cout << "Khong ghi duoc file lophocphan.txt\n";
        return;
    }

    for(auto lop : dsLop)
    {
        fout
            << lop.maMon << ","
            << lop.tenMon << ","
            << lop.soTinChi << ","
            << lop.sucChua
            << endl;
    }

    fout.close();
}
