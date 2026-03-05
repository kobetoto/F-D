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

int main(int ac, char **av){

    try{
        /* PARSING */
        if(ac <= 2)
            error("Please provide an list of integer (mini 2 int)");
        
        std::vector<int> input_v;
        input_v.reserve(ac - 1);
        input_to_vector(ac, av, input_v);
        
        /* odd input */
        bool has_orphan = 0;
        int  orphan = 0;

        /* PAIRING */
        std::vector<PairNode> pairs_v;
        pairs_v.reserve(input_v.size() / 2);
        pairing(input_v, pairs_v, has_orphan, orphan);
        
        
        std::vector<PairNode> winners;
        build_winners_v(pairs_v, winners);

        std::vector<PairNode> w = fj_sort_winners(winners, pairs_v.size());

        /* DEBUG */
        for(size_t i = 0; i < w.size(); ++i)
            std::cout << "Winner h:: " << w[i].winner << "  " << w[i].looser << " | id:: " << w[i].id << '\n';
    }
	catch (std::runtime_error& e){
		std::cerr << "Error: " << e.what() << '\n';
		return (1);
	}
    return (0);
}
