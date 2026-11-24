#include "CourseRegistration.h"
#include <iostream>

// Hàm phụ trợ: Tìm lớp học phần theo mã lớp
LopHocPhan* timLopHocPhan(LinkedListLop& dsLop, const std::string& maLop) {
    NodeLop* p = dsLop.head;
    while (p != nullptr) {
        if (p->data.maLop == maLop) {
            return &(p->data);
        }
        p = p->next;
    }
    return nullptr;
}

// 1. Mở lớp học phần mới (có kiểm tra trùng mã lớp)
bool moLopHocPhan(LinkedListLop& dsLop, const LopHocPhan& lopMoi) {
    if (timLopHocPhan(dsLop, lopMoi.maLop) != nullptr) {
        return false; // Trùng mã lớp
    }

    NodeLop* nodeMoi = new NodeLop;
    nodeMoi->data = lopMoi;
    nodeMoi->data.siSoHienTai = 0;
    nodeMoi->data.dsDaDK.head = nodeMoi->data.dsDaDK.tail = nullptr;
    nodeMoi->data.hangDoi.front = nodeMoi->data.hangDoi.rear = nullptr;
    nodeMoi->next = nullptr;

    if (dsLop.head == nullptr) {
        dsLop.head = dsLop.tail = nodeMoi;
    } else {
        dsLop.tail->next = nodeMoi;
        dsLop.tail = nodeMoi;
    }
    return true;
}

// 2. Xem danh sách lớp còn chỗ theo mã môn học
void xemDanhSachLopConCho(const LinkedListLop& dsLop, const std::string& tuKhoa) {
    std::cout << "\n--- Danh sach lop con cho (" << tuKhoa << ") ---\n";
    NodeLop* p = dsLop.head;
    bool coLop = false;

    while (p != nullptr) {
        bool khopMa = (p->data.maLop == tuKhoa || p->data.maMonHoc == tuKhoa);
        bool khopTen = (p->data.tenMon.find(tuKhoa) != std::string::npos);

        if ((khopMa || khopTen) && p->data.siSoHienTai < p->data.siSoToiDa) {
            std::cout << "Ma lop: " << p->data.maLop
                      << " | Ten mon: " << p->data.tenMon
                      << " | Lich hoc: " << p->data.lichHoc
                      << " | Si so: " << p->data.siSoHienTai << "/" << p->data.siSoToiDa
                      << " | Tin chi: " << p->data.soTinChi << "\n";
            coLop = true;
        }
        p = p->next;
    }

    if (!coLop) {
        std::cout << "Khong co lop nao con cho phu hop.\n";
    }
}

// 3. Kiểm tra điều kiện tiên quyết
bool kiemTraDieuKienTienQuyet(const SinhVien& sv, const std::string& maMonTienQuyet) {
    if (maMonTienQuyet.empty() || maMonTienQuyet == "NONE" || maMonTienQuyet == "Khong"
        || maMonTienQuyet == "Khong co" || maMonTienQuyet == "0" || maMonTienQuyet == "-"
        || maMonTienQuyet == "NULL" || maMonTienQuyet == "null") {
        return true;
    }

    NodeMon* p = sv.dsMonDaHoc;
    while (p != nullptr) {
        if (p->maMon == maMonTienQuyet) {
            return true;
        }
        p = p->next;
    }
    return false;
}

// 4. Kiểm tra trùng lịch học với các lớp SV đã đăng ký
bool kiemTraTrungLich(const LinkedListLop& dsLop, const std::string& mssv, const std::string& lichHocMoi) {
    NodeLop* p = dsLop.head;
    while (p != nullptr) {
        // Nếu sinh viên đã nằm trong danh sách lớp này và lịch học bị trùng
        if (tonTaiSV(p->data.dsDaDK, mssv) && p->data.lichHoc == lichHocMoi) {
            return true; // Bị trùng lịch
        }
        p = p->next;
    }
    return false;
}

