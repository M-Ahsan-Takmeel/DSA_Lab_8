#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) {
        val = v;
        next = NULL;
    }
};

class MinHeap {
    ListNode* arr[100];
    int size;

public:
    MinHeap() { size = 0; }

    bool empty() { return size == 0; }

    void push(ListNode* n) {
        int i = size++;
        arr[i] = n;
        while (i > 0 && arr[(i - 1) / 2]->val > arr[i]->val) {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    ListNode* pop() {
        ListNode* top = arr[0];
        arr[0] = arr[--size];
        int i = 0;
        while (true) {
            int l = 2 * i + 1, r = 2 * i + 2, small = i;
            if (l < size && arr[l]->val < arr[small]->val) small = l;
            if (r < size && arr[r]->val < arr[small]->val) small = r;
            if (small == i) break;
            swap(arr[i], arr[small]);
            i = small;
        }
        return top;
    }
};

ListNode* mergeKLists(ListNode* lists[], int k) {
    MinHeap heap;
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL) heap.push(lists[i]);
    }

    ListNode* head = NULL;
    ListNode* tail = NULL;

    while (!heap.empty()) {
        ListNode* cur = heap.pop();
        if (head == NULL) {
            head = tail = cur;
        } else {
            tail->next = cur;
            tail = cur;
        }
        if (cur->next != NULL) heap.push(cur->next);
    }
    return head;
}

ListNode* readList() {
    int n;
    cin >> n;
    ListNode* head = NULL;
    ListNode* tail = NULL;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        ListNode* node = new ListNode(x);
        if (head == NULL) head = tail = node;
        else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

int main() {
    int k;
    cout << "Enter number of lists: ";
    cin >> k;
    ListNode* lists[100];
    for (int i = 0; i < k; i++) {
        cout << "List " << i + 1 << " (size then sorted elements): ";
        lists[i] = readList();
    }

    ListNode* res = mergeKLists(lists, k);
    cout << "Merged list: ";
    while (res != NULL) {
        cout << res->val << " ";
        res = res->next;
    }
    cout << endl;
    return 0;
}
