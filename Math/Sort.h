#pragma once
#include <vector>

namespace Sort {
    static int partition(std::vector<int>& tab, int p, int q) //p7.1.0
    {
        int x = tab[p];
        int i = p;

        for (int j = p + 1; j < q; j++)
        {
            if (tab[j] <= x)
            {
                i = i + 1;
                std::swap(tab[i], tab[j]);
            }

        }

        std::swap(tab[i], tab[p]);
        return i;
    }

    static void quickSort(std::vector<int>& tab, int p, int q)//p7.1.0
    {
        int r;
        if (p < q)
        {
            r = partition(tab, p, q);
            quickSort(tab, p, r);
            quickSort(tab, r + 1, q);
        }
    }

    // float
    static int partitionf(std::vector<float>& tab, int p, int q)// p7.1.0
    {
        float x = tab[p];
        int i = p;

        for (int j = p + 1; j < q; j++)
        {
            if (tab[j] <= x)
            {
                i = i + 1;
                std::swap(tab[i], tab[j]);
            }

        }

        std::swap(tab[i], tab[p]);
        return i;
    }

    static void quickSortf(std::vector<float>& tab, int p, int q)// p7.1.0
    {
        int r;
        if (p < q)
        {
            r = partitionf(tab, p, q);
            quickSortf(tab, p, r);
            quickSortf(tab, r + 1, q);
        }
    }

    static void reverse(std::vector<int>& tab) {// p7.1.0
        for (int i = 0; i < tab.size() / 2; i++) {
            std::swap(tab[i], tab[tab.size() - i - 1]);
        }
    }

    static void reversef(std::vector<float>& tab) {// p7.1.0
        for (int i = 0; i < tab.size() / 2; i++) {
            std::swap(tab[i], tab[tab.size() - i - 1]);
        }
    }
}