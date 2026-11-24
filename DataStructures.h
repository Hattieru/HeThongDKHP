#pragma once
#include <string>
#include "Models.h"

struct NodeLop {
    LopHocPhan data;
    NodeLop* next = nullptr;
};

struct LinkedListLop {
    NodeLop* head = nullptr;
    NodeLop* tail = nullptr;
};

// Bảng băm quản lý sinh viên theo MSSV (kích thước số nguyên tố tối ưu cho 10^4 SV)
const int TABLE_SIZE = 10007;

struct HashTable {
    NodeSV* buckets[TABLE_SIZE] = { nullptr };
};

// Hàm thao tác Bảng băm (Sinh viên)
int hashMSSV(const std::string& mssv);
bool themSinhVien(HashTable& dsSV, const SinhVien& sv);
SinhVien* timSinhVien(HashTable& dsSV, const std::string& mssv);

// Hàm thao tác Danh sách liên kết Sinh viên
void themCuoiSV(LinkedListSV& ds, const SinhVien& sv);
bool xoaSVTheoMSSV(LinkedListSV& ds, const std::string& mssv);
bool tonTaiSV(const LinkedListSV& ds, const std::string& mssv);

// Hàm thao tác Hàng đợi (có ưu tiên sinh viên năm cuối)
bool isEmptyQueue(const Queue& q);
void enqueue(Queue& q, const SinhVien& sv);
bool dequeue(Queue& q, SinhVien& svOut);