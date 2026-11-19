#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "DSLK.h"
#include "LopHocPhan.h"
#include <vector>
#include <string>

using namespace std;

// Sinh viên
void docFile(Node*& head);
void ghiFile(Node* head);

// Lớp học phần
void docLopHocPhan(vector<LopHocPhan>& dsLop);
void ghiLopHocPhan(vector<LopHocPhan>& dsLop);

#endif
