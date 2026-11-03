#pragma once
#include "DataStructures.h"

// Thuật toán sắp xếp (tự cài đặt Quick Sort hoặc Merge Sort)
void sapXepDanhSachTheoTen(LinkedListSV& ds);

// Thống kê
void thongKeLopTiLeThap(const LinkedListSV& dsLop); 
void inThoiKhoaBieu(const std::string& mssv, const LinkedListSV& dsLop);

// Chức năng nâng cao & Thực nghiệm
void moPhong10000SinhVienDangKy(HashTable& dsSV, LinkedListSV& dsLop); // Sinh đồng thời ngẫu nhiên
void tinhToanThoiGianThucThi(); // Trả về số liệu để viết báo cáo

// Quản lý bộ nhớ - RẤT QUAN TRỌNG ĐỂ KHÔNG BỊ TRỪ ĐIỂM
void giaiPhongToanBoBoNho(HashTable& dsSV, LinkedListSV& dsLop);