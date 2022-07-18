package main.graph.algorithms;

import main.graph.Graph;
import main.graph.Node;

import java.util.*;

// BFS
public class ConnectedNodes {
    public static Object[] init(Graph graph, Node<?> src) {
        Map<Node<?>, Boolean> visited = new HashMap<>();
        LinkedList<Node<?>> queue = new LinkedList<>();

        for (Node<?> node : graph)
            visited.put(node, false);

        visited.put(src, true);
        queue.add(src);

        while (!queue.isEmpty()) {
            Node<?> current = queue.poll();

            for (Map.Entry<Node<?>, Double> edge : current.connectedNodes.entrySet()) {
                if (!visited.get(edge.getKey())) {
                    visited.put(edge.getKey(), true);
                    queue.add(edge.getKey());
                }
            }
        }

        List<Node<?>> connected = new ArrayList<>();
        for(Map.Entry<Node<?>, Boolean> edge : visited.entrySet()) {
            if(edge.getValue()) {
                connected.add(edge.getKey());
            }
        }

        return connected.toArray();
    }
}
