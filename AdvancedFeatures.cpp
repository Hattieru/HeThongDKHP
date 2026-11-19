#include "AdvancedFeatures.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// ============================================================================
// AdvancedFeatures.cpp
// Thành viên thực hiện: Bùi Đình Khôi
// Các hàm nâng cao: sắp xếp, thống kê, mô phỏng và quản lý bộ nhớ.
// ============================================================================

// 1. Sắp xếp danh sách sinh viên theo họ tên tăng dần.
// Dùng vector con trỏ để sắp xếp rồi nối lại danh sách; không cấp phát node mới.
void sapXepDanhSachTheoTen(LinkedListSV& ds) {
    if (ds.head == nullptr || ds.head->next == nullptr) {
        std::cout << "Danh sach khong du sinh vien de sap xep.\n";
        return;
    }

    std::vector<NodeSV*> nodes;
    for (NodeSV* p = ds.head; p != nullptr; p = p->next) {
        nodes.push_back(p);
    }

    std::sort(nodes.begin(), nodes.end(), [](const NodeSV* a, const NodeSV* b) {
        return a->data.hoTen < b->data.hoTen;
    });

    ds.head = nodes.front();
    for (std::size_t i = 0; i + 1 < nodes.size(); ++i) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes.back()->next = nullptr;
    ds.tail = nodes.back();

    std::cout << "Da sap xep danh sach sinh vien theo ho ten tang dan.\n";
}

// 2. Thống kê lớp có tỷ lệ thấp.
// LinkedListSV hiện chỉ chứa SinhVien, chưa có dữ liệu lớp học phần/sĩ số,
// vì vậy không thể tính tỷ lệ lớp một cách chính xác ở phiên bản cấu trúc này.
void thongKeLopTiLeThap(const LinkedListSV& dsLop) {
    (void)dsLop;
    std::cout << "Chua the thong ke ty le lop: LinkedListSV/NodeSV hien chua "
                 "luu thong tin LopHocPhan va si so.\n";
}

// 3. In thời khóa biểu của sinh viên.
// Hiện chưa có cấu trúc liên kết MSSV với danh sách lớp đã đăng ký và lịch học.
void inThoiKhoaBieu(const std::string& mssv, const LinkedListSV& dsLop) {
    (void)dsLop;
    std::cout << "Thoi khoa bieu cua sinh vien " << mssv << ":\n";
    std::cout << "Chua co du lieu dang ky/lien ket lich hoc de hien thi.\n";
}

// 4. Mô phỏng tạo dữ liệu 10.000 sinh viên.
// Đây là mô phỏng sinh dữ liệu trong bộ nhớ tạm; HashTable hiện chưa có
// cấu trúc bucket hoặc hàm insert nên không thể đưa dữ liệu vào bảng băm.
void moPhong10000SinhVienDangKy(HashTable& dsSV, LinkedListSV& dsLop) {
    (void)dsSV;
    (void)dsLop;

    constexpr int SO_LUONG = 10000;
    std::mt19937 rng(static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> namHocDist(1, 4);
    std::uniform_int_distribution<int> tinChiDist(0, 25);

    std::vector<SinhVien> duLieu;
    duLieu.reserve(SO_LUONG);

    for (int i = 1; i <= SO_LUONG; ++i) {
        SinhVien sv{};
        sv.mssv = "SV" + std::to_string(100000 + i);
        sv.hoTen = "Sinh Vien " + std::to_string(i);
        sv.namHoc = namHocDist(rng);
        sv.soTinChiDaDK = tinChiDist(rng);
        duLieu.push_back(sv);
    }

    std::cout << "Da mo phong tao " << duLieu.size()
              << " sinh vien ngau nhien.\n";
    std::cout << "Luu y: du lieu dang nam trong vector tam; chua insert vao "
                 "HashTable vi HashTable chua duoc cai dat.\n";
}

// 5. Đo thời gian sắp xếp dữ liệu thử nghiệm.
void tinhToanThoiGianThucThi() {
    constexpr int SO_LUONG = 10000;
    std::vector<std::string> ten;
    ten.reserve(SO_LUONG);

    std::mt19937 rng(static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(1, SO_LUONG);

    for (int i = 0; i < SO_LUONG; ++i) {
        ten.push_back("Sinh Vien " + std::to_string(dist(rng)));
    }

    const auto batDau = std::chrono::high_resolution_clock::now();
    std::sort(ten.begin(), ten.end());
    const auto ketThuc = std::chrono::high_resolution_clock::now();

    const auto microGiay = std::chrono::duration_cast<std::chrono::microseconds>(
        ketThuc - batDau).count();

    std::cout << "Thoi gian sort " << SO_LUONG << " chuoi (std::sort): "
              << microGiay << " micro giay.\n";
    std::cout << "Do phuc tap tham khao: O(N log N).\n";
}

// 6. Giải phóng danh sách liên kết sinh viên.
// HashTable chưa có định nghĩa bucket/node nên không thể giải phóng an toàn
// phần bộ nhớ của bảng băm ở đây.
void giaiPhongToanBoBoNho(HashTable& dsSV, LinkedListSV& dsLop) {
    (void)dsSV;

    NodeSV* p = dsLop.head;
    while (p != nullptr) {
        NodeSV* nodeCanXoa = p;
        p = p->next;
        delete nodeCanXoa;
    }

    dsLop.head = nullptr;
    dsLop.tail = nullptr;

    std::cout << "Da giai phong danh sach lien ket sinh vien/lop.\n";
    std::cout << "HashTable chua co cau truc node/bucket; chua the giai phong "
                 "bang ham nay.\n";
}
