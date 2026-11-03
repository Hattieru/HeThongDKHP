#pragma once
#include <string>
#include "DataStructures.h"

// Quản lý lớp
bool moLopHocPhan(LinkedListSV& dsLop, const LopHocPhan& lopMoi);
void xemDanhSachLopConCho(const LinkedListSV& dsLop, const std::string& maMon);

// Logic đăng ký
bool kiemTraDieuKienTienQuyet(const std::string& mssv, const std::string& maMon);
bool kiemTraTrungLich(const std::string& mssv, const std::string& lichHocMoi);
bool kiemTraGioiHanTinChi(const SinhVien& sv, int tinChiMonMoi); // Tối đa 25 tín chỉ

// Hành động của Sinh viên
int dangKyHocPhan(const std::string& mssv, const std::string& maLop); 
// Trả về: 1 (Thành công), 2 (Vào hàng đợi), 0 (Thất bại do vi phạm điều kiện)

bool huyDangKy(const std::string& mssv, const std::string& maLop);
void xetDuyetHangDoi(const std::string& maLop); // Kéo SV đầu hàng đợi vào lớp khi có người hủy