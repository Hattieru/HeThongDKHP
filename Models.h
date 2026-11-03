#pragma once
#include <string>

// Các cấu trúc cơ bản
struct SinhVien {
    std::string mssv;
    std::string hoTen;
    int namHoc;          // Dùng để ưu tiên sinh viên năm cuối
    int soTinChiDaDK;    // Kiểm tra giới hạn 25 tín chỉ
};

struct LopHocPhan {
    std::string maLop;
    std::string maMonHoc;
    int siSoToiDa;
    int siSoHienTai;
    std::string lichHoc; // VD: "Thu2_Tiet1-3"
    std::string maMonTienQuyet;
};