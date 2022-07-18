import subprocess
from urllib import request
from subprocess import Popen, PIPE
import os
import signal

from py4j.java_gateway import JavaGateway, GatewayParameters


class Graph:
    def __init__(self):
        try:
            self.entry_point = JavaGateway(gateway_parameters=GatewayParameters(port=25335)).entry_point
            self.graph = self.entry_point.getGraph()
        except:
            # you must compile src as list5.jar
            self.gateway = Popen(['java', '-jar', 'list5.jar'], stdin=PIPE, stdout=PIPE)
            self.entry_point = JavaGateway(gateway_parameters=GatewayParameters(port=25335)).entry_point
        self.graph = self.entry_point.getGraph()

    def __del__(self):
        JavaGateway().close()
        JavaGateway().shutdown()

        self.gateway.kill()

    def add_node(self, label):
        return self.entry_point.newNode(label)
        # return self.graph.addNode(label)

    def remove_node(self, label):
        self.graph.removeNode(label)

    def put_edge(self, src_label, dst_label, weight):
        self.graph.putEdge(src_label, dst_label, weight)

    def remove_edge(self, src_label, dst_label):
        self.graph.removeNode(src_label, dst_label)

    def get_edge_weight(self, src, dst):
        return self.graph.getEdgeWeight(src, dst)

    def get_shortest_path_to_node(self, src_label, dst_label):
        return self.graph.getShortestPathToNode(src_label, dst_label)

    def get_connected_nodes(self, src_label):
        return list(self.graph.getConnectedNodes(src_label))

    def help(self):
        JavaGateway(gateway_parameters=GatewayParameters(port=25335)).help(self.entry_point)


if __name__=="__main__":
    """
       10
    A----------->B
    |\    \   /3 |
    | \2   \ /   |
    |  \   / \   | 1 
    |5   E    \  |
    v       20 v v
    C           D
    """

    g1 = Graph()
    a = g1.add_node("A")
    b = g1.add_node("B")
    c = g1.add_node("C")
    d = g1.add_node("D")
    e = g1.add_node("E")
    f = g1.add_node("F")

    g1.put_edge(a, b, 10.0)
    g1.put_edge(a, e, 2.0)
    g1.put_edge(a, d, 20.0)
    g1.put_edge(a, c, 5.0)
    g1.put_edge(b, d, 1.0)
    g1.put_edge(e, b, 3.0)

    print(a)
    print(g1.get_edge_weight(e, b))
    print(g1.get_shortest_path_to_node(a, d))

    print(type(g1.get_connected_nodes(a)))
    for node in g1.get_connected_nodes(a):
        print(node)
