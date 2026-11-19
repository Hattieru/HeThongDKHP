#include "FileManager.h"

int main()
{
    Node* head = NULL;

    docFile(head);

    int choice;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Hien thi danh sach\n";
        cout << "2. Them sinh vien\n";
        cout << "3. Tim sinh vien\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                cout << "\n===== DANH SACH SINH VIEN =====\n";
                hienThi(head);
                break;
            }

            case 2:
            {
                SinhVien sv;

                cout << "Nhap MSSV: ";
                cin >> sv.mssv;

                cin.ignore();

                cout << "Nhap ho ten: ";
                getline(cin, sv.hoTen);

                cout << "Nhap tin chi: ";
                cin >> sv.tinChi;

                themCuoi(head, sv);

                ghiFile(head);

                cout << "\nThem thanh cong!\n";
                break;
            }

            case 3:
            {
                string ma;

                cout << "Nhap MSSV can tim: ";
                cin >> ma;

                Node* kq = timSinhVien(head, ma);

                if(kq != NULL)
                {
                    cout << "\nTim thay:\n";

                    cout
                        << kq->data.mssv
                        << " - "
                        << kq->data.hoTen
                        << " - "
                        << kq->data.tinChi
                        << endl;
                }
                else
                {
                    cout << "\nKhong tim thay sinh vien!\n";
                }

                break;
            }

            case 0:
            {
                cout << "\nTam biet!\n";
                break;
            }

            default:
            {
                cout << "\nLua chon khong hop le!\n";
            }
        }

    } while(choice != 0);

    return 0;
}