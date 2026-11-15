#pragma once
#include <string>
#include "DataStructures.h"

using namespace std;

bool moLopHocPhan(LinkedListSV& dsLop, const LopHocPhan& lopMoi);

void xemDanhSachLopConCho(
    const LinkedListSV& dsLop,
    const string& maMon
);

bool kiemTraDieuKienTienQuyet(
    const string& mssv,
    const string& maMon
);

bool kiemTraTrungLich(
    const string& mssv,
    const string& lichHocMoi
);

bool kiemTraGioiHanTinChi(
    const SinhVien& sv,
    int tinChiMonMoi
);

int dangKyHocPhan(
    const string& mssv,
    const string& maLop
);

bool huyDangKy(
    const string& mssv,
    const string& maLop
);

void xetDuyetHangDoi(const string& maLop);
