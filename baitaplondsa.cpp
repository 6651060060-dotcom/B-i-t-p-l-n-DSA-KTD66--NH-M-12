#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Fix loi chuyen so sang chuoi
string numToString(long long n) {
    if (n == 0) return "0";
    bool isNegative = false;
    if (n < 0) {
        isNegative = true;
        n = -n;
    }
    string res = "";
    while (n > 0) {
        char digit = '0' + (n % 10);
        res = digit + res;
        n /= 10;
    }
    if (isNegative) res = "-" + res;
    return res;
}

// Ham them khoang trang can le bang
string khoangTrang(string str, int width) {
    if ((int)str.length() >= width) return str;
    return str + string(width - str.length(), ' ');
}

// 1. Khai bao bien cho cac mon hang (Item Node)
struct ItemNode {
    int id;
    string name;
    double price;
    int soLuong;
    ItemNode* next;

    ItemNode(int id, string name, double price, int soLuong)
        : id(id), name(name), price(price), soLuong(soLuong), next(NULL) {}
};

// 2. Gio hang
class ShoppingCart {
private:
    ItemNode* head;

public:
    ShoppingCart() : head(NULL) {}

    ~ShoppingCart() {
        clear();
    }

    void clear() {
        ItemNode* current = head;
        while (current != NULL) {
            ItemNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = NULL;
    }

    void addItem(int id, string name, double price, int soLuong) {
        if (soLuong <= 0) {
            cout << "-> Loi: So luong phai lon hon 0!\n";
            return;
        }
        ItemNode* current = head;
        while (current != NULL) {
            if (current->id == id) {
                current->soLuong += soLuong;
                cout << "-> Da cap nhat so luong san pham \"" << name << "\" trong gio: " << current->soLuong << "\n";
                return;
            }
            current = current->next;
        }

        ItemNode* newItem = new ItemNode(id, name, price, soLuong);
        if (head == NULL) {
            head = newItem;
        } else {
            ItemNode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newItem;
        }
        cout << "-> Da them mon \"" << name << "\" vao gio hang!\n";
    }

    // Ham cap nhat so luong san pham
    bool capNhatSoLuong(int id, int soLuongMoi) {
        ItemNode* current = head;
        while (current != NULL) {
            if (current->id == id) {
                if (soLuongMoi <= 0) {
                    removeItem(id);
                    cout << "-> So luong <= 0, da xoa san pham khoi gio hang.\n";
                } else {
                    current->soLuong = soLuongMoi;
                    cout << "-> Da cap nhat so luong san pham [Ma " << id << "] thanh: " << soLuongMoi << "\n";
                }
                return true;
            }
            current = current->next;
        }
        cout << "-> Khong tim thay san pham co ma " << id << " trong gio hang!\n";
        return false;
    }

    bool removeItem(int id) {
        if (head == NULL) return false;

        if (head->id == id) {
            ItemNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        ItemNode* current = head;
        while (current->next != NULL && current->next->id != id) {
            current = current->next;
        }
        if (current->next != NULL) {
            ItemNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
        return false;
    }

    double tinhTongTien() const {
        double total = 0;
        ItemNode* current = head;
        while (current != NULL) {
            total += current->price * current->soLuong;
            current = current->next;
        }
        return total;
    }

    bool isEmpty() const {
        return head == NULL;
    }

    ItemNode* copyItems() const {
        if (head == NULL) return NULL;

        ItemNode* newHead = new ItemNode(head->id, head->name, head->price, head->soLuong);
        ItemNode* currentOld = head->next;
        ItemNode* currentNew = newHead;

        while (currentOld != NULL) {
            currentNew->next = new ItemNode(currentOld->id, currentOld->name, currentOld->price, currentOld->soLuong);
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
        return newHead;
    }

    void display() const {
        if (head == NULL) {
            cout << "\n[!] Gio hang hien dang rong!\n";
            return;
        }
        cout << "\n================ CHI TIET GIO HANG HIEN TAI ================\n";
        cout << khoangTrang("Ma SP", 10)
             << khoangTrang("Ten san pham", 25)
             << khoangTrang("Don gia (VND)", 15)
             << khoangTrang("So luong", 12)
             << khoangTrang("Thanh tien", 15) << endl;
        cout << string(77, '-') << endl;

        ItemNode* current = head;
        while (current != NULL) {
            cout << khoangTrang(numToString(current->id), 10)
                 << khoangTrang(current->name, 25)
                 << khoangTrang(numToString((long long)current->price), 15)
                 << khoangTrang(numToString(current->soLuong), 12)
                 << khoangTrang(numToString((long long)(current->price * current->soLuong)), 15) << endl;
            current = current->next;
        }
        cout << string(77, '-') << endl;
        cout << "TONG TIEN: " << numToString((long long)tinhTongTien()) << " VND\n";
        cout << "=============================================================\n";
    }
};

// 3. CAU TRUC DON HANG (Order Node)
struct OrderNode {
    int orderId;
    string customerName;
    ItemNode* itemsHead;
    double totalAmount;
    OrderNode* next;

    OrderNode(int id, string custName, ItemNode* items, double total)
        : orderId(id), customerName(custName), itemsHead(items), totalAmount(total), next(NULL) {}

    ~OrderNode() {
        ItemNode* current = itemsHead;
        while (current != NULL) {
            ItemNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

// 4. HANG DOI THANH TOAN (Order Queue - FIFO)
class OrderQueue {
private:
    OrderNode* front;
    OrderNode* rear;

    template <typename T>
    void mySwap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    OrderQueue() : front(NULL), rear(NULL) {}

    ~OrderQueue() {
        while (!isEmpty()) {
            xoaDonDau();
        }
    }

    bool isEmpty() const {
        return front == NULL;
    }

    void hangDoi(int orderId, string customerName, ItemNode* items, double total) {
        OrderNode* newOrder = new OrderNode(orderId, customerName, items, total);
        if (rear == NULL) {
            front = rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }
        cout << "-> Da dua don hang #" << orderId << " cua khach hang [" << customerName << "] vao Hang doi thanh toan.\n";
    }

    void xuLyGiaoDich() {
        if (isEmpty()) {
            cout << "\n[!] Hang doi thanh toan dang trong!\n";
            return;
        }

        OrderNode* orderToProcess = front;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }

        cout << "\n======================================================\n";
        cout << "   XU LY GIAO DICH THANH TOAN DON HANG #" << orderToProcess->orderId << "\n";
        cout << " Khach hang: " << orderToProcess->customerName << "\n";
        cout << "------------------------------------------------------\n";
        cout << khoangTrang("Ma SP", 8)
             << khoangTrang("Ten san pham", 20)
             << khoangTrang("Don gia", 12)
             << khoangTrang("SL", 8)
             << khoangTrang("Thanh tien", 15) << "\n";

        ItemNode* item = orderToProcess->itemsHead;
        while (item != NULL) {
            cout << khoangTrang(numToString(item->id), 8)
                 << khoangTrang(item->name, 20)
                 << khoangTrang(numToString((long long)item->price), 12)
                 << khoangTrang(numToString(item->soLuong), 8)
                 << khoangTrang(numToString((long long)(item->price * item->soLuong)), 15) << "\n";
            item = item->next;
        }

        cout << "------------------------------------------------------\n";
        cout << "TONG TIEN THANH TOAN: " << numToString((long long)orderToProcess->totalAmount) << " VND\n";
        cout << "-> Xu ly thanh toan don hang #" << orderToProcess->orderId << " thanh cong!\n";
        cout << "======================================================\n";

        delete orderToProcess;
    }

    void xoaDonDau() {
        if (isEmpty()) return;
        OrderNode* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
    }

    void sapXepTheoTongTien(bool giamDan = true) {
        if (front == NULL || front->next == NULL) {
            cout << "-> Hang doi rong hoac chi co 1 don, khong can sap xep.\n";
            return;
        }

        for (OrderNode* i = front; i != NULL; i = i->next) {
            for (OrderNode* j = i->next; j != NULL; j = j->next) {
                bool shouldSwap = giamDan ? (i->totalAmount < j->totalAmount) : (i->totalAmount > j->totalAmount);
                if (shouldSwap) {
                    mySwap(i->orderId, j->orderId);
                    mySwap(i->customerName, j->customerName);
                    mySwap(i->itemsHead, j->itemsHead);
                    mySwap(i->totalAmount, j->totalAmount);
                }
            }
        }
        cout << "-> Da sap xep hang doi don hang theo Tong tien (" << (giamDan ? "Giam dan" : "Tang dan") << ") thanh cong!\n";
    }

    void displayQueue() const {
        if (isEmpty()) {
            cout << "\n[!] Hang doi thanh toan hien dang rong!\n";
            return;
        }
        cout << "\n=========== DANH SACH DON HANG DANG CHO THANH TOAN (QUEUE) ===========\n";
        cout << khoangTrang("Ma Don", 10)
             << khoangTrang("Ten Khach Hang", 25)
             << khoangTrang("Tong Tien (VND)", 20) << endl;
        cout << string(60, '-') << endl;

        OrderNode* current = front;
        while (current != NULL) {
            cout << khoangTrang(numToString(current->orderId), 10)
                 << khoangTrang(current->customerName, 25)
                 << khoangTrang(numToString((long long)current->totalAmount), 20) << endl;
            current = current->next;
        }
        cout << string(60, '-') << endl;
    }
};

// 5. CHUONG TRINH CHINH (MAIN MENU)
int main() {
    ShoppingCart cart;
    OrderQueue queue;
    int autoOrderId = 101;
    int choice;

    do {
        cout << "\n======================================================\n";
        cout << "   HE THONG QUAN LY GIO HANG & HANG DOI THANH TOAN    \n";
        cout << "======================================================\n";
        cout << " 1. Them san pham vao Gio hang\n";
        cout << " 2. Cap nhat so luong san pham trong Gio hang\n";
        cout << " 3. Xoa san pham khoi Gio hang\n";
        cout << " 4. Xem chi tiet Gio hang hien tai\n";
        cout << " 5. Chuyen Gio hang thanh Don hang (Dua vao Hang doi)\n";
        cout << " 6. Xem danh sach Hang doi thanh toan (Queue)\n";
        cout << " 7. Sap xep Don hang theo Tong tien (Giam dan)\n";
        cout << " 8. Xu ly thanh toan don hang dau tien (FIFO)\n";
        cout << " 0. Thoat chuong trinh\n";
        cout << "======================================================\n";
        cout << " Lua chon cua ban: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            int id, qty;
            string name;
            double price;
            cout << " Nhap Ma san pham (int): "; cin >> id;
            cin.ignore();
            cout << " Nhap Ten san pham: "; getline(cin, name);
            cout << " Nhap Don gia (VND): "; cin >> price;
            cout << " Nhap So luong: "; cin >> qty;
            cart.addItem(id, name, price, qty);
            break;
        }
        case 2: {
            int id, qty;
            cout << " Nhap Ma san pham can cap nhat: "; cin >> id;
            cout << " Nhap So luong moi: "; cin >> qty;
            cart.capNhatSoLuong(id, qty);
            break;
        }
        case 3: {
            int id;
            cout << " Nhap Ma san pham can xoa: "; cin >> id;
            if (cart.removeItem(id)) {
                cout << "-> Da xoa san pham [Ma " << id << "] khoi gio hang!\n";
            } else {
                cout << "-> Khong tim thay san pham co ma " << id << "!\n";
            }
            break;
        }
        case 4: {
            cart.display();
            break;
        }
        case 5: {
            if (cart.isEmpty()) {
                cout << "-> Gio hang dang rong, khong the tao don hang!\n";
            } else {
                cin.ignore();
                string custName;
                cout << " Nhap Ten khach hang: ";
                getline(cin, custName);

                ItemNode* itemsCopy = cart.copyItems();
                double total = cart.tinhTongTien();
                queue.hangDoi(autoOrderId++, custName, itemsCopy, total);

                cart.clear();
                cout << "-> Gio hang da duoc lam rong de san sang cho lan mua tiep theo.\n";
            }
            break;
        }
        case 6: {
            queue.displayQueue();
            break;
        }
        case 7: {
            queue.sapXepTheoTongTien(true);
            break;
        }
        case 8: {
            queue.xuLyGiaoDich();	
            break;
        }
        case 0:
            cout << "Cam on ban da su dung he thong!\n";
            break;
        default:
            cout << "Lua chon khong hop le, vui long thu lai!\n";
        }
    } while (choice != 0);

    return 0;
}
