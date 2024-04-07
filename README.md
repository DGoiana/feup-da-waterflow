# Water Flow Program

This project has its main focus on determining the Max-Flow of graphs that represent locations and its flow of water. Using **Reservoirs** as the sources, **Pumping Stations** as the intermediary nodes and the **Cities** as the sinks. 

## Installation

Install the zip given in the delivery or clone this respository. Then you can run the program via the Clion Client or via terminal

```bash
cmake . -B output/ && make && cd classes/ && ../feup_da_proj1 && cd ..
```

## Balancing Graph Algorithm

## Modified Edmonds-Karp

The main objective of this "modified" Edmonds-Karp is to determine how the graph was affected (as a whole) when all the nodes are removed, one by one. Our strategy takes advantage of the fact that all the nodes are removed and what matter is the difference in the whole graph. For that, instead of removing each node at a time, we add those nodes in reverse order, then run a BFS for the affected nodes and add the flow. Therefore, we can see how much of the flow was lost or gained. After all the values are determined, we just print out in the "right" order.

```
graph: Graph with all pipes with Set as false and flow as 0
Define arrayMaxFlow

modifiedEdmondsKarp(graph,source,sink):
    Create newGraph as a copy of graph
    Define changedFlow  // The affected cities and how much
    currentMaxFlow = EdmondsKarp(newGraph,source,sink,affectedNodes)
    for affected in affectedNodes:
        if(newCity.currentFlow != graph.findNode(City).currentFlow && !graph.findNode(City).isSet()):
            changedFlow.add({City,graph.findNode(City).currentFlow - newCity.currentFlow})
        graph.findNode(City).Set = true
    oldMaxFlow = EdmondsKarp(graph,source,sink)
    return (currentMaxFlow + oldMaxFlow), changedFlow

for reservoir in graph:
    Create subSuperSink
    affectedNodes = BFS(reservoir,graph)
    for affectedNode in affectedNodes:
        connect affectedNode to subSuperSink
    currentMaxFlow,changedFlow = modifiedEdmondsKarp(graph,reservoir,subSuperSink,affectedNodes) // Adds flow to the old Graph
    arrayMaxFlow.add({reservoir,currentMaxFlow,changedFlow})

arrayMaxFlow.reverse()
```

In terms of complexity, at the worst case both of the algorithms have the number of nodes to be removed O(V) times the complexity of each Edmonds-Karp O(VE²). But the presented solution, works the more isolated subgraphs faster and works better for  graphs that have a bigger number of connected components. Final Time Complexity would 
be O(V²E²)

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.
