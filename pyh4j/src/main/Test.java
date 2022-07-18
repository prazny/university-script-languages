package main;

import main.exceptions.NodeExists;
import main.graph.Graph;
import main.graph.Node;

import java.util.Arrays;

public class Test {
    public static void main(String[] args) throws NodeExists {
        Graph g1 = new Graph();

        Node<String> a = new Node<>("A");
        Node<String> b = new Node<>("B");
        Node<String> c = new Node<>("C");
        Node<String> d = new Node<>("D");
        Node<String> e = new Node<>("E");

        g1.putEdge(a, b, 10.0);
        g1.putEdge(a, e, 2.0);
        g1.putEdge(a, d, 20.0);
        g1.putEdge(a, c, 5.0);
        g1.putEdge(b, d, 1.0);
        g1.putEdge(e, b, 3.0);

        System.out.println(g1.getShortestPathToNode(a, d));
        System.out.println(Arrays.toString(g1.getConnectedNodes(a)));

        for(Node<?> node: g1) {
            System.out.print(node.toString() + " -> ");
            System.out.println(node.connectedNodes);

        }
    }
}
