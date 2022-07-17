#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "pool_tst.h"
#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

int main()
{
    size_t maxx;
    // Declaring A Simple BST
    struct BSTNode* CVALS1;
    double Max_time;
    double Min_time;
    double DT1;
    std::clock_t c_start1;
    std::clock_t c_end1;

    maxx = 1e5;
    std::cout << "Number Of Pool Data: " << maxx << std ::endl;

    DT1 = 0;
    Max_time = 0;
    Min_time = 1000000000;
    for (size_t i = 0; i < 100; i++)
    {
        c_start1 = std::clock();

        // Create BST Node As Soon As We Require It (We Do It For A Million Times In Our Code)
        for (size_t i = 0; i < maxx; i++)
            CVALS1 = (struct BSTNode*) calloc(1, sizeof(struct BSTNode));

        c_end1 = std::clock();

        if ((static_cast <double> (c_end1) - static_cast <double> (c_start1)) / static_cast <double> (CLOCKS_PER_SEC)
                > Max_time)
            Max_time = (static_cast <double> (c_end1) - static_cast <double> (c_start1)) / static_cast <double> (CLOCKS_PER_SEC);

        if ((static_cast <double> (c_end1) - static_cast <double> (c_start1)) / static_cast <double> (CLOCKS_PER_SEC)
                < Min_time)
            Min_time = (static_cast <double> (c_end1) - static_cast <double> (c_start1)) / static_cast <double> (CLOCKS_PER_SEC);

        DT1 += (static_cast <double> (c_end1) - static_cast <double> (c_start1)) / static_cast <double> (CLOCKS_PER_SEC);
//        std::cout <<  i << " -> "<< std::fixed << std::showpoint << std::setprecision(8)
//                   << (static_cast <double> (c_end1) - static_cast <double> (c_start1))/ static_cast <double> (CLOCKS_PER_SEC) << std::endl;
    }

    std::cout << std::fixed << std::showpoint << std::setprecision(8) << "Min Elapsed time in Sec: " << Min_time
              <<  "  AVE Elapsed time in Sec: " << DT1/100 << "  Max Elapsed time in Sec: " << Max_time<< std::endl;


    struct BSTNode* CVALS2;
    std::clock_t c_start2;
    std::clock_t c_end2;
    double DT2 = 0;
    Max_time = 0;
    Min_time = 1000000000;

    for (size_t i = 0; i < 100; i++)
    {
        c_start2 = std::clock();

        // Create A Million Elements (Pool Of BST) For Future Use
        CVALS2 = (struct BSTNode*) calloc(maxx, sizeof(struct BSTNode));

        c_end2 = std::clock();

        if ((static_cast <double> (c_end2) - static_cast <double> (c_start2)) / static_cast <double> (CLOCKS_PER_SEC)
                > Max_time)
            Max_time = (static_cast <double> (c_end2) - static_cast <double> (c_start2)) / static_cast <double> (CLOCKS_PER_SEC);

        if ((static_cast <double> (c_end2) - static_cast <double> (c_start2)) / static_cast <double> (CLOCKS_PER_SEC)
                < Min_time)
            Min_time = (static_cast <double> (c_end2) - static_cast <double> (c_start2)) / static_cast <double> (CLOCKS_PER_SEC);

        DT2 += (static_cast <double> (c_end2) - static_cast <double> (c_start2)) / static_cast <double> (CLOCKS_PER_SEC);

        //        std::cout << i << " -> " << std::fixed << std::showpoint << std::setprecision(8)
        //                  << (static_cast <double> (c_end2) - static_cast <double> (c_start2)) / static_cast <double> (CLOCKS_PER_SEC) << std::endl;

    }

    std::cout << std::fixed << std::showpoint << std::setprecision(8) << "Min Elapsed time in Sec: " << Min_time
              <<  "  AVE Elapsed time in Sec: " << DT2/100 << "  Max Elapsed time in Sec: " << Max_time<< std::endl;

    std::cout << "NP to P Time Ratio: " << DT1 / DT2 << std::endl;


}

