/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:05:03 by thodavid          #+#    #+#             */
/*   Updated: 2026/02/24 14:10:27 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void error(const std::string &str){ throw(std::runtime_error(str)); }

void    check_input(const char *str){
    if (str[0] == '\0')
        error("Wrong input (empty)");
    int i = 0;
    while(str[i])
    {
        if (!isdigit(str[i]))
            error("Wrong input (positive digit only)");
        i++;
    }
}

void    input_to_vector(int ac, char **argv, std::vector<int> &v){
    if(!argv)
        return;
    for(int i = 1; i < ac ; i++){
        check_input(argv[i]);
        int n = atoi(argv[i]);
        if (n < 0)
            error("Wrong input (getconf INT_MAX)");
        v.push_back(n);
    }
}

void    pairing(std::vector<int> &vect, std::vector<std::pair< int, int > > &vect_p){

    for(std::vector< int >::iterator it = vect.begin(); it != vect.end(); it++){
        std::pair< int, int > p;
        p.first = *it;
        it++;
        p.second = *it;
        vect_p.push_back(p);
    }
}
