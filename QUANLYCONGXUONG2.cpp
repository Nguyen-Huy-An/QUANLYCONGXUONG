#include <iostream>
#include <vector>
using namespace std;

class NhanVien {
protected:
    string id;
    string ten;
    int tuoi;
    string diaChi;
    string soDienThoai;
    int ngayCong;
    int meme = 250000;
public:
    NhanVien(string _id, string _ten, int _tuoi, string _diaChi, string _soDienThoai, int _ngayCong)
        : id(_id), ten(_ten), tuoi(_tuoi), diaChi(_diaChi), soDienThoai(_soDienThoai), ngayCong(_ngayCong) {}
	float tinhLuong(){
		return ngayCong*meme;
	}
    virtual void thongTin() {
        cout << "ID: " << id << ", Ten: " << ten << ", Tuoi: " << tuoi << ", Dia chi: " << diaChi << ", So dien thoai: " << soDienThoai << ", Ngay cong: " << ngayCong << endl;
    }
    bool kiemTraID(const string& otherID) const {
        return (id == otherID);}
    string getId() const {
        return id;}
    string getTen() const {
        return ten;}
};
class CongNhan : public NhanVien {
public:
    CongNhan(string _id, string _ten, int _tuoi, string _diaChi, string _soDienThoai, int _ngayCong)
        : NhanVien(_id, _ten, _tuoi, _diaChi, _soDienThoai, _ngayCong) {}
};
class QuanLy : public NhanVien {
public:
    QuanLy(string _id, string _ten, int _tuoi, string _diaChi, string _soDienThoai, int _ngayCong)
        : NhanVien(_id, _ten, _tuoi, _diaChi, _soDienThoai, _ngayCong) {}
};
class MatHang {
private:
    string id;
    string tenMatHang;
    int gia;
public:
    MatHang(string _id, string _tenMatHang, int _gia)
        : id(_id), tenMatHang(_tenMatHang), gia(_gia) {}

    void thongTin() {
        cout << "ID: " << id << ", Ten mat hang: " << tenMatHang << ", Gia: " << gia << endl;
    }
    bool kiemTraID(const string& otherID) const {
        return id == otherID;}
};
class PhongBan {
private:
    vector<MatHang*> danhSachSanPham;
    vector<NhanVien*> nhanVienSanPham;
    QuanLy* quanLy;
public:
	string tenPhongBan;
    PhongBan(string _tenPhongBan) : tenPhongBan(_tenPhongBan), quanLy(NULL) {}

    void themNhanVien(NhanVien* nv) {
        if (dynamic_cast<QuanLy*>(nv) != NULL) {
            if (quanLy == NULL) {
                quanLy = dynamic_cast<QuanLy*>(nv);
                nhanVienSanPham.push_back(nv);
            } else {
                cout << "Phong ban da co quan ly!" << endl;
            }
        } else {
            nhanVienSanPham.push_back(nv);
        }
    }

    void hienThiThongTinPhongBan() {
    cout << "Thong tin phong ban " << tenPhongBan << ":" << endl;
    if (quanLy != NULL) {
        cout << "Quan ly: " << quanLy->getTen() << endl;
        
    } else {
        cout << "Chua co quan ly." << endl;
    }

    // Hi?n th? danh sách nhân viên
    cout << "Danh sach nhan vien:" << endl;
    for (int i = 0; i < nhanVienSanPham.size(); i++) {
        nhanVienSanPham[i]->thongTin();
    }

    // Hi?n th? danh sách s?n ph?m
    cout << "Danh sach san pham:" << endl;
    for (int i = 0; i < danhSachSanPham.size(); i++) {
        danhSachSanPham[i]->thongTin();
    }
}

	QuanLy* getQuanLy() const {
        return quanLy;
    }
	void themSanPham(MatHang* sanPham) {
        danhSachSanPham.push_back(sanPham);
    }
};

