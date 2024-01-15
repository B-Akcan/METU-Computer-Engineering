int absoluteDifference(int a, int b);
void swapTwoNumbers(unsigned short &a, unsigned short &b, long& swaps, int i1, int i2, double& avg_dist, double& max_dist);
int lomutoPartition(unsigned short* arr, int size, long& swaps, double& avg_dist, double& max_dist);
int hoarePartition(unsigned short* arr, int size, long& swaps, double& avg_dist, double& max_dist);
void selectPivot(unsigned short* arr, int size, long& swaps, double& avg_dist, double& max_dist, bool isLomuto);

int calls = 0;
int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size)
{    
    int i;
    calls++;
    
    if (size > 1)
    {
        if (hoare)
        {
            if (median_of_3 && size != 2)
                selectPivot(arr, size, swap, avg_dist, max_dist, !hoare);
                
            i = hoarePartition(arr, size, swap, avg_dist, max_dist);
            quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, i+1);
            quickSort(arr+i+1, swap, avg_dist, max_dist, hoare, median_of_3, size-i-1);
        }
        
        else
        {
            if (median_of_3 && size != 2)
                selectPivot(arr, size, swap, avg_dist, max_dist, !hoare);
                
            i = lomutoPartition(arr, size, swap, avg_dist, max_dist);
            quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, i);
            quickSort(arr+i+1, swap, avg_dist, max_dist, hoare, median_of_3, size-i-1);
        }
    }
    
    return calls;
}

void swapTwoNumbers(unsigned short &a, unsigned short &b, long& swaps, int i1, int i2, double& avg_dist, double& max_dist)
{
    unsigned short tmp;
    tmp = a;
    a = b;
    b = tmp;
    
    int res = absoluteDifference(i1, i2);
    if (res > max_dist)
        max_dist = res;
    
    double totalDistance = avg_dist * swaps;
    swaps++;
    avg_dist = (totalDistance + res) / swaps;
}

int absoluteDifference(int a, int b)
{
    return a > b ? a - b : b - a;
}

int lomutoPartition(unsigned short* arr, int size, long& swaps, double& avg_dist, double& max_dist) // <p  p  >p
{
    unsigned short P = arr[size-1];
    int i = -1;
    
    for (int j=0; j<=size-2; j++)
    {
        if (arr[j] >= P)
        {
            i++;
            swapTwoNumbers(arr[i], arr[j], swaps, i, j, avg_dist, max_dist);
        }
    }
    
    swapTwoNumbers(arr[i+1], arr[size-1], swaps, i+1, size-1, avg_dist, max_dist);
    return i+1; // returns index of p
}

int hoarePartition(unsigned short* arr, int size, long& swaps, double& avg_dist, double& max_dist) // <p  p  >p
{
    unsigned short P = arr[(size-1)/2];
    int i = -1;
    int j = size;
    
    
    while (true)
    {
        do j--;
        while (arr[j] < P);
        
        do i++;
        while (arr[i] > P);
        
        if (i < j)
            swapTwoNumbers(arr[i], arr[j], swaps, i, j, avg_dist, max_dist);
        else
            return j;
    }
}

void selectPivot(unsigned short* arr, int size, long& swaps, double& avg_dist, double& max_dist, bool isLomuto) // returns the index of pivot
{
    unsigned short p1 = arr[0], p2 = arr[(size-1)/2], p3 = arr[size-1];
    
    if (isLomuto)
    {
        if ((p3 > p1 && p1 > p2) || (p2 > p1 && p1 > p3))
            swapTwoNumbers(arr[0], arr[size-1], swaps, 0, size-1, avg_dist, max_dist);
        else if ((p1 > p2 && p2 > p3) || (p3 > p2 && p2 > p1))
            swapTwoNumbers(arr[(size-1)/2], arr[size-1], swaps, (size-1)/2, size-1, avg_dist, max_dist); 
    }
    
    else
    {
        if ((p2 > p1 && p1 > p3) || (p3 > p1 && p1 > p2))
            swapTwoNumbers(arr[0], arr[(size-1)/2], swaps, 0, (size-1)/2, avg_dist, max_dist);
        else if ((p1 > p3 && p3 > p2) || (p2 > p3 && p3 > p1))
            swapTwoNumbers(arr[(size-1)/2], arr[size-1], swaps, (size-1)/2, size-1, avg_dist, max_dist);
    }
    
}
