/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodavid <thodavid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 10:05:03 by thodavid          #+#    #+#             */
/*   Updated: 2026/02/26 16:21:12 by thodavid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    error(const std::string &str){ throw(std::runtime_error(str)); }

void    print_v(std::vector<int> &v){
    std::cout << "=================\n";
    std::cout << "======VECTOR=====\n";
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++){
        std::cout << "it:: " << *it << '\n';
        // it++;
        // std::cout << "next:: " << *it << '\n';
        // it--;
    } 
    std::cout << "=================\n";
    return;
}

int     check_input(const char *str){
	if (!str || *str == '\0')
		error("Wrong input");

	char *end = 0;
	long l 		= std::strtol(str, &end, 10);
	if(*end != '\0')
		error("Wrong input");
	if(l <= 0 || l > INT_MAX)
		error("Wrong input");
	return (static_cast<int>(l));
}

void    input_to_vector(int ac, char **argv, std::vector<int> &s){
	if(!argv)
		return;
	for(int i = 1; i < ac ; i++){
		int n = check_input(argv[i]);
		s.push_back(n);
	}
}


void    pairing(const std::vector<int> &input_v,
                        std::vector<PairNode> &pairs_v,
                        bool &has_orphan,
                        int &orphan)
{
    pairs_v.clear();
    has_orphan = false;
    orphan = 0;

    size_t i = 0;
    size_t id = 0;
    while (i < input_v.size())
    {
        int a = input_v[i++];
        if (i >= input_v.size()){
            has_orphan = true; 
            orphan = a;
            break;
        }
        int b = input_v[i++];

        PairNode p;
        p.id = id++;
        if (a <= b) {
            p.looser = a; 
            p.winner = b;
        }
        else{ 
            p.looser = b;
            p.winner = a;
        }
        pairs_v.push_back(p);
    }
}

void    build_winners_v(const std::vector<PairNode> &pairs_v,
                          std::vector<PairNode> &winners_v)
{
    winners_v.clear();
    winners_v.reserve(pairs_v.size());
    for (size_t i = 0; i < pairs_v.size(); ++i)
        winners_v.push_back(pairs_v[i]); //
}


std::vector<PairNode>   fj_sort_winners(const std::vector<PairNode> &pairs_v, size_t total_ids)
{
    if (pairs_v.size() <= 1)
        return pairs_v;

    std::vector<PairNode> winners;
    winners.reserve(pairs_v.size() / 2);

    std::vector<PairNode>   pendById(total_ids);
    std::vector<char>       havePend(total_ids, 0); //checkSecurity

    //orphan on this level?
    bool has_orphan = false;
    PairNode orphan;

    size_t i = 0;
    while (i < pairs_v.size())
    {
        PairNode a = pairs_v[i++];
        if (i >= pairs_v.size())
        {
            has_orphan = true;
            orphan = a;
            break;
        }
        PairNode b = pairs_v[i++];
        
        PairNode win;
        PairNode los;
        // match sur high
        if (a.winner <= b.winner){
            win = b;
            los = a;
        }
        else{
           win = a;
           los = b;
        }         
        winners.push_back(win);
        pendById[win.id] = los;
        havePend[win.id] = 1;
    }

    //recurssion !
    std::vector<PairNode> W = fj_sort_winners(winners, total_ids);


    //unwinding !
    std::vector<PairNode> S = W;
    PairNode smallWinner = W[0];

    if(!havePend[smallWinner.id])
        error("missing pend");

    PairNode firstLooser = pendById[smallWinner.id];
    S.insert(S.begin(), firstLooser);

    // pour l’instant on ne réinsère pas les perdants, on retourne juste W
    // (orphans ignoré ici, car c’est une version debug)
    (void)has_orphan;
    (void)orphan;

    return (S);
}
