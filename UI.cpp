#include <iostream>
#include <string>
#include "UI.h"
#include "CourseRegistration.h"
#include "AdvancedFeatures.h"

using namespace std;

// Chống trôi lệnh và kiểm tra sai kiểu, sai miền
int nhapSoTrongKhoang(int minVal, int maxVal) {
    int val;
    while (true) {
        cin >> val;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "=> [LOI] Vui long nhap mot so nguyen! Nhap lai: ";
        } else if (val < minVal || val > maxVal) {
            cout << "=> [LOI] Gia tri phai tu " << minVal << " den " << maxVal << ". Nhap lai: ";
        } else {
            cin.ignore(10000, '\n');
            return val;
        }
    }
}

// ---------------------------------------------------------
// MENU DÀNH CHO SINH VIÊN
// ---------------------------------------------------------
void hienThiMenuSinhVien(HashTable& dsSV, LinkedListLop& dsLop) {
    string mssv;
    cout << "\n--- XAC THUC SINH VIEN ---" << endl;
    cout << "Nhap MSSV cua ban: ";
    getline(cin, mssv);

    SinhVien* sv = timSinhVien(dsSV, mssv);
    if (sv == nullptr) {
        cout << "=> [LOI] Khong tim thay sinh vien co MSSV '" << mssv << "' trong he thong!" << endl;
        cout << "   (Hay kiem tra file du lieu hoac vao Menu Quan Tri -> Them sinh vien moi)" << endl;
        return;
    }

    cout << "=> Xin chao: " << sv->hoTen << " (Nam " << sv->namHoc
         << " | Tin chi da DK: " << sv->soTinChiDaDK << "/25)" << endl;

    int chon;
    do {
        cout << "\n========== MENU SINH VIEN ==========" << endl;
        cout << "1. Xem danh sach lop con cho theo ma mon" << endl;
        cout << "2. Dang ky hoc phan" << endl;
        cout << "3. Huy dang ky hoc phan" << endl;
        cout << "4. Xem thoi khoa bieu" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "====================================" << endl;
        cout << "Nhap lua chon cua ban (0-4): ";

        chon = nhapSoTrongKhoang(0, 4);

        switch (chon) {
            case 1: {
                string maMon;
                cout << "Nhap Ma Mon Hoc can tra cuu: ";
                getline(cin, maMon);
                xemDanhSachLopConCho(dsLop, maMon);
                break;
            }
            case 2: {
                string maLop;
                cout << "\n[DANG KY HOC PHAN]" << endl;
                cout << "Nhap Ma Lop Hoc Phan muon dang ky: ";
                getline(cin, maLop);

                int kq = dangKyHocPhan(dsSV, dsLop, mssv, maLop);
                if (kq == 1) {
                    cout << "=> Dang ky thanh cong! Ban da vao danh sach chinh." << endl;
                } else if (kq == 2) {
                    cout << "=> Lop da day! Ban da duoc xep vao hang doi cho." << endl;
                } else {
                    cout << "=> Dang ky that bai! (Sai ma lop, da dang ky, trung lich, thieu tien quyet hoac vuot 25 tin chi)" << endl;
                }
                break;
            }
            case 3: {
                string maLop;
                cout << "\n[HUY DANG KY HOC PHAN]" << endl;
                cout << "Nhap Ma Lop Hoc Phan muon huy: ";
                getline(cin, maLop);

                if (huyDangKy(dsSV, dsLop, mssv, maLop)) {
                    cout << "=> Huy dang ky thanh cong! He thong da tu dong xet duyet hang doi." << endl;
                } else {
                    cout << "=> Huy that bai! (Sai ma lop hoac ban chua dang ky lop nay)" << endl;
                }
                break;
            }
            case 4:
                cout << "\n[THOI KHOA BIEU CUA " << sv->hoTen << "]" << endl;
                inThoiKhoaBieu(mssv, dsLop);
                break;
            case 0:
                cout << "Quay lai menu chinh..." << endl;
                break;
        }
    } while (chon != 0);
}

