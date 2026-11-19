#include "CourseRegistration.h"
#include <iostream>

bool moLopHocPhan(LinkedListSV& dsLop, const LopHocPhan& lopMoi) {
    return true; 
}
void xemDanhSachLopConCho(const LinkedListSV& dsLop, const std::string& maMon) {
    std::cout << "Danh sach lop con cho mon " << maMon << ":\n";
}

bool kiemTraDieuKienTienQuyet(const std::string& mssv, const std::string& maMon) {
    return true; 
}

bool kiemTraTrungLich(const std::string& mssv, const std::string& lichHocMoi) {
    return false;

bool kiemTraGioiHanTinChi(const SinhVien& sv, int tinChiMonMoi) {
    return (sv.tongTinChi + tinChiMonMoi) <= 25;
}

int dangKyHocPhan(const std::string& mssv, const std::string& maLop) {
    if (!kiemTraDieuKienTienQuyet(mssv, "MA_MON") || kiemTraTrungLich(mssv, "LICH")) {
        return 0; // Thất bại
    }
    bool conCho = true;
    if (conCho) {
        return 1;
    } else {
        return 2; 
    }
}

bool huyDangKy(const std::string& mssv, const std::string& maLop) {
    xetDuyetHangDoi(maLop);
    return true;
}

void xetDuyetHangDoi(const std::string& maLop) {
   
}
