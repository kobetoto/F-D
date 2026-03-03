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

/*
1. Pairing : make pair & compare each pair → (loser, winner) loser < winner

2. Rec_Desc : trier recursivement(step 1.) la liste des winners (ce qui reduit le problèm)
                => Base case : 1winner

3. Unwinding / insertion :
    3.0 insertion loser associé au plus petit winner au début (placement certain 0 comparaisons)
    3.1 insertion autres losers (+ l’orphelin) dans un ordre -> déterminé par un schéma basé sur JacobsthalList
    3.2 chaque loser (y_i) est inséré par binarySearch dans S[0 .. x_i) (borne exclue), 
        et l’orphelin dans toute `S`.
*/

//input X = { 42 , 3 , 1 , 2 , 4 }

int main(int ac, char **av){

    try{
        /* PARSING */
        if(ac <= 2)
            error("Please provide an list of integer (mini 2 int)");
        
        std::vector<int> s_main;
        s_main.reserve(ac - 1);

        input_to_vector(ac, av, s_main);

        /* 1.PAIRING */
        bool    has_orphan = false;
        int     orphan = 0;
        std::vector<std::pair< int, int> > s_pair;
        s_pair.reserve((s_main.size() / 2));
        
        //pairing(s_main, s_pair, has_orphan, orphan);
        
        /* 2~3. REC */
        lets_cook(s_main, s_pair, has_orphan, orphan);

        /* DEBUG */
        //print_arg(av);
        print_v(s_main);
        print_vp(s_pair);
    }
	catch (std::runtime_error& e){
		std::cerr << "Error: " << e.what() << '\n';
		return (1);
	}
    return (0);
}


/*
    -> comment inserer les loosers associe au plus petit winner lors de l'unwinding?
    -> comment gerer les associations??
    -> comment ne pas perdre les loosers
    -> Jacobstal en dur????

*/
