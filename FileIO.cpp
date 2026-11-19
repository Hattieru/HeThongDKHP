#include "FileIO.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void docDuLieuKhoiDong(HashTable& dsSV, LinkedListSV& dsLop)
{
    // ========= Đọc sinh viên =========

    ifstream finSV("sinhvien.txt");

    if(finSV)
    {
        string line;

        while(getline(finSV, line))
        {
            if(line.empty())
                continue;

            stringstream ss(line);

            SinhVien sv;

            string temp;

            getline(ss, sv.mssv, ',');
            getline(ss, sv.hoTen, ',');

            getline(ss, temp, ',');
            sv.soTinChiDaDK = stoi(temp);

            sv.namHoc = 1;

            // TODO:
            // Khi HashTable hoàn thiện:
            // insert(dsSV, sv);
        }

        finSV.close();
    }

    // ========= Đọc lớp học phần =========

    ifstream finLop("lophocphan.txt");

    if(finLop)
    {
        string line;

        while(getline(finLop, line))
        {
            if(line.empty())
                continue;

            stringstream ss(line);

            LopHocPhan lop;

            string temp;

            getline(ss, lop.maLop, ',');
            getline(ss, lop.maMonHoc, ',');

            getline(ss, temp, ',');
            lop.siSoToiDa = stoi(temp);

            getline(ss, temp, ',');
            lop.siSoHienTai = stoi(temp);

            lop.lichHoc = "";
            lop.maMonTienQuyet = "";

            // TODO:
            // Khi LinkedListSV hoàn thiện:
            // add(dsLop, lop);
        }

        finLop.close();
    }

    cout << "Doc du lieu khoi dong thanh cong!\n";
}


void ghiDuLieuKetThuc(const HashTable& dsSV,
                      const LinkedListSV& dsLop)
{
    // TODO:
    // HashTable và LinkedListSV chưa hoàn thiện.

    ofstream foutSV("sinhvien_backup.txt");
    foutSV.close();

    ofstream foutLop("lophocphan_backup.txt");
    foutLop.close();

    cout << "Da ghi du lieu ket thuc!\n";
}


void sinhDuLieuNgauNhien(int soLuong)
{
    ofstream fout("sinhvien_ngau_nhien.txt");

    for(int i = 1; i <= soLuong; i++)
    {
        fout
            << "SV"
            << i
            << ",SinhVien"
            << i
            << ",0"
            << endl;
    }

    fout.close();

    cout << "Da sinh "
         << soLuong
         << " sinh vien.\n";
}