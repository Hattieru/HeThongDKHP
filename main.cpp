#include <iostream>
#include "DataStructures.h"
#include "FileIO.h"
#include "AdvancedFeatures.h"
#include "UI.h"

using namespace std;

int main() {
    // 1. Khoi tao cac cau truc du lieu tong (khoi tao rong de tranh con tro rac)
    HashTable dsSV{};
    LinkedListSV dsLop{};

    // 2. Doc du lieu tu file text khi khoi dong chuong trinh
    docDuLieuKhoiDong(dsSV, dsLop);

    // 3. Chay giao dien menu chinh (nho cap nhat tham so nay o UI.h va UI.cpp)
    hienThiMenuChinh(dsSV, dsLop);

    // 4. Ghi lai du lieu vao file text khi thoat
    ghiDuLieuKetThuc(dsSV, dsLop);

    // 5. Giai phong toan bo bo nho cap phat dong de tranh ro ri RAM
    giaiPhongToanBoBoNho(dsSV, dsLop);

    return 0;
}
