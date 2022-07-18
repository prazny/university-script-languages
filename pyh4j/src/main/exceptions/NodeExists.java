package main.exceptions;

import main.graph.Node;

public class NodeExists extends Exception {
    public NodeExists(String label) {
        super("Node " + label + " already exists.");
    }

    public NodeExists() {
        super("Node already exists");
    }

    public NodeExists(Node<?> node) {
        super("Node " + node.toString() + " not exists");
    }
}
