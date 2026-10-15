//int类型倒序
void reverseArray(int arr[], int size) {
    int start = 0;        
    int end = size - 1;    
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

//char类型倒序
void reverse(char arr[]) {
    int start = 0;         
    int end =strlen(arr)-1;    
    while (start < end) {
        char temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // 移动索引
        start++;
        end--;
    }
}