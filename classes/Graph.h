#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include <limits>
#include "NetworkPoint.h"

#define INF std::numeric_limits<double>::max()

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}
/**
 * @brief Graph adapted to Max-Flow problems as well as implementation of various auxiliary functions to help solve the
 * proposed problems.
 */
class Graph;

/**
 * @brief Node in the graph. With its Demand (for Cities) and other parameters.
 */
class Node;

/**
 * @brief Similar to edge, but it has a maximum capacity and flow.
 */
class Pipe;


class Graph {
    private:
        std::unordered_map<std::string, Node*> nodes;
        void dfsVisit(Node *v, std::vector<NetworkPoint> &res) const;
    public:
        // DON'T KNOW IF THIS IS REALLY NECESSARY
        // Graph(std::unordered_map<std::string, Node*> nodes);

        Node* findNode(const std::string &code) const;
        Pipe* findPipe(const std::string source, const std::string dest) const;

        int getNumNode() const { return nodes.size(); };
        std::vector<Node*> getNodeSet() const;

        bool addNode(const std::string &s,NetworkPoint *type);
        bool removeNode(const NetworkPoint &type);

        bool addPipe(const std::string &source, const std::string &dest, double capacity);
        bool removePipe(const std::string &source, const std::string &dest);
        bool addBidirectionalPipe(const std::string &source, const std::string &dest, double capacity); // maybe a bool in the addPipe parameters?

        std::vector<NetworkPoint> dfs() const;
        std::vector<NetworkPoint> dfs(const std::string &source) const;
        std::vector<NetworkPoint> bfs(const std::string &source) const;
};

class Node{
    private:
        NetworkPoint* info;
        std::vector<Pipe*> pipes;
        bool visited;
        bool processing;
        int inDegree;
        int num;
        int low;
        Pipe *path = nullptr; // why path and not node?

        std::vector<Pipe*> incoming; // don't we already have the pipes vector?

        bool removePipe(Node *dest);
    public:
        Node(NetworkPoint *_info) : info(_info) {};

        NetworkPoint* getInfo() const { return this->info; };
        void setInfo(NetworkPoint *info) { this->info = info; };

        bool isVisited() const { return this->visited; };
        void setVisited(bool v) { this->visited = v; };

        bool isProcessing() const { return this->processing; };
        void setProcessing(bool p) { this->processing = p; };

        int getInDegree() const { return this->inDegree; };
        void setInDegree(int inDegree) { this->inDegree = inDegree; };

        void setLow(int low) { this->low = low; };
        int getLow() const { return this->low; };
        
        int getNum() const { return this->num; };
        void setNum(int num) { this->num = num; };

        /**
         * @brief Returns the next pipe in path
         *
         * At each iteration of the Edmonds-Karp algorithm, a path is created and, it needs to be stored. Then, a possible
         * solution is to have, for each node, the next node in a given path. In the next iteration, if the node is in
         * the path, this variable will be overriden.\n\n
         *
         * @return the next pipe in that path
         */
        Pipe *getPath() const {return this->path;};
        void setPath(Pipe *path) {this->path = path;};

        std::vector<Pipe*> getIncoming() const {return this->incoming;};

        std::vector<Pipe*> getPipes() const { return this->pipes; };
        void setPipes(std::vector<Pipe*> pipes) { this->pipes = pipes; };

        bool deletePipe(Pipe *pipe); // already defined up there?
        Pipe* addPipe(Node *dest, double capacity); // double with the graph one?

        friend class Graph;
};

class Pipe {
    private:
        Node *dest;
        double capacity;   
        Node *orig;    
        Pipe *reverse = nullptr; 
        double flow;
    public:
        Pipe(Node *_orig, Node *_dest, double _c) : orig(_orig), dest(_dest), capacity(_c) {};

        Node* getDest() const { return this->dest; };
        void setDest(Node *dest) { this->dest = dest; };
        
        Node* getOrig() const { return this->orig; };

        Pipe* getReverse() const { return this->reverse; };
        void setReverse(Pipe *reverse) { this->reverse = reverse; };

        double getFlow() const { return this->flow; };
        void setFlow(double flow) { this->flow = flow; };

        void setCapacity(double capacity) { this->capacity = capacity; };
        double getCapacity() const { return this->capacity; };
};

#endif