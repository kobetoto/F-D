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

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <exception>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>


void    error(const std::string &str);
void    check_input(const char *str);
void    input_to_vector(int ac, char **argv, std::vector< int > &v);
void    pairing(std::vector< int > &vect, std::vector<std::pair< int, int> > &vect_p);

#endif //PMERGEME_HPP
