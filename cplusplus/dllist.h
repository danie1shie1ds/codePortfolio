/**********************************
 * Name: Daniel Shields
 * Email: dshield2@nd.edu
 * File Name: dllist.h
 * Date Created: 3/17/2022
 * File Contents: This file contains the dllist and dllist_node structs
 **********************************/

#ifndef DLLIST_H
#define DLLIST_H

#include <iostream>
#include <cstdlib>

#define COUT std::cout 
#define CIN std::cin
#define ENDL std::endl
#define SIZE_T long unsigned int

struct dllist_node{

		/********************************
		 * Put the public members and the constructor here for the 
		 * Doubly Linked List Node as identified in the project description
		 *********************************/
		int data;
		int time_stamp;
		dllist_node* prev_node;
		dllist_node* next_node;

	// Default Constructor
	dllist_node( ) : data( ), prev_node(NULL), next_node(NULL) {}
	
	// Overloaded Constructor - When we know the data 
	dllist_node( const int& data_in, const int& timestamp_in ) : data(data_in), time_stamp(timestamp_in), prev_node(NULL), next_node(NULL) {}

	
};


struct dllist{

    private:
    
        void destructor( dllist_node* curr_ptr ){
	
        	// Dr. Morrison's Golden Rule of Pointers 
        	if( curr_ptr == NULL )
        		return;
        	
        
        	// Recursively call destructor on the next node  
        	destructor( curr_ptr->next_node );
        		
        	// Delete the current pointer 
        	delete curr_ptr;
        	
        }

    public:

		/********************************
		 * Put the public members, the constructor, and the destructor here 
		 * for the Doubly Linked List as identified in the project description
		 *********************************/
		SIZE_T capacity, list_size;
		dllist_node* head_node;
		dllist_node* tail_node;

		// Constructor
		dllist(const SIZE_T& capacity_in, const SIZE_T& list_size_in) : capacity(capacity_in), list_size(list_size_in), head_node(NULL), tail_node(NULL) {}

		// Destructor
		// Public Destructor Call
		~dllist(){
			
			// Do nothing if the list is empty
			if( this->head_node == NULL && this->tail_node == NULL ){
				return;
			}
			
			// Call the private, recursive destructor
			destructor( this->head_node );
		}
    	
    	
		/********************************
		 * Here, you will modify the push_front method to return a 
		 * pointer to the address of the inserted node 
		 *********************************/
    	dllist_node* push_front( const int& the_value, const int& the_time ){
        	
        	// Create a dll_node pointer called insert_node
        	dllist_node* insert_node = new dllist_node( the_value, the_time );
        	
        	// Dr. Morrison's Golden Rule of Pointers 
        	if( this->head_node == NULL ){
        		
        		// Set the head node equal to insert_node 
        		this->head_node = insert_node;
        		this->tail_node = insert_node;
        		
        		// Increment the size
        		this->list_size++;
        		
				return insert_node;
        	}
        	
        	// Otherwise, we perform the pointer arithmetic
        	dllist_node* reference = this->head_node;
        	
        	// Set the head_node to the new node 
        	this->head_node = insert_node;
        	
        	// Set the new head_node's next to the reference 
        	this->head_node->next_node = reference;
        	reference->prev_node = this->head_node;
        	
    		// Increment the size
    		this->list_size++;
    		
    		
			return insert_node;
        	
        }
        
    // Step 15 - Pop Back 
    void pop_back( ){
    	
    	// Check if the list is not empty
    	if( this->head_node == NULL && this->tail_node == NULL )
    		return;
    	
    	if( this->head_node == this->tail_node ){
    		
    		delete this->head_node;
    		
    		// Set the pointers value to NULL
    		this->head_node = NULL;
    		this->tail_node = NULL;
    		
    		// Decrement the size
    		this->list_size--;
    		
    		// Return the node to delete
    		return;
    	}
    	
    	// Otherwise, move the node and free
    	// Set a reference pointer to head_node
    	dllist_node* reference = this->tail_node;
    	
    	// Set the head_node to head_node's next_node;
    	this->tail_node = reference->prev_node;
    	this->tail_node->next_node = NULL;
    
    	
    	// Free the reference 
    	delete reference;
    	
		// Decrement the size
		this->list_size--;
    	
    }


    void promote_node_to_front( dllist_node* the_node, int num_accesses ){
        
		/**********************************
		 * Here, you will write the code to promote 
		 * the node at the address passed to this method
		 * to the front of the Doubly Linked List 
		 * and you will update the internal time stamp to num_accesses
		 ***********************************/
		if(this->head_node == NULL || this->tail_node == NULL || the_node == NULL ){
			return;
		}

		the_node->time_stamp = num_accesses;

		if(the_node == this->head_node) return;

		if(the_node == this->tail_node){
			this->tail_node = the_node->prev_node;
			this->tail_node->next_node = NULL;
		}
		else{
			the_node->prev_node->next_node = the_node->next_node;
			the_node->next_node->prev_node = the_node->prev_node;
		}

		the_node->prev_node = NULL;
		the_node->next_node = this->head_node;
		this->head_node->prev_node = the_node;
		this->head_node = the_node;

        
    }
    
    bool at_capacity(){
        
        return this->capacity == this->list_size;
    }
    
    void print_list(){
        
        COUT << "Cache contents: " << ENDL;
        COUT << "Current size: " << this->list_size << ENDL;
        
        dllist_node* print_node = this->head_node;
        
        while( print_node != NULL ){
        
            COUT << "Address = " << print_node << ": ";
            COUT << "Time Stamp = " << print_node->time_stamp << ", ";
            COUT << "Data =  " << print_node->data << ENDL;
            
            print_node = print_node->next_node;
        }
    }
};

#endif