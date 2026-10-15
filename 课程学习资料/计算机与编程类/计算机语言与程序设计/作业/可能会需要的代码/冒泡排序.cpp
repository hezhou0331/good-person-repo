此处的代码都是从小到大排序
//int类型的冒泡排序
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//char类型冒泡排序
void bubbleSort(char arr[], int n) {
    int i, j;
	char temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//给定 索引row[i]=i 类型 
//int
void bubbleSort(int arr[], int n，int row[100]) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
				temp=row[j];
				row[j]=row[j+1];
				row[j+1]=temp;
            }
        }
    }
}
//char
void bubbleSort(char arr[], int n,int row[]) {
    int i, j;
	char temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
				temp=row[j];
				row[j]=row[j+1];
				row[j+1]=temp;
            }
        }
    }
}