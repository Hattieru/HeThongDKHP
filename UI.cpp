#include <iostream>
#include <string>
#include "UI.h"
#include "CourseRegistration.h" 
#include "AdvancedFeatures.h"
#include "DataStructures.h"

using namespace std;

int nhapLuaChonMenu(int minVal, int maxVal) {
    int luaChon;
    while (true) {
        cin >> luaChon;        
        // Nếu người dùng nhập sai kiểu (VD: nhập chữ 'a' thay vì số 1)
        if (cin.fail()) {
            cin.clear(); // Xóa cờ lỗi
            cin.ignore(10000, '\n'); // Bỏ qua phần dữ liệu rác trong buffer
            cout << "=> [LOI] Vui long nhap vao mot so nguyen! Nhap lai: ";
        } 
        // Nếu người dùng nhập số nhưng ngoài phạm vi menu (Sai miền)
        else if (luaChon < minVal || luaChon > maxVal) {
            cout << "=> [LOI] Lua chon phai tu " << minVal << " den " << maxVal << ". Nhap lai: ";
        } 
        // Dữ liệu hợp lệ
        else {
            cin.ignore(10000, '\n');
            return luaChon;
        }
    }
}
void hienThiMenuSinhVien(/* Tham chieu den danh sach can thiet */) {
    int chon;
    string mssv, maLop;

    cout << "\n--- XAC THUC SINH VIEN ---" << endl;
    cout << "Nhap MSSV cua ban: ";
    getline(cin, mssv);
    // !Hàm kiểm tra xem MSSV có trong HashTable không!

    do {
        cout << "\n========== MENU SINH VIEN ==========" << endl;
        cout << "1. Dang ky hoc phan" << endl;
        cout << "2. Huy dang ky hoc phan" << endl;
        cout << "3. Xem thoi khoa bieu" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "====================================" << endl;
        cout << "Nhap lua chon cua ban (0-3): ";
        
        chon = nhapLuaChonMenu(0, 3);

        switch (chon) {
            case 1: {
                cout << "\n[DANG KY HOC PHAN]" << endl;
                cout << "Nhap Ma Lop Hoc Phan muon dang ky: ";
                getline(cin, maLop);
                
                // GỌI HÀM LÕI (Ví dụ)
                // int kq = dangKyHocPhan(mssv, maLop);
                // if(kq == 1) cout << "Dang ky thanh cong!" << endl;
                // else if(kq == 2) cout << "Lop day! Ban da vao hang doi." << endl;
                // else cout << "Loi: Vi pham dieu kien tien quyet/trung lich." << endl;
                cout << "=> Dang goi ham dang ky..." << endl;
                break;
            }
            case 2:
                cout << "\n[HUY DANG KY HOC PHAN]" << endl;
                // Hàm huyDangKy(mssv, maLop)
                break;
            case 3:
                cout << "\n[XEM THOI KHOA BIEU]" << endl;
                // Hàm inThoiKhoaBieu(mssv)
                break;
            case 0:
                cout << "Quay lai..." << endl;
                break;
        }
    } while (chon != 0);
}
void hienThiMenuQuanTri() {
    int chon;
    do {
        cout << "\n========= MENU QUAN TRI VIEN =========" << endl;
        cout << "1. Mo lop hoc phan moi" << endl;
        cout << "2. Xem danh sach sinh vien cua 1 lop" << endl;
        cout << "3. Thong ke cac lop co ti le dang ky thap" << endl;
        cout << "4. Chay mo phong 10^4 sinh vien dang ky" << endl;
        cout << "0. Quay lai menu chinh" << endl;
        cout << "======================================" << endl;
        cout << "Nhap lua chon cua ban (0-4): ";
        
        chon = nhapLuaChonMenu(0, 4);

        switch (chon) {
            case 1:
                cout << "\n[MO LOP HOC PHAN] (Chuc nang dang xay dung...)" << endl;
                break;
            case 2:
                cout << "\n[XEM DANH SACH LOP] (Chuc nang dang xay dung...)" << endl;
                break;
            case 3:
                cout << "\n[THONG KE LOP HUY] (Chuc nang dang xay dung...)" << endl;
                break;
            case 4:
                cout << "\n[MO PHONG THUC NGHIEM] (Chuc nang dang xay dung...)" << endl;
                break;
        }
    } while (chon != 0);
}
void hienThiMenuChinh(/* Trùng các danh sách dữ liệu từ main vào đây */) {
    int chon;
    do {
        cout << "\n==============================================" << endl;
        cout << "   HE THONG DANG KY HOC PHAN - Nhom X" << endl;
        cout << "==============================================" << endl;
        cout << "1. Phien lam viec cua Sinh Vien" << endl;
        cout << "2. Phien lam viec cua Quan Tri Vien" << endl;
        cout << "0. Luu du lieu va Thoat chuong trinh" << endl;
        cout << "==============================================" << endl;
        cout << "Nhap lua chon cua ban (0-2): ";
        
        chon = nhapLuaChonMenu(0, 2);

        switch (chon) {
            case 1:
                hienThiMenuSinhVien();
                break;
            case 2:
                hienThiMenuQuanTri();
                break;
            case 0:
                cout << "Dang luu du lieu..." << endl;
                cout << "Tam biet! Chuong trinh ket thuc." << endl;
                break;
        }
    } while (chon != 0);
}