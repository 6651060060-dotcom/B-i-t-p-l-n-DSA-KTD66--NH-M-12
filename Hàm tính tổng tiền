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
