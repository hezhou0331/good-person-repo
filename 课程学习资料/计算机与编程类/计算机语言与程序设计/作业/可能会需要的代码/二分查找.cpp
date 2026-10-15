//二分查找（arr数组，l为左边界，r为右边界，x为要查找的元素的下标）
int binarySearch(int arr[], int l, int r, int x) {
    while (l <= r) {
        int m = l + (r - l) / 2;

        if (arr[m] == x) return m;

        if (arr[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