// ---------------------------------------------------------
// MENU DÀNH CHO QUẢN TRỊ VIÊN (GIÁO VỤ)
// ---------------------------------------------------------
void hienThiMenuQuanTri(HashTable& dsSV, LinkedListLop& dsLop) {
    int chon;
    do {
        cout << "\n========= MENU QUAN TRI VIEN =========" << endl;
        cout << "1. Mo lop hoc phan moi" << endl;
        cout << "2. Them sinh vien moi" << endl;
        cout << "3. Xem danh sach sinh vien cua 1 lop (sap xep theo ten)" << endl;
        cout << "4. Thong ke cac lop co ti le dang ky thap" << endl;
        cout << "5. Chay mo phong 10^4 sinh vien dang ky" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "======================================" << endl;
        cout << "Nhap lua chon cua ban (0-5): ";

        chon = nhapSoTrongKhoang(0, 5);

        switch (chon) {
            case 1: {
                LopHocPhan lopMoi;
                cout << "\n[MO LOP HOC PHAN MOI]" << endl;
                cout << "Nhap Ma Lop (VD: LHP001): ";
                getline(cin, lopMoi.maLop);
                cout << "Nhap Ma Mon Hoc (VD: CTDL): ";
                getline(cin, lopMoi.maMonHoc);
                cout << "Nhap Ten Mon Hoc: ";
                getline(cin, lopMoi.tenMon);
                cout << "Nhap So Tin Chi (1-10): ";
                lopMoi.soTinChi = nhapSoTrongKhoang(1, 10);
                cout << "Nhap Si So Toi Da (1-500): ";
                lopMoi.siSoToiDa = nhapSoTrongKhoang(1, 500);
                cout << "Nhap Lich Hoc (VD: Thu2_Tiet1-3): ";
                getline(cin, lopMoi.lichHoc);
                cout << "Nhap Ma Mon Tien Quyet (nhap NONE neu khong co): ";
                getline(cin, lopMoi.maMonTienQuyet);

                if (moLopHocPhan(dsLop, lopMoi)) {
                    cout << "=> Mo lop " << lopMoi.maLop << " thanh cong!" << endl;
                } else {
                    cout << "=> [LOI] Ma lop " << lopMoi.maLop << " da ton tai!" << endl;
                }
                break;
            }
            case 2: {
                SinhVien svMoi;
                cout << "\n[THEM SINH VIEN MOI]" << endl;
                cout << "Nhap MSSV: ";
                getline(cin, svMoi.mssv);
                cout << "Nhap Ho Ten: ";
                getline(cin, svMoi.hoTen);
                cout << "Nhap Nam Hoc (1-5): ";
                svMoi.namHoc = nhapSoTrongKhoang(1, 5);
                svMoi.soTinChiDaDK = 0;
                svMoi.dsMonDaHoc = nullptr;

                if (themSinhVien(dsSV, svMoi)) {
                    cout << "=> Them sinh vien " << svMoi.hoTen << " thanh cong!" << endl;
                } else {
                    cout << "=> [LOI] MSSV " << svMoi.mssv << " da ton tai!" << endl;
                }
                break;
            }
            case 3: {
                string maLop;
                cout << "\n[XEM DANH SACH LOP]" << endl;
                cout << "Nhap Ma Lop can xem: ";
                getline(cin, maLop);

                LopHocPhan* lop = timLopHocPhan(dsLop, maLop);
                if (lop == nullptr) {
                    cout << "=> Khong tim thay lop " << maLop << "!" << endl;
                    break;
                }

                sapXepDanhSachTheoTen(lop->dsDaDK);

                cout << "--- Lop " << lop->maLop << " (" << lop->tenMon << ") | Si so: "
                     << lop->siSoHienTai << "/" << lop->siSoToiDa << " ---" << endl;
                cout << "Danh sach da dang ky:" << endl;
                NodeSV* p = lop->dsDaDK.head;
                if (p == nullptr) cout << "  (Trong)" << endl;
                while (p != nullptr) {
                    cout << "  - " << p->data.mssv << " | " << p->data.hoTen
                         << " (Nam " << p->data.namHoc << ")" << endl;
                    p = p->next;
                }

                cout << "Danh sach hang doi:" << endl;
                NodeSV* q = lop->hangDoi.front;
                if (q == nullptr) cout << "  (Trong)" << endl;
                while (q != nullptr) {
                    cout << "  - " << q->data.mssv << " | " << q->data.hoTen
                         << " (Nam " << q->data.namHoc << ")" << endl;
                    q = q->next;
                }
                break;
            }
            case 4:
                cout << "\n[THONG KE LOP CO TI LE DANG KY THAP]" << endl;
                thongKeLopTiLeThap(dsLop);
                break;
            case 5:
                cout << "\n[MO PHONG 10^4 SINH VIEN DANG KY]" << endl;
                moPhong10000SinhVienDangKy(dsSV, dsLop);
                break;
            case 0:
                cout << "Quay lai menu chinh..." << endl;
                break;
        }
    } while (chon != 0);
}

// ---------------------------------------------------------
// MENU CHÍNH
// ---------------------------------------------------------
void hienThiMenuChinh(HashTable& dsSV, LinkedListLop& dsLop) {
    int chon;
    do {
        cout << "\n==============================================" << endl;
        cout << "   HE THONG DANG KY HOC PHAN" << endl;
        cout << "==============================================" << endl;
        cout << "1. Phien lam viec cua Sinh Vien" << endl;
        cout << "2. Phien lam viec cua Quan Tri Vien" << endl;
        cout << "0. Luu du lieu va Thoat chuong trinh" << endl;
        cout << "==============================================" << endl;
        cout << "Nhap lua chon cua ban (0-2): ";

        chon = nhapSoTrongKhoang(0, 2);

        switch (chon) {
            case 1:
                hienThiMenuSinhVien(dsSV, dsLop);
                break;
            case 2:
                hienThiMenuQuanTri(dsSV, dsLop);
                break;
            case 0:
                cout << "Dang luu du lieu va giai phong bo nho..." << endl;
                break;
        }
    } while (chon != 0);
}