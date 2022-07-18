import functools
import random
from random import randint



class MultipleAccumulate:
    data_list = list
    accumulate_functions = tuple
    dict = {}

    def __init__(self, data_list, *accumulate_functions):
        self.dict = None
        self.data_list = data_list
        self.accumulate_functions = accumulate_functions
        # self.dict = {func.__name__: 0 for func in accumulate_functions}

    @staticmethod
    def make_name( name):
        if name == "<lambda>":
            return "lambda-" + str(random.randint(1, 999999))
        else:
            return name

    def __filter_functions(self):
        return [func for func in self.accumulate_functions if callable(func)]

    def get_data(self):
        self.dict = {self.make_name(func.__name__): functools.reduce(func, self.data_list)
                     for func in self.__filter_functions()}
        return self.dict


# for key, value in ma.get_data().items():
#    print(key, ' : ', value)
