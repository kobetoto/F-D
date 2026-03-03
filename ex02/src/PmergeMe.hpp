/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:05:10 by thodavid          #+#    #+#             */
/*   Updated: 2026/02/24 13:17:08 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <exception>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <climits>


int     check_input(const char *str);
void    error(const std::string &str);
void    input_to_vector(int ac, char **argv, std::vector< int > &v);
void    pairing(const std::vector< int > &v_main, 
                std::vector< std::pair< int, int> > &v_pair,
                bool &has_orphan,
                int &orphan);
void update_seq(std::vector<int> &s, std::vector<std::pair<int,int> > &s_p);
void lets_cook(std::vector<int> &s_main,
             std::vector< std::pair< int, int> > &s_pair,
             bool &has_orphan,
             int &orphan);
void       print_vp( std::vector<std::pair< int, int> > vect_p);
void        print_v(std::vector<int> v);
void        print_arg(char **ac);
