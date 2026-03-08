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
    g_comp++;
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


/*
 *  BINARY SEARCH (INT)
 */

//binarySearch recursion on int
size_t bsr_int_r(const std::vector<int> &arr, int toInsert, size_t low, size_t high)
{
    if (low >= high)
        return low;

    size_t mid = low + (high - low) / 2;
    g_comp++;
    if (toInsert <= arr[mid])
        return bsr_int_r(arr, toInsert, low, mid);
    return bsr_int_r(arr, toInsert, mid + 1, high);
}

//return position in whole int vector
size_t bsr_int(const std::vector<int> &arr, int toInsert)
{
    return bsr_int_r(arr, toInsert, 0, arr.size());
}

//return position in prefix [0..high)
size_t bsr_int_prefix(const std::vector<int> &arr, int toInsert, size_t high)
{
    if (high > arr.size())
        high = arr.size();
    return bsr_int_r(arr, toInsert, 0, high);
}

/*
 *  BINARY SEARCH (DEQUE)
 */

size_t bsr_deque_r(const std::deque<int> &arr, int toInsert, size_t low, size_t high)
{
    if (low >= high)
        return low;

    size_t mid = low + (high - low) / 2;
    g_comp++;
    if (toInsert <= arr[mid])
        return bsr_deque_r(arr, toInsert, low, mid);
    return bsr_deque_r(arr, toInsert, mid + 1, high);
}

size_t bsr_deque(const std::deque<int> &arr, int toInsert)
{
    return bsr_deque_r(arr, toInsert, 0, arr.size());
}

size_t bsr_deque_prefix(const std::deque<int> &arr, int toInsert, size_t high)
{
    if (high > arr.size())
        high = arr.size();
    return bsr_deque_r(arr, toInsert, 0, high);
}

/*
 *INDEX TABLE (BORN FOR INSERT)
 */

//Maj index table to replicate S
void    rebuild_posById(const std::vector<PairNode> &S, std::vector<size_t> &posById){
    for (size_t i = 0; i < S.size(); ++i)
        posById[S[i].id] = i;
}

/*
 *  INDEX TABLE UPDATE (INT)
 */

void    int_posHighById(std::vector<size_t> &posHighById, size_t inserted_pos)
{
    size_t i = 0;
    while (i < posHighById.size())
    {
        if (posHighById[i] >= inserted_pos)
            posHighById[i] += 1;
        ++i;
    }
}

/*
 *PAIRING
 */
//comparaison+1
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
        g_comp++;
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
    // itere de 3 a 21845
    for (size_t j = 3; j < g_jacob_sz && count_y > 0; ++j)
    {
        long diff = g_jacob[j] - g_jacob[j - 1];
        if (diff <= 0) continue;
        // ^ impossible sauf si tu as fait une erreur

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
    //base case
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
    //Match PairNode.winner
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

        g_comp++;
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

    //maj pos by id (bornes) | maj indexTable posById (qui represent S qui change a chaque insert)
    std::vector<size_t> posById(total_ids, 0);
    rebuild_posById(S, posById);

    //insert loos of the smallest winner
    PairNode smallWinner = W[0];
    if(!havePend[smallWinner.id])
        error("missing pend");

    PairNode firstLooser = pendById[smallWinner.id];
    S.insert(S.begin(), firstLooser);
    rebuild_posById(S, posById);

    //number of element to insert (for jacobstal)
    size_t m        = W.size();
    size_t count_y  = 0;
    if (m > 1)
        count_y = m-1;
    if(has_orphan)
        count_y++;

    //insertion part (with jacobstal)

    //build the index list of insertion 
    std::vector<size_t> order =  jacob_order(count_y);

    for(size_t k = 0; k < order.size(); k++){

        size_t y_id = order[k];

        //if orphan (m+2 == convention !=  m+1 == normal elem)
        if(has_orphan && y_id == (m + 2)){
            size_t pos = bsr(S, orphan.winner);
            S.insert(S.begin() + pos, orphan);
            rebuild_posById(S, posById);
        }
        else{
            //y3 -> W[1], y4 -> W[2] 
            size_t w_i = y_id-2; //convertis l'index y_ en index w_
            if(w_i >= m)
                error("bad Y index");

            PairNode wnode = W[w_i]; //recup le winner associe au perdant de ce tour
            if(!havePend[wnode.id])
                error("missing pend");

            PairNode lnode = pendById[wnode.id]; //recup le perdant associe au winner trouve

            size_t bound    = posById[wnode.id]; // pos winner in S
            size_t pos      = bsr_prefix(S, lnode.winner, bound); // insert [0...bound]

            S.insert(S.begin() + pos, lnode);
            rebuild_posById(S, posById);
        }
    }

    return (S);
}

/*
 *  FINAL SORT (INT VECTOR)
 */