class CongXuong {
private:
    vector<NhanVien*> nhanVien;
    vector<MatHang> matHang;
    vector<PhongBan> phongBan;
public:
	void themPhongBan(const string& tenPhongBan) {
        phongBan.push_back(PhongBan(tenPhongBan));
    };
    void themNhanVien() {
        string id, ten, diaChi, soDienThoai;
        int tuoi, ngayCong;

        cout << "Nhap ID nhan vien: ";
        cin >> id;
        cout << "Nhap ten nhan vien: ";
        cin.ignore();
        getline(cin, ten);
        cout << "Nhap tuoi nhan vien: ";
        cin >> tuoi;
        cout << "Nhap dia chi nhan vien: ";
        cin.ignore();
        getline(cin, diaChi);
        cout << "Nhap so dien thoai nhan vien: ";
        cin >> soDienThoai;
        cout << "Nhap so ngay cong: ";
        cin >> ngayCong;

        cout << "Chon loai nhan vien (1 - Cong nhan, 2 - Quan ly): ";
        int choice;
        cin >> choice;

        NhanVien* nv;
if (choice == 1) {
	cout << "Danh sach phong ban:" << endl;
    for (size_t i = 0; i < phongBan.size(); i++) {
        cout << i << ". " << phongBan[i].tenPhongBan << endl;
    }
	cout << "Chon phong ban (0 - " << phongBan.size()-1 << "): ";
    int pbChoice;
    cin >> pbChoice;
    if (pbChoice >= 0 && pbChoice < phongBan.size()) {
        nv = new CongNhan(id, ten, tuoi, diaChi, soDienThoai, ngayCong);
        phongBan[pbChoice].themNhanVien(nv);
        nhanVien.push_back(nv);
    } else {
        cout << "Nhap khong hop le" << endl;
    }
} else if (choice == 2) {
	cout << "Danh sach phong ban:" << endl;
    for (size_t i = 0; i < phongBan.size(); i++) {
        cout << i << ". " << phongBan[i].tenPhongBan << endl;
    }
    cout << "Chon phong ban (0 - " << phongBan.size() - 1 << "): ";
    int pbChoice;
    cin >> pbChoice;
 
    if (pbChoice >= 0 && pbChoice < phongBan.size()) {
        if (phongBan[pbChoice].getQuanLy() == NULL) {
            nv = new QuanLy(id, ten, tuoi, diaChi, soDienThoai, ngayCong);
            phongBan[pbChoice].themNhanVien(nv);
            nhanVien.push_back(nv);
        } else {
            cout << "Phong ban da co quan ly!" << endl;
            return;
        }
    } else {
        cout << "Nhap khong hop le" << endl;
        return;
    }
} else {
    cout << "Lua chon khong hop li!" << endl;
    return;
}}
    void themSanPham() {
        string id, tenMatHang;
        float gia;
        cout << "Nhap ID mat hang: ";
        cin >> id;
        cout << "Nhap ten mat hang: ";
        cin.ignore();
        getline(cin, tenMatHang);
        cout << "Nhap gia mat hang: ";
        cin >> gia;

        MatHang matHangMoi(id, tenMatHang, gia);
        matHang.push_back(matHangMoi);

        cout << "Mat hang da duoc them vào cong xuong." << endl;
    }

    void tinhLuong() {
        int tongLuong = 0;
        int tinhluong;
        for (int i = 0; i < nhanVien.size(); i++) 
            tongLuong += nhanVien[i]->tinhLuong();
        cout<<"Tien Luong: "<<tongLuong<<endl;
	};
	

    void giaoSanPhamChoPhongBan() {
    	cout<< "Giao San Pham cho phan khu"<<endl;
    if (matHang.empty()) {
        cout << "Khong co san pham trong cong xuong." << endl;
        return;
    }

    cout << "Danh sach san pham trong cong xuong:" << endl;
    for (size_t i = 0; i < matHang.size(); i++) {
        cout << "San pham thu" << i + 1 << ":" << endl;
        matHang[i].thongTin();
    }

    cout << "Chon san pham (nhap ID): ";
    string id;
    cin >> id;

    int index = -1;
    for (size_t i = 0; i < matHang.size(); i++) {
        if (matHang[i].kiemTraID(id)) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay san pham có ID tuong ung." << endl;
        return;
    }

    cout << "Danh sach phong ban:" << endl;
    for (size_t i = 0; i < phongBan.size(); i++) {
        cout << i << ". " << phongBan[i].tenPhongBan << endl;
    }

    cout << "Chon phong ban (nhap so): ";
    int phongBanIndex;
    cin >> phongBanIndex;

    phongBan[phongBanIndex].themSanPham(&matHang[index]);
    cout << "San pham da duoc giao cho phong ban " << phongBan[phongBanIndex].tenPhongBan << "." << endl;
}

