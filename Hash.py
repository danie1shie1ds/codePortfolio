class Hash():
    __hash = ""
    def __init__(self, city:str, state:str):
        # Calculate Hash
        self.city  = city.lower().strip()
        self.state = state.lower().strip()
        self.__hash = self.city + self.state

    def get_hash(self):
        # Return the Hash
        return self.__hash