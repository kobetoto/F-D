/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:41:37 by thodavid          #+#    #+#             */
/*   Updated: 2026/02/24 14:10:58 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void        print_v(std::vector<int> v){
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << "it:: " << *it << '\n';
        // it++;
        // std::cout << "next:: " << *it << '\n';
        // it--;
    } 
        return;
}

void        print_arg(char **ac){
    int i = 1;
    while (ac[i]){
        std::cout << "ac[" << i << "]:: " << ac[i] << '\n';
        i++;
    }
        return;
}

void       print_vp( std::vector<std::pair< int, int> > vect_p){
    for(std::vector<std::pair< int, int> >::iterator it = vect_p.begin(); it != vect_p.end(); ++it)
        std::cout << "it->first:: " << it->first << "   ||   it->second:: " << it->second << '\n';
}

//input X = { 2 ; 6 ; 0 ; 7 ; 42 ; 12 ; 24 ; 10 ; 5 ; 11 } /* 9elements */

int main(int ac, char **av){

    try{
        /* PARSING */
        if(ac <= 2)
            error("Please provide an list of integer (mini 2 int)");
        std::vector<int> vec;
        vec.reserve(ac - 1);
        input_to_vector(ac, av, vec);

        /* PAIRING */
        std::vector<std::pair< int, int> > vect_p;
        vect_p.reserve((vec.size() / 2));
        pairing(vec, vect_p);
        print_arg(av);
        print_v(vec);
        print_vp(vect_p);
    }
	catch (std::runtime_error& e){
		std::cerr << "Error: " << e.what() << '\n';
		return (1);
	}
    return (0);
}