    void hienThiDanhSachNhanVien() {
    cout << "Danh sach nhan vien trong cong xuong:" << endl;
    for (size_t i = 0; i < nhanVien.size(); i++) {
        cout << "Nhan vien " << i + 1 << ":" << endl;
        nhanVien[i]->thongTin();
    }
}
    void hienThiDanhSachSanPham() {
    cout << "Danh sach san pham trong cong xuong:" << endl;
    for (size_t i = 0; i < matHang.size(); i++) {
        cout << "San pham " << i + 1 << ":" << endl;
        matHang[i].thongTin();
    }
}

	
    void timKiemNhanVien() {
    string id;
    cout << "Nhap ID nhan vien can tim: ";
    cin >> id;

    bool found = false;
    for (size_t i = 0; i < nhanVien.size(); i++) {
        if (nhanVien[i]->kiemTraID(id)) {
            cout << "Thong tin nhan vien " << i + 1 << ":" << endl;
            nhanVien[i]->thongTin();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay nhan vien co ID tuong ung." << endl;
    }
}
  	void hienThiThongTinPhongBan() {
        cout << "Danh sach phong ban: " << endl;
        for (int i = 0; i < phongBan.size(); i++) {
            phongBan[i].hienThiThongTinPhongBan();
            cout << endl;
        }
    }

    void timKiemSanPham() {
    string id;
    cout << "Nhap ID san pham can tim: ";
    cin >> id;

    bool found = false;
    for (size_t i = 0; i < matHang.size(); i++) {
        if (matHang[i].kiemTraID(id)) {
            cout << "Thong tin san pham " << i + 1 << ":" << endl;
            matHang[i].thongTin();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay san pham có ID tuong ung." << endl;
    }
}
};
int main() {
    CongXuong congXuong;
    string _tenPhongBan = "Ten cua phong ban";
   	PhongBan phongBan(_tenPhongBan);
    int N,m;
    cout << "Nhap so luong phong ban: ";
    cin >> N;
    vector<PhongBan> danhSachPhongBan;
	cin.ignore();
    for (int i = 1; i <= N; i++) {
        string tenPhongBan;
        cout << "Nhap ten phong ban thu " << i << ": ";
        
        getline(cin, tenPhongBan);
        PhongBan phongBan(_tenPhongBan);
        congXuong.themPhongBan(tenPhongBan);
    }
    int choice;

    do {
        cout << "-----QUANLYCONGXUONG-----" << endl;
        cout << "1. Them nhan vien vao cong xuong" << endl;
        cout << "2. Them san pham vao cong xuong" << endl;
        cout << "3. Hien thi danh sach nhan vien" << endl;
        cout << "4. Hien thi danh sach san pham" << endl;
        cout << "5. Tim kiem nhan vien" << endl;
        cout << "6. Tim kiem san pham" << endl;
        cout << "7. Hien thi thong tin phong ban"<<endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "-----------------" << endl;
        cout << "Nhap so: ";
        cin >> choice;
      
        switch (choice) {
            case 1:
            	cout<<"Nhap so nhan vien can them"<<endl;
            	cin>>m;
            	for (int i = 1; i <= m; i++) {
                congXuong.themNhanVien();}
                break;
            case 2:
                congXuong.themSanPham();
				congXuong.giaoSanPhamChoPhongBan();
                break;
            case 3:
                congXuong.hienThiDanhSachNhanVien();
                break;
            case 4:
                congXuong.hienThiDanhSachSanPham();
                break;
            case 5:
                congXuong.timKiemNhanVien();
                congXuong.tinhLuong();
                break;
            case 6:
                congXuong.timKiemSanPham();
                
                break;
            case 7:
            	congXuong.hienThiThongTinPhongBan();
    			break;
            	
            case 0:
                cout << "Chuong trinh da thoat." << endl;
                break;
            default:
                cout << "Lua chon không hop li!" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
