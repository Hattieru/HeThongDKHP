#include "AdvancedFeatures.h"
#include "CourseRegistration.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>

// ---------------------------------------------------------
// HÀM PHỤ TRỢ: TÁCH TÊN (TỪ CUỐI CÙNG) ĐỂ SẮP XẾP ĐÚNG TÊN VIỆT NAM
// ---------------------------------------------------------
static std::string layTenChinh(const std::string& hoTen) {
    size_t pos = hoTen.find_last_of(' ');
    if (pos == std::string::npos) return hoTen;
    return hoTen.substr(pos + 1);
}

static bool nhoHonTheoTen(const SinhVien& a, const SinhVien& b) {
    std::string tenA = layTenChinh(a.hoTen);
    std::string tenB = layTenChinh(b.hoTen);
    if (tenA != tenB) return tenA < tenB;
    return a.hoTen < b.hoTen;
}

// ---------------------------------------------------------
// 1. SẮP XẾP DANH SÁCH SINH VIÊN THEO TÊN (MERGE SORT - O(N log N))
// ---------------------------------------------------------
static NodeSV* tronHaiDanhSach(NodeSV* a, NodeSV* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    NodeSV* ketQua = nullptr;
    if (nhoHonTheoTen(a->data, b->data)) {
        ketQua = a;
        ketQua->next = tronHaiDanhSach(a->next, b);
    } else {
        ketQua = b;
        ketQua->next = tronHaiDanhSach(a, b->next);
    }
    return ketQua;
}

static NodeSV* mergeSortNodeSV(NodeSV* head) {
    if (head == nullptr || head->next == nullptr) return head;

    NodeSV* slow = head;
    NodeSV* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    NodeSV* nuaSau = slow->next;
    slow->next = nullptr;

    NodeSV* trai = mergeSortNodeSV(head);
    NodeSV* phai = mergeSortNodeSV(nuaSau);

    return tronHaiDanhSach(trai, phai);
}

void sapXepDanhSachTheoTen(LinkedListSV& ds) {
    if (ds.head == nullptr || ds.head->next == nullptr) return;
    ds.head = mergeSortNodeSV(ds.head);

    NodeSV* p = ds.head;
    while (p->next != nullptr) {
        p = p->next;
    }
    ds.tail = p;
}

// ---------------------------------------------------------
// 2. IN THỜI KHÓA BIỂU CỦA SINH VIÊN
// ---------------------------------------------------------
void inThoiKhoaBieu(const std::string& mssv, const LinkedListLop& dsLop) {
    NodeLop* p = dsLop.head;
    bool coLop = false;
    int tongTinChi = 0;

    while (p != nullptr) {
        if (tonTaiSV(p->data.dsDaDK, mssv)) {
            std::cout << "  - " << p->data.maLop
                      << " | Mon: " << p->data.maMonHoc << " (" << p->data.tenMon << ")"
                      << " | Lich: " << p->data.lichHoc
                      << " | Tin chi: " << p->data.soTinChi << "\n";
            tongTinChi += p->data.soTinChi;
            coLop = true;
        }
        p = p->next;
    }

    if (!coLop) {
        std::cout << "  Sinh vien chua dang ky lop hoc phan nao.\n";
    } else {
        std::cout << "=> Tong so tin chi da dang ky: " << tongTinChi << "/25\n";
    }
}

// ---------------------------------------------------------
// 3. THỐNG KÊ LỚP CÓ TỈ LỆ ĐĂNG KÝ THẤP (< 50%) ĐỂ XÉT HỦY LỚP
// ---------------------------------------------------------
void thongKeLopTiLeThap(const LinkedListLop& dsLop) {
    NodeLop* p = dsLop.head;
    bool coLopThap = false;

    std::cout << std::fixed << std::setprecision(1);
    while (p != nullptr) {
        double tiLe = (p->data.siSoToiDa > 0)
            ? (100.0 * p->data.siSoHienTai / p->data.siSoToiDa)
            : 0.0;

        if (tiLe < 50.0) {
            std::cout << "  - " << p->data.maLop
                      << " (" << p->data.tenMon << ")"
                      << " | Si so: " << p->data.siSoHienTai << "/" << p->data.siSoToiDa
                      << " (" << tiLe << "%) -> De xuat huy lop\n";
            coLopThap = true;
        }
        p = p->next;
    }

    if (!coLopThap) {
        std::cout << "  Khong co lop nao co ti le dang ky duoi 50%.\n";
    }
}

