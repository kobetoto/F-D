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

void error(const std::string &str){ throw(std::runtime_error(str)); }

bool bsr_r(std::vector<int> &arr, int to_find, int low, int high){
  
  if(low > high)
    return (false);
  
  int mid = low + (high - low) /2;

  if(arr[mid] == to_find)
    return (true);

  if(to_find < arr[mid])
    return (bsr_r(arr, to_find, 0, mid-1));
  
  return (bsr_r(arr, to_find, mid+1, high));
}

bool bsr(std::vector<int> &arr, int to_find){
  return (bsr_r(arr, to_find, 0, static_cast<int>(arr.size())));
}

void       print_vp( std::vector<std::pair< int, int> > vect_p){

    std::cout << "===VECTOR_PAIR===\n";
    for(std::vector<std::pair< int, int> >::iterator it = vect_p.begin(); it != vect_p.end(); ++it)
        std::cout << "it->first:: " << it->first << "   ||   it->second:: " << it->second << '\n';
    std::cout << "=================\n";
}


void        print_v(std::vector<int> v){
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

void        print_arg(char **ac){
    int i = 1;
    while (ac[i]){
        std::cout << "ac[" << i << "]:: " << ac[i] << '\n';
        i++;
    }
        return;
}

int    check_input(const char *str){
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

void pairing(const std::vector<int> &s_main,
             std::vector< std::pair< int, int> > &s_pair,
             bool &has_orphan,
             int &orphan)
{
    s_pair.clear();
    has_orphan = false;

    std::vector<int>::const_iterator it = s_main.begin();
    while (it != s_main.end())
    {
        int a = *it;
        ++it;

        if (it == s_main.end()) {
            has_orphan = true;
            orphan = a;
            break;
        }

        int b = *it;
        ++it;
        if (a <= b) 
      		s_pair.push_back(std::make_pair(a, b));
        else
			s_pair.push_back(std::make_pair(b, a));
    }
}


void update_seq(std::vector<int> &s, std::vector<std::pair<int,int> > &s_p){
  s.clear();
  for(size_t i = 0; i < s_p.size(); i++)
    s.push_back(s_p[i].second);
}

void lets_cook(std::vector<int> &s_main,
             std::vector< std::pair< int, int> > &s_pair,
             bool &has_orphan,
             int &orphan)
{
    /*base case*/
    if(s_main.size() == 1)
        return;

    print_v(s_main);
    print_vp(s_pair);

    /* 1.PAIRING */
    has_orphan  = false;
    orphan      = 0;
    pairing(s_main, s_pair, has_orphan, orphan);
    update_seq(s_main, s_pair);   
    
    /* 2. + 3. ~REC~ */
    lets_cook(s_main, s_pair, has_orphan, orphan);
}