std::vector<int> fj_sort_ints_vector(const std::vector<int> &input_v)
{
    bool has_orphan = false;
    int  orphan = 0;

    // 1) make initial pairs (id stable)
    std::vector<PairNode> pairs_v;
    pairs_v.reserve(input_v.size() / 2);
    pairing(input_v, pairs_v, has_orphan, orphan);

    // 2) sort winners (PairNode) FJ engine
    std::vector<PairNode> sortedPairs = fj_sort_winners(pairs_v, pairs_v.size());

    // 3) build main chain S_int = all winners
    std::vector<int> S_int;
    S_int.reserve(has_orphan ? (pairs_v.size() * 2 + 1) : (pairs_v.size() * 2));

    std::vector<size_t> posHighById(pairs_v.size(), 0);

    size_t i = 0;
    while (i < sortedPairs.size())
    {
        S_int.push_back(sortedPairs[i].winner);
        posHighById[sortedPairs[i].id] = i;
        ++i;
    }

    // 3.0 insert loser of smallest winner
    if (sortedPairs.size() > 0)
    {
        S_int.insert(S_int.begin(), sortedPairs[0].looser);
        int_posHighById(posHighById, 0);
    }

    // remaining insertions: losers of sortedPairs[1..] + orphan
    size_t m = sortedPairs.size();
    size_t count_y = 0;
    if (m > 1)
        count_y = m - 1;
    if (has_orphan)
        count_y += 1;

    std::vector<size_t> order = jacob_order(count_y);

    size_t k = 0;
    while (k < order.size())
    {
        size_t y_id = order[k];

        // orphan is y_{m+2} 
        if (has_orphan && y_id == (m + 2))
        {
            size_t pos = bsr_int(S_int, orphan);
            S_int.insert(S_int.begin() + pos, orphan);
            int_posHighById(posHighById, pos);
        }
        else
        {
            // y3 -> sortedPairs[1], y4 -> sortedPairs[2], ...
            size_t w_i = y_id - 2;
            if (w_i >= m)
                error("bad Y index (int stage)");

            PairNode node = sortedPairs[w_i];

            size_t bound = posHighById[node.id];
            size_t pos = bsr_int_prefix(S_int, node.looser, bound);

            S_int.insert(S_int.begin() + pos, node.looser);
            int_posHighById(posHighById, pos);
        }
        ++k;
    }

    return S_int;
}

/*
 * SAME SHIT FOR DEQUE
 */
std::vector<int> fj_sort_ints_deque(const std::deque<int> &input_d)
{
    bool has_orphan = false;
    int  orphan = 0;

    // build pairs from deque (same PairNode vector)
    std::vector<PairNode> pairs_v;
    pairs_v.reserve(input_d.size() / 2);

    size_t i = 0;
    size_t id = 0;
    while (i < input_d.size())
    {
        int a = input_d[i++];
        if (i >= input_d.size()) { has_orphan = true; orphan = a; break; }
        int b = input_d[i++];

        PairNode p;
        p.id = id++;
        g_comp++;
        if (a <= b) { p.looser = a; p.winner = b; }
        else        { p.looser = b; p.winner = a; }
        pairs_v.push_back(p);
    }

    std::vector<PairNode> sortedPairs = fj_sort_winners(pairs_v, pairs_v.size());

    std::deque<int> S_d;

    std::vector<size_t> posHighById(pairs_v.size(), 0);

    size_t j = 0;
    while (j < sortedPairs.size())
    {
        S_d.push_back(sortedPairs[j].winner);
        posHighById[sortedPairs[j].id] = j;
        ++j;
    }

    if (!sortedPairs.empty())
    {
        S_d.insert(S_d.begin(), sortedPairs[0].looser);
        int_posHighById(posHighById, 0);
    }

    size_t m = sortedPairs.size();
    size_t count_y = 0;
    if (m > 1) count_y = m - 1;
    if (has_orphan) count_y += 1;

    std::vector<size_t> order = jacob_order(count_y);

    size_t k = 0;
    while (k < order.size())
    {
        size_t y_id = order[k];

        if (has_orphan && y_id == (m + 2))
        {
            size_t pos = bsr_deque(S_d, orphan);
            S_d.insert(S_d.begin() + pos, orphan);
            int_posHighById(posHighById, pos);
        }
        else
        {
            size_t w_i = y_id - 2;
            if (w_i >= m)
                error("bad Y index (int stage deque)");

            PairNode node = sortedPairs[w_i];

            size_t bound = posHighById[node.id];
            size_t pos = bsr_deque_prefix(S_d, node.looser, bound);

            S_d.insert(S_d.begin() + pos, node.looser);
            int_posHighById(posHighById, pos);
        }
        ++k;
    }

    // convert deque -> vector for display compatibility
    std::vector<int> out;
    out.reserve(S_d.size());
    for (std::deque<int>::const_iterator it = S_d.begin(); it != S_d.end(); ++it)
        out.push_back(*it);
    return out;
}
