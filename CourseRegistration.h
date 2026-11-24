#pragma once
#include <string>
#include "DataStructures.h"

LopHocPhan* timLopHocPhan(LinkedListLop& dsLop, const std::string& maLop);

bool moLopHocPhan(LinkedListLop& dsLop, const LopHocPhan& lopMoi);
void xemDanhSachLopConCho(const LinkedListLop& dsLop, const std::string& maMon);

bool kiemTraDieuKienTienQuyet(const SinhVien& sv, const std::string& maMonTienQuyet);
bool kiemTraTrungLich(const LinkedListLop& dsLop, const std::string& mssv, const std::string& lichHocMoi);
bool kiemTraGioiHanTinChi(const SinhVien& sv, int tinChiMonMoi);

int dangKyHocPhan(HashTable& dsSV, LinkedListLop& dsLop, const std::string& mssv, const std::string& maLop);
bool huyDangKy(HashTable& dsSV, LinkedListLop& dsLop, const std::string& mssv, const std::string& maLop);
void xetDuyetHangDoi(HashTable& dsSV, LinkedListLop& dsLop, const std::string& maLop);