#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "DataStructures.h"

// ============================================================================
// CHỨC NĂNG: TÍNH NĂNG NÂNG CAO VÀ QUẢN LÝ BỘ NHỚ (Advanced Features & Memory Management)
// Thành viên thực hiện: Bùi Đình Khôi
// Nhánh GitHub: advanced-features
// ============================================================================

class AdvancedFeatures {
public:
    // 1. TÍNH NĂNG NÂNG CAO: Kiểm tra điều kiện ràng buộc giới hạn tín chỉ đăng ký (Tối đa 25 tín chỉ)
    static bool kiemTraGioiHanTinChi(int soTinChiDaDangKy, int soTinChiMonMoi) {
        int tongTinChi = soTinChiDaDangKy + soTinChiMonMoi;
        if (tongTinChi > 25) {
            std::cout << "\n[CANH BAO] Dang ky that bai: Tong so tin chi (" 
                      << tongTinChi << ") vuot qua gioi han cho phap (25 tin chi)!\n";
            return false;
        }
        std::cout << "\n[THONG BAO] So tin chi hợp le (" << tongTinChi << "/25 tin chi).\n";
        return true;
    }

    // 2. TÍNH NĂNG NÂNG CAO: Sắp xếp danh sách lớp học phần theo sĩ số hiện tại (Giảm dần)
    // Thuật toán sắp xếp QuickSort/std::sort với độ phức tạp O(N log N)
    static void sapXepLopTheoSiSo(std::vector<LopHocPhan>& danhSachLop) {
        std::sort(danhSachLop.begin(), danhSachLop.end(), [](const LopHocPhan& a, const LopHocPhan& b) {
            return a.siSoHienTai > b.siSoHienTai;
        });
        std::cout << "\n[INFO] Da sap xep danh sach lop hoc phan theo si so giam dan.\n";
    }

    // 3. QUẢN LÝ BỘ NHỚ: Thu hồi và giải phóng bộ nhớ động (Memory Leak Prevention)
    // Tự động thu hồi các con trỏ cấp phát động trong vector trước khi kết thúc chương trình
    template <typename T>
    static void giaiPhongBoNhoDong(std::vector<T*>& danhSachConTro) {
        int count = 0;
        for (size_t i = 0; i < danhSachConTro.size(); ++i) {
            if (danhSachConTro[i] != nullptr) {
                delete danhSachConTro[i];
                danhSachConTro[i] = nullptr;
                count++;
            }
        }
        danhSachConTro.clear();
        std::cout << "\n[MEMORY MANAGEMENT] Da giai phong " << count << " vung nho dong an toan!\n";
    }
};
