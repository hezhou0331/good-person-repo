typedef struct node{
    int data;
    struct node *next;
}Inode;
Inode* setminus(Inode *head1, Inode *head2) {
    Inode *result = nullptr;
    Inode *tail = nullptr;

    while (head1 != nullptr) {
        bool found = false;
        Inode *temp = head2;

        while (temp != nullptr) {
            if (head1->data == temp->data) {
                found = true;
                break;
            }
            temp = temp->next;
        }

        if (!found) {
            Inode *newNode = new Inode();
            newNode->data = head1->data;
            newNode->next = nullptr;

            if (result == nullptr) {
                result = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        head1 = head1->next;
    }

    return result;
}