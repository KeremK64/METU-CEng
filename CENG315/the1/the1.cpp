int numberOfRecs = 0;
double totalSwaps = 0.0;
double maxSwapDistance = 0;

template <typename T>
T abs(T n)
{
    if (n < 0)
    {
        return -n;
    }
    else
    {
        return n;
    }
}

void swap1(unsigned short *p, unsigned short *q)
{
    unsigned short tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

int findMedianIndex(unsigned short *arr, int start, int end)
{
    unsigned short first = arr[start];
    unsigned short last = arr[end];
    unsigned short middle = arr[start + (end - start) / 2];

    if ((first >= middle && first <= last) || (first <= middle && first >= last))
        return start;
    else if ((middle >= first && middle <= last) || (middle <= first && middle >= last))
        return start + (end - start) / 2;
    else
        return end;
}

int StandartPartition(unsigned short *arr, int start, int size, long &swap, double &avg_dist, double &max_dist, bool median_of_3)
{

    unsigned short x;
    if (median_of_3 && size > 2)
    {
        int medianIndex = findMedianIndex(arr, start, size - 1);

        if (arr[medianIndex] == arr[size - 1])
        {
        }
        else
        {
            swap++;
            totalSwaps += abs(medianIndex - (size - 1));
        }

        swap1(&arr[medianIndex], &arr[size - 1]);

        if (abs(medianIndex - (size - 1)) > maxSwapDistance)
        {
            maxSwapDistance = abs(medianIndex - (size - 1));
        }

        x = arr[size - 1];
    }
    else
    {
        x = arr[size - 1];
    }

    int i = start - 1;
    int temp = 0;

    for (int j = start; j <= size - 2; j++)
    {
        if (arr[j] >= x)
        {

            i++;
            swap1(&arr[i], &arr[j]);
            swap++;

            totalSwaps += abs(i - j);

            if (abs(i - j) > maxSwapDistance)
            {
                maxSwapDistance = abs(i - j);
            }
        }
    }
    swap1(&arr[i + 1], &arr[size - 1]);

    swap++;
    totalSwaps += abs(i + 1 - (size - 1));

    if (abs(i + 1 - (size - 1)) > maxSwapDistance)
    {
        maxSwapDistance = abs(i + 1 - (size - 1));
    }
    return i + 1;
}

void StandartQuickSort(unsigned short *arr, int slice, int size, long &swap, double &avg_dist, double &max_dist, bool median_of_3)
{
    numberOfRecs++;

    double temp1 = 0;
    double temp2 = 0;

    if (size - slice > 1)
    {
        int p = StandartPartition(arr, slice, size, swap, avg_dist, max_dist, median_of_3);
        StandartQuickSort(arr, slice, p, swap, avg_dist, max_dist, median_of_3);
        StandartQuickSort(arr, p + 1, size, swap, avg_dist, max_dist, median_of_3);
    }
}

int HoarePartition(unsigned short *arr, int start, int size, long &swap, double &avg_dist, double &max_dist, bool median_of_3)
{
    unsigned short x;

    if (median_of_3 && size > 2)
    {
        int medianIndex = findMedianIndex(arr, start, size - 1);

        if (arr[medianIndex] == arr[start + (size - 1 - start) / 2])
        {
        }
        else
        {
            swap++;
            totalSwaps += abs((start + (size - 1 - start) / 2) - medianIndex);
        }
        swap1(&arr[start + (size - 1 - start) / 2], &arr[medianIndex]);

        if (abs((start + (size - 1 - start) / 2) - medianIndex) > maxSwapDistance)
        {
            maxSwapDistance = abs((start + (size - 1 - start) / 2) - medianIndex);
        }
        x = arr[start + (size - 1 - start) / 2];
    }
    else
    {
        x = arr[start + (size - 1 - start) / 2];
    }

    int i = start - 1;
    int j = size;

    while (true)
    {

        do
        {
            j--;
        } while (arr[j] < x);

        do
        {
            i++;
        } while (arr[i] > x);

        if (i < j)
        {
            swap1(&arr[i], &arr[j]);
            swap++;
            totalSwaps += abs(i - j);

            if (abs(i - j) > maxSwapDistance)
            {
                maxSwapDistance = abs(i - j);
            }
        }
        else
        {

            return j;
        }
    }
}

void HoareQuickSort(unsigned short *arr, int slice, int size, long &swap, double &avg_dist, double &max_dist, bool median_of_3)
{
    numberOfRecs++;

    if (size - slice > 1)
    {
        int p = HoarePartition(arr, slice, size, swap, avg_dist, max_dist, median_of_3);
        HoareQuickSort(arr, slice, p + 1, swap, avg_dist, max_dist, median_of_3);
        HoareQuickSort(arr, p + 1, size, swap, avg_dist, max_dist, median_of_3);
    }
}

int quickSort(unsigned short *arr, long &swap, double &avg_dist, double &max_dist, bool hoare, bool median_of_3, int size)
{

    if (!hoare)
    {
        StandartQuickSort(arr, 0, size, swap, avg_dist, max_dist, median_of_3);
    }

    else
    {
        HoareQuickSort(arr, 0, size, swap, avg_dist, max_dist, median_of_3);
    }

    avg_dist = totalSwaps / swap;
    max_dist = maxSwapDistance;

    return numberOfRecs;
}

int main(){



    return 0;
}
