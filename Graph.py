from numpy import insert
from inc.Node import Node
from inc.Hash import Hash
import pandas as pd




class Graph():
    __graph = {}

    def __init__(self):
        self.populate_graph()
        while(self.get_selection()):
            continue


    
    def populate_graph(self):
        '''Populates graph with all relevant statistics and Nodes'''
        data = pd.read_csv('Data/Best_US_CIties_Modified.csv')
        data = data.drop(columns=['Link','US News Rank','PathOrder','City and State','Coastal String'])
        data = data.fillna('')
        
        # For each city seperate City and State
        for row in data.index:
            city        = data['City'][row]
            state       = data['State'][row]
            # Generate a hash for each city
            newCityhash = Hash(city, state)
            # Insert the node using the hash
            self.insert_node(city, state, newCityhash)
            
            # Insert all stats into the city's node
            for col in data.columns:
                self.__graph[newCityhash.get_hash()].insert_stat(col, data[col][row])
        self.insert_all_connections()

    def insert_all_connections(self):
        '''This method calculates all of the connections and adds them to the graph'''
        # Loop through all of the dictionaries
        for city in self.__graph:
            # Iterate through all other cities
            for otherCity in self.__graph:
                # If the cities are not the same
                if city != otherCity:
                    # Calculate the weight
                    weight = self.__graph[city].calculate_connection(self.__graph[otherCity])

                    # Add the connection
                    self.__graph[city].add_connection(self.__graph[otherCity], weight)
        return

    def insert_node(self, city, state, newCityhash):
        ''' Inserts node to Graph'''
        self.__graph[newCityhash.get_hash()] = Node(city, state)
    
    def print_graph(self):
        '''Prints the entire graph'''
        for key in self.__graph:
            # Call each nodes print function
            self.__graph[key].print_node()
        return

    
    def get_selection(self):
        
        '''Get User Selections'''
        # Print the Menu Options
        print('Menu Options:')
        print('\t1: Print Entire Graph')
        print('\t2  Print City')
        print('\t3  Print City and a Specified Number of Connections')
        print('\t4  Compare Two Cities Side-By-Side')

        print('\t0: Quit')

        # Get the input argument
        option = input('Select Option: ')
        selection = int(option[0])

        # Parse the options
        if selection == 1:
            self.print_graph()
        elif selection == 2:

            choice = input('Enter a City, State (Abbrv): ').split(', ')
            city = choice[0]
            state = choice[-1]
            # Compute hash for user input city, state
            cityHash = Hash(city, state)
                
            # Print City if exists in graph
            if cityHash.get_hash() in self.__graph:
                self.__graph[cityHash.get_hash()].print_node()
        elif selection == 3:
            # Get city, state abbreviation, and number of connections from user
            choice = input('Enter a City, State (Abbrv): ').split(', ')
            city = choice[0]
            state = choice[-1]

            num_connections = int(input('How many connections would you like to see?: '))

            # Compute hash
            cityHash = Hash(city, state)

            # Print connections
            self.__graph[cityHash.get_hash()].connections.print_connections(0, num_connections)

        elif selection == 4:
            # Hash
            choice1 = input('Enter a City, State (Abbrv): ').split(', ')
            city1 = choice1[0]
            state1 = choice1[-1]
            choice2 = input('Enter another City, State (abbrv): ').split(', ')
            city2 = choice2[0] 
            state2 = choice2[-1]
            city1Hash = Hash(city1, state1)
            city2Hash = Hash(city2, state2)
            # Print comparison
            self.__graph[city1Hash.get_hash()].compare_node(self.__graph[city2Hash.get_hash()])
    
        else:
            return False
        # Keep Looping this if true
        return True