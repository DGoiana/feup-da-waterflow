#ifndef GRAPH_H_
#define GRAPH_H_

#include <unordered_map>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
#include "NetworkPoint.h"

class Graph;
class Node;
class Pipe;

class Graph {
    private:
        std::unordered_map<std::string, Node*> nodes;
        void dfsVisit(Node *v, std::vector<NetworkPoint> &res) const;
    public:
        // DON'T KNOW IF THIS IS REALLY NECESSARY
        // Graph(std::unordered_map<std::string, Node*> nodes);

        Node* findNode(const std::string &code) const;

        int getNumNode() const { return nodes.size(); };
        std::vector<Node*> getNodeSet() const;

        bool addNode(const std::string &s,const NetworkPoint &type);
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
        NetworkPoint info;
        std::vector<Pipe*> pipes;
        bool visited;
        bool processing;
        int inDegree;
        int num;
        int low;
        Pipe *path = nullptr; // why path and not node?

        std::vector<Pipe*> incoming; // don't we already have the pipes vector?

        Pipe* addPipe(Node *dest, double capacity); // double with the graph one?
        bool removePipe(Node *dest);
    public:
        Node(NetworkPoint _info) : info(_info) {};

        NetworkPoint getInfo() const { return this->info; };
        void setInfo(NetworkPoint info) { this->info = info; }; 

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

        std::vector<Pipe*> getPipes() const { return this->pipes; };
        void setPipes(std::vector<Pipe*> pipes) { this->pipes = pipes; };

        bool deletePipe(Pipe *pipe); // already defined up there?

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