// 5. Kiểm tra giới hạn tối đa 25 tín chỉ/học kỳ
bool kiemTraGioiHanTinChi(const SinhVien& sv, int tinChiMonMoi) {
    return (sv.soTinChiDaDK + tinChiMonMoi) <= 25;
}

// 6. Đăng ký học phần
int dangKyHocPhan(HashTable& dsSV, LinkedListLop& dsLop, const std::string& mssv, const std::string& maLop) {
    SinhVien* sv = timSinhVien(dsSV, mssv);
    LopHocPhan* lop = timLopHocPhan(dsLop, maLop);

    if (sv == nullptr || lop == nullptr) {
        return 0; // Không tìm thấy SV hoặc lớp
    }

    // Kiểm tra đã đăng ký lớp này trước đó chưa
    if (tonTaiSV(lop->dsDaDK, mssv)) {
        return 0;
    }

    // Kiểm tra đủ 3 ràng buộc: tiên quyết, trùng lịch, giới hạn 25 tín chỉ
    if (!kiemTraDieuKienTienQuyet(*sv, lop->maMonTienQuyet)) return 0;
    if (kiemTraTrungLich(dsLop, mssv, lop->lichHoc)) return 0;
    if (!kiemTraGioiHanTinChi(*sv, lop->soTinChi)) return 0;

    // Còn chỗ -> thêm vào danh sách chính
    if (lop->siSoHienTai < lop->siSoToiDa) {
        themCuoiSV(lop->dsDaDK, *sv);
        lop->siSoHienTai++;
        sv->soTinChiDaDK += lop->soTinChi;
        return 1;
    } 
    // Hết chỗ -> đẩy vào hàng đợi
    else {
        enqueue(lop->hangDoi, *sv);
        return 2;
    }
}

// 7. Hủy đăng ký học phần
bool huyDangKy(HashTable& dsSV, LinkedListLop& dsLop, const std::string& mssv, const std::string& maLop) {
    SinhVien* sv = timSinhVien(dsSV, mssv);
    LopHocPhan* lop = timLopHocPhan(dsLop, maLop);

    if (sv == nullptr || lop == nullptr) {
        return false;
    }

    // Xóa sinh viên khỏi danh sách lớp
    if (!xoaSVTheoMSSV(lop->dsDaDK, mssv)) {
        return false; // Sinh viên vốn không đăng ký lớp này
    }

    lop->siSoHienTai--;
    sv->soTinChiDaDK -= lop->soTinChi;

    // Tự động kéo sinh viên đầu hàng đợi hợp lệ vào lớp
    xetDuyetHangDoi(dsSV, dsLop, maLop);
    return true;
}

// 8. Xét duyệt hàng đợi khi có chỗ trống
void xetDuyetHangDoi(HashTable& dsSV, LinkedListLop& dsLop, const std::string& maLop) {
    LopHocPhan* lop = timLopHocPhan(dsLop, maLop);
    if (lop == nullptr) return;

    while (!isEmptyQueue(lop->hangDoi) && lop->siSoHienTai < lop->siSoToiDa) {
        SinhVien svTam;
        if (!dequeue(lop->hangDoi, svTam)) break;

        // Tra cứu lại bản ghi gốc mới nhất của SV trong bảng băm
        SinhVien* svThuc = timSinhVien(dsSV, svTam.mssv);
        if (svThuc == nullptr) continue;

        // Kiểm tra lại xem tại thời điểm được duyệt, SV còn hợp lệ hay không
        bool hopLe = !tonTaiSV(lop->dsDaDK, svThuc->mssv)
                     && kiemTraDieuKienTienQuyet(*svThuc, lop->maMonTienQuyet)
                     && !kiemTraTrungLich(dsLop, svThuc->mssv, lop->lichHoc)
                     && kiemTraGioiHanTinChi(*svThuc, lop->soTinChi);

        if (hopLe) {
            themCuoiSV(lop->dsDaDK, *svThuc);
            lop->siSoHienTai++;
            svThuc->soTinChiDaDK += lop->soTinChi;
        }
        // Nếu không hợp lệ thì bỏ qua và vòng lặp tự động xét người tiếp theo trong hàng đợi
    }
}