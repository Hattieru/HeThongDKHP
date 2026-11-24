#include "FileIO.h"
#include "CourseRegistration.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Xóa khoảng trắng và ký tự '\r' (CRLF của Windows) ở hai đầu chuỗi
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n')) {
        start++;
    }
    size_t end = s.size();
    while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t' || s[end - 1] == '\r' || s[end - 1] == '\n')) {
        end--;
    }
    return s.substr(start, end - start);
}

// Tách một dòng theo dấu phẩy ',' vào mảng tĩnh (không dùng std::vector)
static int tachCotCSV(const std::string& line, std::string cols[], int maxCols) {
    int count = 0;
    size_t start = 0;
    while (count < maxCols) {
        size_t pos = line.find(',', start);
        if (pos == std::string::npos) {
            cols[count++] = trim(line.substr(start));
            break;
        }
        cols[count++] = trim(line.substr(start, pos - start));
        start = pos + 1;
    }
    return count;
}

// Thêm mã môn đã học vào danh sách tiên quyết của sinh viên (nếu file có cột thứ 5 dạng: CTDL;OOP)
static void themMonDaHoc(SinhVien& sv, const std::string& danhSachMon) {
    if (danhSachMon.empty() || danhSachMon == "NONE") return;
    size_t start = 0;
    while (start < danhSachMon.size()) {
        size_t pos = danhSachMon.find(';', start);
        std::string maMon = (pos == std::string::npos)
            ? trim(danhSachMon.substr(start))
            : trim(danhSachMon.substr(start, pos - start));

        if (!maMon.empty()) {
            NodeMon* node = new NodeMon{ maMon, sv.dsMonDaHoc };
            sv.dsMonDaHoc = node;
        }
        if (pos == std::string::npos) break;
        start = pos + 1;
    }
}

// ---------------------------------------------------------
// 1. ĐỌC DỮ LIỆU KHI KHỞI ĐỘNG
// ---------------------------------------------------------
void docDuLieuKhoiDong(HashTable& dsSV, LinkedListLop& dsLop) {
    int demSV = 0, demLop = 0;

    // A. Đọc file sinhvien.txt (Định dạng: MSSV,HoTen,NamHoc,SoTinChiDaDK[,MonDaHoc1;MonDaHoc2])
    std::ifstream fSV("sinhvien.txt");
    if (fSV.is_open()) {
        std::string line;
        while (std::getline(fSV, line)) {
            line = trim(line);
            if (line.empty()) continue;

            std::string cols[6];
            int n = tachCotCSV(line, cols, 6);
            if (n >= 4) {
                SinhVien sv;
                sv.mssv = cols[0];
                sv.hoTen = cols[1];
                sv.namHoc = std::stoi(cols[2]);
                sv.soTinChiDaDK = std::stoi(cols[3]);
                sv.dsMonDaHoc = nullptr;
                if (n >= 5) {
                    themMonDaHoc(sv, cols[4]);
                }
                if (themSinhVien(dsSV, sv)) {
                    demSV++;
                }
            }
        }
        fSV.close();
    } else {
        std::cout << "=> [CANH BAO] Khong mo duoc file sinhvien.txt!\n";
    }

    // B. Đọc file lophocphan.txt
    // MaLop, TenMon, SiSoToiDa, SoTinChi, SiSoHienTai, LichHoc, MaMonTienQuyet
    std::ifstream fLop("lophocphan.txt");
    if (fLop.is_open()) {
        std::string line;
        while (std::getline(fLop, line)) {
            line = trim(line);
            if (line.empty()) continue;

            std::string cols[8];
            int n = tachCotCSV(line, cols, 8);
            if (n >= 7) {
                LopHocPhan lop;
                lop.maLop = cols[0];
                lop.maMonHoc = cols[0]; // Dùng luôn mã lớp làm mã tra cứu
                lop.tenMon = cols[1];
                lop.siSoToiDa = std::stoi(cols[2]);
                lop.soTinChi = std::stoi(cols[3]);
                int siSoCu = std::stoi(cols[4]);
                lop.lichHoc = cols[5];
                lop.maMonTienQuyet = cols[6];

                if (moLopHocPhan(dsLop, lop)) {
                    LopHocPhan* pLop = timLopHocPhan(dsLop, lop.maLop);
                    if (pLop != nullptr) {
                        pLop->siSoHienTai = siSoCu; // Giữ nguyên sĩ số hiện tại từ file
                    }
                    demLop++;
                }
            }
        }
        fLop.close();
    } else {
        std::cout << "=> [CANH BAO] Khong mo duoc file lophocphan.txt!\n";
    }

    std::cout << "=> Da nap " << demSV << " sinh vien va " << demLop << " lop hoc phan tu file.\n";
}

// ---------------------------------------------------------
// 2. GHI DỮ LIỆU KHI KẾT THÚC CHƯƠNG TRÌNH
// ---------------------------------------------------------
void ghiDuLieuKetThuc(const HashTable& dsSV, const LinkedListLop& dsLop) {
    // Ghi lại sinhvien.txt (bỏ qua các bản ghi mô phỏng SIM_SV_ để không làm rác file gốc)
    std::ofstream fSV("sinhvien.txt");
    if (fSV.is_open()) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            NodeSV* p = dsSV.buckets[i];
            while (p != nullptr) {
                if (p->data.mssv.rfind("SIM_SV_", 0) != 0) {
                    fSV << p->data.mssv << ","
                        << p->data.hoTen << ","
                        << p->data.namHoc << ","
                        << p->data.soTinChiDaDK << "\n";
                }
                p = p->next;
            }
        }
        fSV.close();
    }

    // Ghi lại lophocphan.txt (bỏ qua các lớp mô phỏng SIM_LHP_)
    std::ofstream fLop("lophocphan.txt");
    if (fLop.is_open()) {
        NodeLop* p = dsLop.head;
        while (p != nullptr) {
            if (p->data.maLop.rfind("SIM_LHP_", 0) != 0) {
                fLop << p->data.maLop << ","
                     << p->data.tenMon << ","
                     << p->data.siSoToiDa << ","
                     << p->data.soTinChi << ","
                     << p->data.siSoHienTai << ","
                     << p->data.lichHoc << ","
                     << p->data.maMonTienQuyet << "\n";
            }
            p = p->next;
        }
        fLop.close();
    }
}

// ---------------------------------------------------------
// 3. SINH FILE DỮ LIỆU MẪU LỚN (>= 10^4 BẢN GHI)
// ---------------------------------------------------------
void sinhDuLieuNgauNhien(int soLuong) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::ofstream fOut("sinhvien_lon.txt");
    if (!fOut.is_open()) return;

    for (int i = 1; i <= soLuong; ++i) {
        int nam = (std::rand() % 4) + 1;
        fOut << "2211" << (10000 + i) << ",Sinh Vien " << i << "," << nam << ",0\n";
    }
    fOut.close();
}