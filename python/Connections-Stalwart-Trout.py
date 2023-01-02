class Connections():
    '''Needs to have a hash map for connections and looking up which city'''
    # City: weight
    __connections       = {}
    # Sorted order with the city as data
    __connectionsOrder  = []

    def __init__(self):
        '''Initialize and set connections to empty'''
        self.__connections       = {}
        self.__connectionsOrder  = []
    
    def insertConnection(self, newCity:str, weight:float):
        '''Given a float weight insert into connections and order'''
        # insert into self.__connections
        self.__connections[newCity] = weight
        # Use a binary search to insert into connectionsOrder, connections order should contain the cities. so to look up the weights check hash
        # Essentially a binary insertion sort for one element
        # linear search
        # if weight of city at end of connectionsOrder is greater than input weight, insert at end of list
        if len(self.__connectionsOrder) == 0 or self.__connections[self.__connectionsOrder[-1]] > weight:
            self.__connectionsOrder.append(newCity)
            

        for i in range(len(self.__connectionsOrder)):
            # if weight of city in connectionsOrder is less than new weight insert
            if self.__connections[self.__connectionsOrder[i]] < weight:
                self.__connectionsOrder.insert(i, newCity)
                return
            
            
        
        return

    def deleteConnection(self, delCity:str):
        '''Deletes a certain city's connection'''
        # Using a binary search loop through connections order similar to insert and delete instance of delCity
        self.__connectionsOrder.remove(delCity)
        # Key delete from connections
        del self.__connections[delCity]
        return
    
    def updateConnection(self, updateCity:str, newWeight:float):
        '''Updates weight of connection'''
        # Check valid input
        if self.__connections[updateCity]:
        # Call Delete Connection
            self.deleteConnection(self, updateCity)
        # Call Insert Conenction
            self.insertConnection(self, updateCity, newWeight)
        pass

    def getConnections(self, start:int, end:int):
        '''Given a start and end, return the connected cities starting at start and end'''
        # Check boundaries of start and end
        if start > end:
            return False
        # return list from start to end. Support negative indexing (-1 returns last index)
        return self.__connectionsOrder[start:end]


    def numConnections(self, threshold:float):
        '''Return number of connections over a given threshold'''
        nconn = 0
        # Use a binary search to find the index
        for city in self.__connectionsOrder:
            if self.__connections[city] > threshold:
                nconn += 1
            else:
                break
        # Use math to determine how many exist
        return nconn
    
    def is_connected(self, city:str, threshold:float):
        '''Checks if city is connected to the current city'''
        # Check if city is connected
        if city in self.__connections:
            return self.__connections[city] > threshold # TODO: Make sure greater than is correct
         
        return False

    def print_connections(self, start:int, end:int):
        '''Prints connections'''
        connections = self.getConnections(start, end)
        print('\tConnections:')
        for connection in connections:
            print(f'\t\tCity: {connection.city}: {self.__connections[connection]}')