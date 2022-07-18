package main.exceptions;

import main.graph.Node;

public class NodeNotExists extends Exception {
    public NodeNotExists(String label) {
        super("Node " + label + " not exists.");
    }

    public NodeNotExists() {
        super("Node not exists");
    }

    public NodeNotExists(Node<?> node) {
        super("Node " + node.toString() + " not exists");
    }
}
