#pragma once
#include <string>

struct NodeMon {
    std::string maMon;
    NodeMon* next = nullptr;
};

struct SinhVien {
    std::string mssv;
    std::string hoTen;
    int namHoc = 1;               // 1..4 (dùng ưu tiên sinh viên năm cuối)
    int soTinChiDaDK = 0;         // Kiểm tra giới hạn 25 tín chỉ
    NodeMon* dsMonDaHoc = nullptr;// Danh sách mã môn đã tích lũy
};

struct NodeSV {
    SinhVien data;
    NodeSV* next = nullptr;
};

struct LinkedListSV {
    NodeSV* head = nullptr;
    NodeSV* tail = nullptr;
};

struct Queue {
    NodeSV* front = nullptr;
    NodeSV* rear = nullptr;
};

struct LopHocPhan {
    std::string maLop;
    std::string maMonHoc;
    std::string tenMon;
    int soTinChi = 3;
    int siSoToiDa = 0;
    int siSoHienTai = 0;
    std::string lichHoc;          // VD: "Thu2_Tiet1-3"
    std::string maMonTienQuyet;   // VD: "NONE" nếu không có
    LinkedListSV dsDaDK;
    Queue hangDoi;
};