/**********************************
 * Name: Daniel Shields
 * Email: dshield2@nd.edu
 * File Name: lru_cache.cpp
 * Date Created: 3/17/2022
 * File Contents: This file contains the functions for PC06
 **********************************/

#include "../include/lru_cache.h"

char get_user_choice( ){
	
	COUT << "Enter your choice: " << ENDL;
	COUT << "p: Put value onto cache" << ENDL;
	COUT << "g: Get value from cache" << ENDL;
	COUT << "Enter your choice: ";
	
	char user_choice;
	
	CIN >> user_choice;
	
	return user_choice;
	
}


SIZE_T initialize_cache( ){
	
	COUT << "State the size of the cache: ";
	
	int capacity;
	
	CIN >> capacity;
	
	return capacity;
}


void put_value( dllist& cache_list, UNOR_MAP< int, dllist_node* >& cache_map, 
    int insert_data, int num_accesses ){

	/*********************************
	 * You will follow the steps for putting an element into a DLList and unordered map
	 * from the Programming Challenge 06 description
	 *********************************/
	if(!(cache_map.count(insert_data))){
		COUT << insert_data << "is now in the cache!" << ENDL;
		if(cache_list.at_capacity()){
			cache_list.pop_back();
			cache_map.erase(insert_data);
		}
		dllist_node* insert_node = cache_list.push_front(insert_data, num_accesses);
		cache_map.insert({insert_data, insert_node});
	}
	else{
	COUT << insert_data << "is already in the cache. Cache hit!" << ENDL;
	get_value(cache_list, cache_map, insert_data, num_accesses);
	}


}


void get_value( dllist& cache_list, UNOR_MAP< int, dllist_node* >& cache_map, 
    const int insert_data, int num_accesses ){
		
	/*********************************
	 * You will follow the steps for putting an element into a DLList and unordered map
	 * from the Programming Challenge 06 description
	 *********************************/
	if(cache_map[insert_data] != 0){
		COUT << "Cache hit!" << ENDL;
		dllist_node* node;
		node = cache_map.at(insert_data);
		cache_list.promote_node_to_front(node, num_accesses);
		COUT << node->data << ENDL;

	}
	else{
		COUT << "Not in the cache! Cache Miss." << ENDL;
	}
}
