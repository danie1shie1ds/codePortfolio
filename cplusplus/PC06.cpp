/**********************************
 * Name: Daniel Shields
 * Email: dshield2@nd.edu
 * File Name: PC06.cpp
 * Date Created: 3/17/2022
 * File Contents: This file contains the main function for PC06
 **********************************/

#include "../include/lru_cache.h"

int main( ){
	
	/*************************************
	 * Here, you will call the constructor for the Doubly Linked List 
	 * and create the unordered_map with the int, dll_node* key value pair
	 ************************************/

	SIZE_T cap = initialize_cache();
	SIZE_T size = 0;
	dllist the_list(cap, size);
	UNOR_MAP< int, dllist_node* > the_map;
	
	char continue_read = 'y';
	
	int num_accesses = 0;
	
	while( continue_read == 'y' ){
	    
	    // Increment the number of accesses
	    ++num_accesses;
	    
	    char user_choice = get_user_choice( );
	   
		switch( user_choice ) {
				
			case 'p':
				
				/*************************************
				 * Here, you will get the input data value from the user 
				 * and then call the put function
				 ************************************/				
				int put_data;
				COUT << "Data Value to insert" << ENDL;
				CIN >> put_data;
				put_value(the_list, the_map, put_data, num_accesses);
				break;
				
			case 'g':
			
				/*************************************
				 * Here, you will get the input data value from the user 
				 * and then call the get function
				 ************************************/	
				int get_data;
				CIN >> get_data;
				get_value(the_list, the_map, get_data, num_accesses);
				break;
				
			default:
				COUT << "Value must be between 1 and 3" << ENDL;
			
		}
		
		/*************************************
		 * Here, you will call print_list on your doubly linked list 
		 ************************************/			
	    the_list.print_list();
	    COUT << "Do you wish to continue? (y/n): ";
	    CIN >> continue_read;
	    
	}
	
	/*************************************
	 * Note: Since you will be calling the constructor for dllist 
	 * without making it a pointer, the destructor will 
	 * automatically be called, so you do not need to call it!
	 ************************************/
	
	return EXIT_SUCCESS;
}