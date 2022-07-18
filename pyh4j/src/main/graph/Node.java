package main.graph;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

public class Node<T> {
    private final T value;

    public Node(T value) {
        this.value = value;
    }

    public T getValue() {
        return value;
    }

    public Map<Node<?>, Double> connectedNodes = new HashMap<>();

    public void addConnectedNode(Node<?> node, double weight) {
        connectedNodes.put(node, weight);
    }

    public Map<Node<?>, Double> getConnectedNodes() {
        return connectedNodes;
    }

    public void removeConnectedNode(Node<?> node) {
        connectedNodes.remove(node);
    }

    @Override
    public String toString() {
        return "Node(" + value + ")";
    }
}
