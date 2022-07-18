package main.graph.algorithms;

import main.graph.Graph;
import main.graph.Node;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

//Dijkstra algorithm
public class FastestPath {
    public static double init(Graph graph, Node<?> src, Node<?> dst) {
        ArrayList<Node<?>> settledNodes = new ArrayList<>();
        ArrayList<Node<?>> unsettledNodes = new ArrayList<>();
        Map<Node<?>, Double> distances = new HashMap<>();
        for (Node<?> node : graph)
            distances.put(node, Double.MAX_VALUE);

        distances.put(src, 0.0);
        unsettledNodes.add(src);

        while (!unsettledNodes.isEmpty()) {
            Node<?> currentNode = findSmallestDistance(unsettledNodes, distances);
            unsettledNodes.remove(currentNode);

            if (currentNode == null)
                System.out.println(unsettledNodes.size());
            else {
                for (Map.Entry<Node<?>, Double> edge : currentNode.connectedNodes.entrySet()) {
                    Node<?> connectedNode = edge.getKey();

                    if (!settledNodes.contains(connectedNode)) {
                        calculateMinimumDistance(connectedNode, currentNode, distances);
                        unsettledNodes.add(connectedNode);
                    }
                }
            }

            settledNodes.add(currentNode);
        }

        return distances.get(dst);
    }

    private static void calculateMinimumDistance(Node<?> connectedNode, Node<?> sourceNode, Map<Node<?>, Double> distances) {
        double sourceDistance = distances.get(sourceNode);
        if (sourceDistance + sourceNode.connectedNodes.get(connectedNode) < distances.get(connectedNode)) {
            distances.put(connectedNode, sourceDistance + sourceNode.connectedNodes.get(connectedNode));
        }
    }

    public static Node<?> findSmallestDistance(ArrayList<Node<?>> nodes, Map<Node<?>, Double> distances) {
        double minDistance = Double.MAX_VALUE;
        Node<?> minNode = nodes.get(0);

        for (Node<?> node : nodes) {
            if (distances.get(node) < minDistance) {
                minDistance = distances.get(node);
                minNode = node;
            }
        }

        return minNode;
    }
}
