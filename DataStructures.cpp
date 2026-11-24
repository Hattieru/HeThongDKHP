#include "DataStructures.h"

// 1. BẢNG BĂM (HASH TABLE - CHAINING)
int hashMSSV(const std::string& mssv) {
    unsigned long long hashVal = 0;
    for (char c : mssv) {
        hashVal = (hashVal * 31 + static_cast<unsigned char>(c)) % TABLE_SIZE;
    }
    return static_cast<int>(hashVal);
}

bool themSinhVien(HashTable& dsSV, const SinhVien& sv) {
    if (timSinhVien(dsSV, sv.mssv) != nullptr) {
        return false; // Trùng MSSV
    }
    int idx = hashMSSV(sv.mssv);
    NodeSV* nodeMoi = new NodeSV{ sv, dsSV.buckets[idx] };
    dsSV.buckets[idx] = nodeMoi;
    return true;
}

SinhVien* timSinhVien(HashTable& dsSV, const std::string& mssv) {
    int idx = hashMSSV(mssv);
    NodeSV* p = dsSV.buckets[idx];
    while (p != nullptr) {
        if (p->data.mssv == mssv) {
            return &(p->data);
        }
        p = p->next;
    }
    return nullptr;
}

// 2. DANH SÁCH LIÊN KẾT SINH VIÊN
void themCuoiSV(LinkedListSV& ds, const SinhVien& sv) {
    NodeSV* nodeMoi = new NodeSV{ sv, nullptr };
    if (ds.head == nullptr) {
        ds.head = ds.tail = nodeMoi;
    } else {
        ds.tail->next = nodeMoi;
        ds.tail = nodeMoi;
    }
}

bool xoaSVTheoMSSV(LinkedListSV& ds, const std::string& mssv) {
    NodeSV* prev = nullptr;
    NodeSV* curr = ds.head;
    while (curr != nullptr) {
        if (curr->data.mssv == mssv) {
            if (prev == nullptr) {
                ds.head = curr->next;
            } else {
                prev->next = curr->next;
            }
            if (curr == ds.tail) {
                ds.tail = prev;
            }
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool tonTaiSV(const LinkedListSV& ds, const std::string& mssv) {
    NodeSV* p = ds.head;
    while (p != nullptr) {
        if (p->data.mssv == mssv) return true;
        p = p->next;
    }
    return false;
}

// 3. HÀNG ĐỢI CHỜ (ƯU TIÊN SINH VIÊN NĂM HỌC CAO HƠN, CÙNG NĂM THÌ FIFO)
bool isEmptyQueue(const Queue& q) {
    return q.front == nullptr;
}

void enqueue(Queue& q, const SinhVien& sv) {
    NodeSV* nodeMoi = new NodeSV{ sv, nullptr };
    if (q.front == nullptr) {
        q.front = q.rear = nodeMoi;
        return;
    }

    // Nếu SV mới có năm học cao hơn người đầu hàng -> đưa lên đầu
    if (sv.namHoc > q.front->data.namHoc) {
        nodeMoi->next = q.front;
        q.front = nodeMoi;
        return;
    }

    // Chèn sau tất cả các SV có năm học >= SV mới để giữ đúng thứ tự đến trước vào trước (FIFO)
    NodeSV* p = q.front;
    while (p->next != nullptr && p->next->data.namHoc >= sv.namHoc) {
        p = p->next;
    }
    nodeMoi->next = p->next;
    p->next = nodeMoi;
    if (nodeMoi->next == nullptr) {
        q.rear = nodeMoi;
    }
}

bool dequeue(Queue& q, SinhVien& svOut) {
    if (q.front == nullptr) return false;
    NodeSV* temp = q.front;
    svOut = temp->data;
    q.front = q.front->next;
    if (q.front == nullptr) {
        q.rear = nullptr;
    }
    delete temp;
    return true;
}