#pragma once
#include <string>

// Gọi các menu hiển thị (Console/Text menu)
void hienThiMenuChinh();
void hienThiMenuSinhVien();
void hienThiMenuQuanTri();

// Các hàm tương tác nhập xuất
std::string nhapMSSV();
std::string nhapMaLop();
void inThongBao(const std::string& thongBao);

// Bắt lỗi dữ liệu nhập từ bàn phím (mã trùng, sai kiểu, sai miền)
bool kiemTraDuLieuDauVao(const std::string& input, int kieuKiemTra);