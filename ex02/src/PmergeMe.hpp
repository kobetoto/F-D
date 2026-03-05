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

struct PairNode {
  int winner;
  int looser;
  size_t id;
};

int     check_input(const char *str);
void    error(const std::string &str);
void    input_to_vector(int ac, char **argv, std::vector< int > &v);
void    print_v(std::vector<int> &v);
void    pairing(const std::vector<int> &input_v,
                        std::vector<PairNode> &pairs_v,
                        bool &has_orphan,
                        int &orphan);
void    build_winners_v(const std::vector<PairNode> &pairs_v,
                          std::vector<PairNode> &winners_v);
std::vector<PairNode>   fj_sort_winners(const std::vector<PairNode> &pairs_v, size_t total_ids);