// ---------------------------------------------------------
// 4. MÔ PHỎNG 10^4 SINH VIÊN ĐĂNG KÝ ĐỒNG THỜI NGẪU NHIÊN & ĐO THỜI GIAN
// ---------------------------------------------------------
void moPhong10000SinhVienDangKy(HashTable& dsSV, LinkedListLop& dsLop) {
    const int SO_SV = 10000;
    const int SO_LOP_MO_PHONG = 120;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Tạo 120 lớp mô phỏng (tổng 9000 chỗ < 10000 SV để phát sinh hàng đợi ưu tiên)
    for (int i = 1; i <= SO_LOP_MO_PHONG; ++i) {
        std::string maLopSim = "SIM_LHP_" + std::to_string(i);
        if (timLopHocPhan(dsLop, maLopSim) == nullptr) {
            LopHocPhan lop;
            lop.maLop = maLopSim;
            lop.maMonHoc = "MH" + std::to_string((i % 25) + 1);
            lop.tenMon = "Mon mo phong " + std::to_string((i % 25) + 1);
            lop.soTinChi = 3;
            lop.siSoToiDa = 75;
            lop.siSoHienTai = 0;
            lop.lichHoc = "Thu" + std::to_string((i % 6) + 2) + "_Ca" + std::to_string((i % 4) + 1);
            lop.maMonTienQuyet = (i % 3 == 0) ? "MH1" : "NONE";
            moLopHocPhan(dsLop, lop);
        }
    }

    int soLop = 0;
    for (NodeLop* p = dsLop.head; p != nullptr; p = p->next) soLop++;

    std::string* dsMaLop = new std::string[soLop];
    int idxLop = 0;
    for (NodeLop* p = dsLop.head; p != nullptr; p = p->next) {
        dsMaLop[idxLop++] = p->data.maLop;
    }

    std::string* dsMSSV = new std::string[SO_SV];
    int* thuTu = new int[SO_SV];

    for (int i = 0; i < SO_SV; ++i) {
        SinhVien sv;
        sv.mssv = "SIM_SV_" + std::to_string(i + 1);
        sv.hoTen = "Sinh Vien " + std::to_string(i + 1);
        sv.namHoc = (std::rand() % 4) + 1;
        sv.soTinChiDaDK = 0;
        sv.dsMonDaHoc = nullptr;

        // 80% sinh viên đã qua môn tiên quyết "MH1"
        if ((std::rand() % 100) < 80) {
            sv.dsMonDaHoc = new NodeMon{ "MH1", nullptr };
        }

        themSinhVien(dsSV, sv);
        dsMSSV[i] = sv.mssv;
        thuTu[i] = i;
    }

    // Trộn ngẫu nhiên thứ tự 10^4 sinh viên đăng ký đồng thời
    for (int i = SO_SV - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        int tmp = thuTu[i];
        thuTu[i] = thuTu[j];
        thuTu[j] = tmp;
    }

    int thanhCong = 0, vaoHangDoi = 0, thatBai = 0;

    auto batDau = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < SO_SV; ++i) {
        const std::string& mssv = dsMSSV[thuTu[i]];
        const std::string& maLop = dsMaLop[std::rand() % soLop];

        int kq = dangKyHocPhan(dsSV, dsLop, mssv, maLop);
        if (kq == 1) thanhCong++;
        else if (kq == 2) vaoHangDoi++;
        else thatBai++;
    }

    auto ketThuc = std::chrono::high_resolution_clock::now();
    double thoiGianMs = std::chrono::duration<double, std::milli>(ketThuc - batDau).count();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "--- KET QUA MO PHONG " << SO_SV << " SINH VIEN ---\n";
    std::cout << "  - Tong so lop tham gia   : " << soLop << "\n";
    std::cout << "  - Dang ky thanh cong     : " << thanhCong << " (" << (100.0 * thanhCong / SO_SV) << "%)\n";
    std::cout << "  - Vao hang doi (uu tien) : " << vaoHangDoi << " (" << (100.0 * vaoHangDoi / SO_SV) << "%)\n";
    std::cout << "  - That bai               : " << thatBai << " (" << (100.0 * thatBai / SO_SV) << "%)\n";
    std::cout << "  - Thoi gian thuc thi     : " << thoiGianMs << " ms\n";

    delete[] dsMaLop;
    delete[] dsMSSV;
    delete[] thuTu;
}

void tinhToanThoiGianThucThi() {
    std::cout << "Thoi gian thuc thi duoc do truc tiep trong chuc nang Mo phong 10^4 sinh vien.\n";
}

// ---------------------------------------------------------
// 5. GIẢI PHÓNG TOÀN BỘ BỘ NHỚ CẤP PHÁT ĐỘNG
// ---------------------------------------------------------
void giaiPhongToanBoBoNho(HashTable& dsSV, LinkedListLop& dsLop) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        NodeSV* p = dsSV.buckets[i];
        while (p != nullptr) {
            NodeMon* m = p->data.dsMonDaHoc;
            while (m != nullptr) {
                NodeMon* tmpM = m;
                m = m->next;
                delete tmpM;
            }
            NodeSV* tmpSV = p;
            p = p->next;
            delete tmpSV;
        }
        dsSV.buckets[i] = nullptr;
    }

    NodeLop* pLop = dsLop.head;
    while (pLop != nullptr) {
        NodeSV* sv = pLop->data.dsDaDK.head;
        while (sv != nullptr) {
            NodeSV* tmp = sv;
            sv = sv->next;
            delete tmp;
        }

        NodeSV* q = pLop->data.hangDoi.front;
        while (q != nullptr) {
            NodeSV* tmp = q;
            q = q->next;
            delete tmp;
        }

        NodeLop* tmpLop = pLop;
        pLop = pLop->next;
        delete tmpLop;
    }
    dsLop.head = dsLop.tail = nullptr;
}