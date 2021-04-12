#include <iostream>

class Range
{
public:
    int L;
    int H;
    int Difference;

public:
    Range(int l, int h)
            : L(l), H(h)
    {
        Difference = h - l;
    }
};

template<typename TValue>
class Array
{
private:
    TValue *Elements;
    int Length;

public:
    Range Range1;
    Range Range2;
    Range Range3;
    Range Range4;

public:
    Array(Range range1, Range range2, Range range3, Range range4)
            : Range1(range1), Range2(range2), Range3(range3), Range4(range4)
    {
        int length = (range1.Difference + 1) *
                     (range2.Difference + 1) *
                     (range3.Difference + 1) *
                     (range4.Difference + 1);

        Elements = new TValue[length];

        Length = length;
    }

    ~Array()
    {
        delete[] Elements;
    }

public:
    TValue GetRowElement(int i1, int i2, int i3, int i4)
    {
        int index = GetRowIndex(i1, i2, i3, i4);

        auto result = Elements[index];
        return result;
    }

    void SetRowElement(TValue value, int i1, int i2, int i3, int i4)
    {
        int index = GetRowIndex(i1, i2, i3, i4);

        Elements[index] = value;
    }

    TValue GetColumnElement(int i1, int i2, int i3, int i4)
    {
        int index = GetColumnIndex(i1, i2, i3, i4);

        auto result = Elements[index];
        return result;
    }

    void SetColumnElement(TValue value, int i1, int i2, int i3, int i4)
    {
        int index = GetColumnIndex(i1, i2, i3, i4);

        Elements[index] = value;
    }

private:
    int GetRowIndex(int i1, int i2, int i3, int i4)
    {
        int D2 = Range1.Difference + 1;
        int D3 = (Range2.Difference + 1) * D2;
        int D4 = (Range3.Difference + 1) * D3;

        int index = CountIndex(i1, i2, i3, i4, D2, D3, D4);
        return index;
    }

    int GetColumnIndex(int i1, int i2, int i3, int i4)
    {
        int D2 = Range4.Difference + 1;
        int D3 = (Range3.Difference + 1) * D2;
        int D4 = (Range2.Difference + 1) * D3;

        int index = CountIndex(i1, i2, i3, i4, D2, D3, D4);
        return index;
    }

    int CountIndex(int i1, int i2, int i3, int i4, int d2, int d3, int d4)
    {
        return i1 - Range1.L +
               (i2 - Range2.L) * d2 +
               (i3 - Range3.L) * d3 +
               (i4 - Range4.L) * d4;
    }
};

template<typename TValue>
void Fill(Array<TValue> *array)
{
    Range range1 = array->Range1;
    Range range2 = array->Range2;
    Range range3 = array->Range3;
    Range range4 = array->Range4;

    int value = 0;

    //std::cout << "Filling the array: " << std::endl;

    for (int i1 = range1.L; i1 <= range1.H; ++i1)
    {
        for (int i2 = range2.L; i2 <= range2.H; ++i2)
        {
            for (int i3 = range3.L; i3 <= range3.H; ++i3)
            {
                for (int i4 = range4.L; i4 <= range4.H; ++i4)
                {
                    array->SetRowElement(value,
                                         i1, i2, i3, i4);

                    //std::cout << value << " ";

                    value++;
                }
                //std::cout << std::endl;
            }
        }
    }
}

template<typename TValue>
void DisplayRowElements(Array<TValue> *array)
{
    Range range1 = array->Range1;
    Range range2 = array->Range2;
    Range range3 = array->Range3;
    Range range4 = array->Range4;

    std::cout << std::endl;
    std::cout << "Displaying the array: " << std::endl;

    for (int i1 = range1.L; i1 <= range1.H; ++i1)
    {
        for (int i2 = range2.L; i2 <= range2.H; ++i2)
        {
            for (int i3 = range3.L; i3 <= range3.H; ++i3)
            {
                for (int i4 = range4.L; i4 <= range4.H; ++i4)
                {
                    auto element = array->GetRowElement(i1, i2, i3, i4);

                    std::cout << element << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

template<typename TValue>
void DisplayColumnElements(Array<TValue> *array)
{
    Range range1 = array->Range1;
    Range range2 = array->Range2;
    Range range3 = array->Range3;
    Range range4 = array->Range4;

    std::cout << std::endl;
    std::cout << "Displaying the array: " << std::endl;

    for (int i1 = range1.L; i1 <= range1.H; ++i1)
    {
        for (int i2 = range2.L; i2 <= range2.H; ++i2)
        {
            for (int i3 = range3.L; i3 <= range3.H; ++i3)
            {
                for (int i4 = range4.L; i4 <= range4.H; ++i4)
                {
                    auto element = array->GetColumnElement(i1, i2, i3, i4);

                    std::cout << element << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

int main()
{
    auto range1 = Range(-1, 1);
    auto range2 = Range(2, 3);
    auto range3 = Range(4, 6);
    auto range4 = Range(7, 8);

    auto array = Array<int>(range1,
                            range2,
                            range3,
                            range4);

    Fill(&array);
    DisplayRowElements(&array);
    DisplayColumnElements(&array);
}
