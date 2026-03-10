/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:41:37 by thodavid          #+#    #+#             */
/*   Updated: 2026/02/26 16:20:55 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//input X = { 42 , 3 , 1 , 2 , 4 }

unsigned long long g_comp = 0;

#include <cmath>
#include <cstdlib>
#include <iostream>

int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

int main(int ac, char **av)
{
    try
    {
        if (ac <= 2)
            throw std::runtime_error("Error");
    
        // VECT input
        std::vector<int> input_v;
        input_v.reserve(ac - 1);
        input_to_vector(ac, av, input_v);


        //LOG
        std::cout << "Before: ";
        for (size_t i = 0; i < input_v.size(); ++i)
            std::cout << input_v[i] << ' ';
        std::cout << "\n";


        // VECTOR timing 
        g_comp = 0;
        std::clock_t t0 = std::clock();
        std::vector<int> sorted_v = fj_sort_ints_vector(input_v);
        std::clock_t t1 = std::clock();
        unsigned long long cmp_v = g_comp;


        // DEQUE input
        std::deque<int> input_d;
        for (size_t i = 0; i < input_v.size(); ++i)
            input_d.push_back(input_v[i]);

        // DEQUE timing
        g_comp = 0;
        std::clock_t d0 = std::clock();
        std::vector<int> sorted_d = fj_sort_ints_deque(input_d);
        std::clock_t d1 = std::clock();
        unsigned long long cmp_d = g_comp;

        std::cout << "After:  ";
        for (size_t i = 0; i < sorted_v.size(); ++i)
            std::cout << sorted_v[i] << ' ';
        std::cout << "\n";

        double us_v = (double)(t1 - t0) * 1000000.0 / (double)CLOCKS_PER_SEC;
        double us_d = (double)(d1 - d0) * 1000000.0 / (double)CLOCKS_PER_SEC;

        std::cout << "Time to process a range of " << input_v.size()
            << " elements with std::vector : " << us_v << " us\n";
        std::cout << "Time to process a range of " << input_v.size()
            << " elements with std::deque : " << us_d << " us\n";


        const unsigned long long MAXCOMP = F(sorted_d.size());
        std::cout << "Comparisons vector: " << cmp_v << "\n";
        std::cout << "Comparisons deque:  " << cmp_d << "\n";
        if (cmp_v > MAXCOMP || cmp_d > MAXCOMP)
            throw std::runtime_error("Exceed !");
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

