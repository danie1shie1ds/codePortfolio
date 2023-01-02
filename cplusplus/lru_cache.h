/****************************
 * File Name: lru_cache.h 
 * Author: Matthew Morrison
 * Email: matt.morrison@nd.edu
 *
 * This file is provided to the students for the
 * function declarations for Programming Challenge 6
 *****************************/

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "dllist.h"

#include <iostream>
#include <unordered_map>

#define SIZE_T long unsigned int
#define UNOR_MAP std::unordered_map

char get_user_choice( );

SIZE_T initialize_cache( );

void get_value( dllist& cache_list, UNOR_MAP< int, dllist_node* >& cache_map, 
    const int insert_data, int num_accesses );


void put_value( dllist& cache_list, UNOR_MAP< int, dllist_node* >& cache_map, 
    int insert_data, int num_accesses );

#endif