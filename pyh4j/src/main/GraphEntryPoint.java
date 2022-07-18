package main;

import main.exceptions.NodeExists;
import main.graph.Graph;
import main.graph.Node;
import py4j.GatewayServer;

public class GraphEntryPoint {

    public Graph getGraph() {
        return new Graph();
    }

    public Node<?> newNode(Object label) {
        return new Node<>(label);
    }


    public static void main(String[] args) throws NodeExists {
        GatewayServer server = new GatewayServer(new GraphEntryPoint(), 25335);
        server.start();
    }
}
