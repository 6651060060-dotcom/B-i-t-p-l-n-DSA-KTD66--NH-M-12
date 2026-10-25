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
