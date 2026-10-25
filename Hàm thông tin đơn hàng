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
