from pickle import FALSE
from re import S
from inc.Hash import Hash
from inc.Connections import Connections
import pandas as pd
import matplotlib.pyplot as plt



class Node():
    def __init__(self, city:str, state:str):
        hash             = Hash(city, state)
        self.city        = hash.city
        self.state       = hash.state
        self.hash        = hash.get_hash()
        self.connections = Connections()
        self.stats       = {}
        self.lionized    = set(['Violent Crime', 'Metro Population','Temperature Range', 'Average Annual Salary', 'Median Monthly Rent', 'Median Home Price'])
        self.normalized   = set(['Avg Annual Rainfall','Avg Commute Time - continuous','Avg Low Temps','Property Crime','Median Age','Percent Single','Total Students','Total Teachers','Unemployment Rate'])
    
    def add_connection(self, newCity, weight:float):
        '''Adds a connection to the specified city'''
        self.connections.insertConnection(newCity, weight)



    def calculate_connection(self, otherCity):
        '''Calculates the connection strength between this city and given city'''
        # TODO: Overwrite with new actual algorithm

        # If City in hash return the calculated score
        if self.connections.is_connected(otherCity, 0):
            print('Test')
            return self.connections
        # Convert each node's dictionary object to a Pandas Series object, dropping values that contain Strings
        self_ser = pd.Series(self.stats).drop(labels=['City','State','Coastal'])
        other_ser = pd.Series(otherCity.stats).drop(labels=['City','State','Coastal'])

        index_ = ['Avg Annual Rainfall','Avg Commute Time - continuous','Avg High Temps','Avg Low Temps','Median Home Price','Median Monthly Rent','Property Crime','Violent crime','Average Annual Salary','Median Age','Metro Population','Percent Single','Temperature Range','Total Students','Total Teachers','Unemployment Rate']
        
        # Create the Intersection of each Series object so that each key has a value for all categories
        count = 0
        for ind in index_:
            if self_ser[ind] == '' or other_ser[ind] == '':
                count += 1
                self_ser = self_ser.drop(ind)
                other_ser = other_ser.drop(ind)

        self_ser = self_ser.astype(float)
        other_ser = other_ser.astype(float)

        # Calculate the Pearson Score of Similarity between the values in each object
        pearson_score = self_ser.corr(other_ser, method='pearson')

        if count >= 3 and count <= 6:
            pearson_score *= 0.92
        elif count > 6:
            pearson_score *= 0.85

        score = 0
        # Similarity Score Algorithm
        for key in (unionKey for unionKey in self.stats if unionKey in otherCity.stats):
            if self.stats[key] != '' and otherCity.stats[key] != '':
                if key == 'City' or key == 'State':
                    continue
                elif key == 'Avg High Temps':
                    temp_diff = abs(self.stats[key] - otherCity.stats[key])
                    # Add a Higher Weight if the max temps are within 2 degrees of each other 
                    if temp_diff <= 3.5:
                        score += 1.3 * (temp_diff / self.stats[key])
                elif key in self.lionized:
                    # Add a Higher Weight to the Important Categories in the Set lionized
                    score += 1.25 * abs(self.stats[key] - otherCity.stats[key]) / self.stats[key]
                elif self.stats[key] == otherCity.stats[key]:
                    # If there are any values that are identical, add to score
                    score *= 1.185 
                elif key in self.normalized:
                    score += 1.115 * abs(self.stats[key] - otherCity.stats[key]) / self.stats[key]
                # If the scores do not match in the Coastal Category, decrease score by 20 percent
                elif key == 'Coastal':
                    if self.stats[key] != otherCity.stats[key]:
                        score *= 0.2 
        
        # Average Score from algorithm with Pearson Score of Similarity
        final_sim = (pearson_score + (1/abs(score))) / 2
        
        return final_sim
    
    def compare_node(self, otherCity):
        '''Compares two city nodes chosen by the user'''
        # Create Series objects for the two cities to be compared
        self_ser = pd.Series(self.stats)
        other_ser = pd.Series(otherCity.stats)
        # Print side by side comparison of each city's statistics
        print(self_ser.compare(other_ser))

    # def plot_nodes(self, otherCity):
    #     '''Compares two city nodes chosen by the user'''
    #     # Create Series objects for the two cities to be compared
    #     self_ser = pd.Series(self.stats)
    #     other_ser = pd.Series(otherCity.stats)

    #     self_ser = self_ser.drop(labels=['City','State'])
    #     other_ser = other_ser.drop(labels=['City','State'])

    #     self_ser = self_ser.astype(float)
    #     other_ser = other_ser.astype(float)

    #     print(self_ser.index)

    #     print(self_ser.corr(other_ser))
        
    #     # for row in range(len(self_ser)):
    #     #     if self_ser[row] != '' and other_ser[row] != '':
    #     #         continue
    #     #     elif self_ser['Coastal']
    #     # city_df = pd.concat([self_ser,other_ser], axis=1)
    #     # city_df = city_df.drop(labels=['City','State'])
    #     # city_df = city_df.astype(float)
 

    def insert_stat(self, statName:str, statNum:float):
        '''Adds statistics to the dictionary'''
        self.stats[statName] = statNum

    def print_node(self, numConnection:int=5):
        '''Prints node and numConnections'''
        print(f'{self.city}, {self.state}: ')
        
        # Print the stats
        for statName, stat in self.stats.items():
            print(f'\t{statName}: {stat}')
            
        self.connections.print_connections(0, numConnection)