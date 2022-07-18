package main.graph;

import main.exceptions.NodeExists;
import main.exceptions.NodeNotExists;
import main.graph.algorithms.ConnectedNodes;
import main.graph.algorithms.FastestPath;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Graph implements Iterable<Node<?>> {
    private final List<Node<?>> nodes = new ArrayList<>();

    public void addNode(Node<?> node) throws NodeExists {
        if (nodes.contains(node))
            throw new NodeExists(node);

        nodes.add(node);
    }

    public void removeNode(Node<?> node) throws NodeNotExists {
        if (!nodes.contains(node))
            throw new NodeNotExists(node);

        nodes.remove(node);
    }


    public void putEdge(Node<?> src, Node<?> dst, double weight) throws NodeExists {
        if (!nodes.contains(src))
            this.addNode(src);

        if (!src.equals(dst) && !nodes.contains(dst))
            this.addNode(dst);

        src.addConnectedNode(dst, weight);
    }

    public double getEdgeWeight(Node<?> src, Node<?> dst) {
        if (nodes.contains(src)) {
            return src.connectedNodes.getOrDefault(dst, Double.MAX_VALUE);
        } else return Double.MAX_VALUE;
    }

    public boolean removeEdge(Node<?> src, Node<?> dst) throws NodeNotExists {
        if (!nodes.contains(src))
            throw new NodeNotExists(src);

        if (!src.equals(dst) && !nodes.contains(dst))
            throw new NodeNotExists(dst);

        src.removeConnectedNode(dst);
        return true;
    }

    // Dijkstra Algorithm
    public double getShortestPathToNode(Node<?> src, Node<?> dst) {
        return FastestPath.init(this, src, dst);
    }

    // BFS
    public Object[] getConnectedNodes(Node<?> src) {
        return ConnectedNodes.init(this, src);

    }

    @NotNull
    @Override
    public Iterator<Node<?>> iterator() {
        return nodes.iterator();
    }
}

