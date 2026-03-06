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


/*
 *  UTILS
 */

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

/*
 *  PARSING
 */

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

/*
 *  BINARY SEARCH
 */

//binarySearch recurssion
size_t bsr_r(const std::vector<PairNode> &arr, int posToFind, size_t low, size_t high){
    if(low >= high)
        return low;

    size_t mid = low + (high - low) / 2;

    if(posToFind <= arr[mid].winner)
        return bsr_r(arr, posToFind, low, mid);
    return bsr_r(arr, posToFind, mid+1, high);
}

//binarySearch:: return [position] (orphan)
size_t  bsr(const std::vector<PairNode> &arr, int posToFind){
    return (bsr_r(arr, posToFind, 0, arr.size()));
}

//for opti insertion return [position] (looser/pend)
size_t bsr_prefix(const std::vector<PairNode> &arr, int posToFind, size_t high){
    if(high > arr.size())
        high = arr.size();
    return (bsr_r(arr, posToFind, 0, high));
}

//Maj index table to replicate S
void    rebuild_posById(const std::vector<PairNode> &S, std::vector<size_t> &posById){
    for (size_t i = 0; i < S.size(); ++i)
        posById[S[i].id] = i;
}

/*
 *PAIRING
 */

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
        winners_v.push_back(pairs_v[i]); 
}

/*
 * JACOBSTHAL
 */

const long g_jacob[] = {0,1,1,3,5,11,21,43,85,171,341,683,1365,2731,5461,10923,21845};
const size_t g_jacob_sz = sizeof(g_jacob)/sizeof(g_jacob[0]);

std::vector<size_t> jacob_order(size_t count_y)
{
    std::vector<size_t> order;
    order.reserve(count_y);

    size_t y = 3;
    for (size_t j = 3; j < g_jacob_sz && count_y > 0; ++j)
    {
        long diff = g_jacob[j] - g_jacob[j - 1];
        if (diff <= 0) continue;

        size_t group = static_cast<size_t>(diff);
        size_t take = (group < count_y) ? group : count_y;

        for (size_t k = 0; k < take; ++k)
            order.push_back(y + (take - 1 - k));

        y += take;
        count_y -= take;
    }
    if (count_y > 0)
        error("Internal error: Jacob table too short");
    return order;
}

/*
 *  FJ ENGINE
 */

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


    //unwinding winners sort!
    std::vector<PairNode> S = W;

    //pos by id (bornes)
    std::vector<size_t> posById(total_ids, 0);
    rebuild_posById(S, posById);

    //insert loos of the smallest winner
    PairNode smallWinner = W[0];
    if(!havePend[smallWinner.id])
        error("missing pend");

    PairNode firstLooser = pendById[smallWinner.id];
    S.insert(S.begin(), firstLooser);
    rebuild_posById(S, posById);

    //insert looser of W[1...] + orphan
    size_t m        = W.size();
    size_t count_y  = 0;
    if (m > 1)
        count_y = m-1;
    if(has_orphan)
        count_y++;

    std::vector<size_t> order =  jacob_order(count_y);

    for(size_t k = 0; k < order.size(); k++){

        size_t y_id = order[k];

        if(has_orphan && y_id == (m + 2)){
            size_t pos = bsr(S, orphan.winner);
            S.insert(S.begin() + pos, orphan);
            rebuild_posById(S, posById);
        }
        else{
            //y3 -> W[1], y4 -> W[2]
            size_t w_i = y_id-2;
            if(w_i >= m)
                error("bad Y index");

            PairNode wnode = W[w_i];
            if(!havePend[wnode.id])
                error("missing pend");

            PairNode lnode = pendById[wnode.id];

            size_t bound    = posById[wnode.id]; // pos winner in S
            size_t pos      = bsr_prefix(S, lnode.winner, bound); // insert [0...bound]

            S.insert(S.begin() + pos, lnode);
            rebuild_posById(S, posById);
        }
    }

    return (S);
}
