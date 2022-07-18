from multiple_accumulate import MultipleAccumulate
from view_files import ViewerCreator
from inspect import getsource


def add(a, b):
    return a + b


def sub(a, b):
    return a - b


def mul(a, b):
    return a * b


instances = [
    ViewerCreator().create_viewer('path-to-file'),
    MultipleAccumulate([1, 2, 3, 4, 5], add, lambda a, b: a - b),
    MultipleAccumulate([5, 7, 2], mul, sub),
]


for ins in instances:
    print(ins.get_data())
