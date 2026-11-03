#pragma once
#include "Models.h"

// 1. Danh sách liên kết đơn (DSLK) cho Lớp học phần & Sinh viên đã đăng ký
struct NodeSV {
    SinhVien data;
    NodeSV* next;
};
struct LinkedListSV {
    NodeSV* head;
    NodeSV* tail;
    // Các hàm: add, remove, find...
};

// 2. Hàng đợi (Queue) cho Sinh viên chờ
struct Queue {
    NodeSV* front;
    NodeSV* rear;
    // Các hàm: enqueue, dequeue, isEmpty, getFront (ưu tiên năm cuối)
};

// 3. Bảng băm (Hash Table) quản lý toàn bộ Sinh viên theo MSSV
struct HashTable {
    // Khai báo mảng con trỏ, hàm băm hash(mssv)
    // Các hàm: insert, search, remove...
};