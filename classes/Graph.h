#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

template <class T> class Graph;
template <class T> class Node;
template <class T> class Pipe;

template <class T>
class Graph {
   private:
    std::unordered_map<std::string, Node<T>*> nodes;
    void dfsVisit(Node<T> *v, std::vector<T> & res) const;
public:
    // DON'T KNOW IF THIS IS REALLY NECESSARY
    //Graph(std::unordered_map<std::string, Node<T>*> nodes);
    Node<T>* findNode(const T &in) const;
    int getNumNode() const;
    std::vector<Node<T> *> getNodeSet() const;

    bool addNode(const std::string &s,const T &type);
    bool removeNode(const T &type);

    bool addPipe(const T &source,const T &dest, double capacity);
    bool removePipe(const T &source, const T &dest);
    bool addBidirectionalPipe(const T &source, const T &dest, double capacity);

    std::vector<T> dfs() const;
    std::vector<T> dfs(const T & source) const;
    std::vector<T> bfs(const T &source) const;
};


template <class T>
class Node{

private:
    T type;
    std::vector<Pipe<T> *> pipes;
    bool visited{};
    bool processing{};
    int inDegree{};
    int num{};
    int low{};
    Pipe<T> *path = nullptr;

    std::vector<Pipe<T> *> incoming;

    Pipe<T> * addPipe(Node<T> *dest, double capacity);
    bool removePipe(Node<T> *dest);

public:
    Node(T type);

    T getType() const;
    void setType(T type) const;

    bool isVisited() const;
    void setVisited(bool v);

    bool isProcessing() const;
    void setProcessing(bool p);

    int getInDegree() const;
    void setInDegree(int inDegree);

    void setLow(int low);
    void setNum(int num);

    int getNum() const;
    int getLow() const;

    std::vector<Pipe<T> *> getPipes() const;
    void setPipes(std::vector<Pipe<T>*> pipes);
    friend class Graph<T>;

    bool deletePipe(Pipe<T> *pipe);
};

template <class T>
class Pipe {
private:
    Node<T>* dest;      // destination vertex
    double capacity;         // pipe capacity
    Node<T> *orig;      // origin vertex
    Pipe<T> *reverse = nullptr; // reverse Pipe
    double flow;        // flow
public:
    Pipe(Node<T> *orig,Node<T> *dest, double c);

    Node<T> *getDest() const;
    Node<T> *getOrig() const;
    Pipe<T> *getReverse() const;
    double getFlow() const;
    double getCapacity() const;

    void setReverse(Pipe<T> *reverse);
    void setDest(Node<T> *dest);
    void setCapacity(double capacity);
    void setFlow(double flow);
};


template<class T>
void Pipe<T>::setFlow(double flow) {
    this->flow = flow;
}

template<class T>
void Pipe<T>::setReverse(Pipe<T> *reverse) {
    this->reverse = reverse;
}

template<class T>
double Pipe<T>::getFlow() const {
    return this->flow;
}

template<class T>
Pipe<T> *Pipe<T>::getReverse() const {
    return this->reverse;
}

template<class T>
Node<T> *Pipe<T>::getOrig() const {
    return this->orig;
}

template <class T>
Node<T>::Node(T type) {
    this->type = type;
}

/*
template <class T>
Graph<T>::Graph(std::unordered_map<std::string, Node<T>*> nodes){
   this->nodes = nodes;
}
 */

template <class T>
std::vector<Node<T> *> Graph<T>::getNodeSet() const {
    std::vector<Node<T> *> nodesKeys;
    nodesKeys.reserve(nodes.size());
    for(auto kv: nodes) {
        nodesKeys.push_back(kv.second);
    }
    return nodesKeys;
}

template <class T>
Node<T>* Graph<T>::findNode(const T &in) const {
    for(auto it = nodes.begin(); it!= nodes.end(); it++) {
        if(it->second->getType() == in) {
            return it->second;
        }
    }
    return nullptr;
}

template <class T>
int Graph<T>::getNumNode() const {return nodes.size();}

template <class T>
bool Graph<T>::addNode(const std::string &s,const T &type) {
    if(findNode(type) != NULL)
        return false;
    nodes.insert({s,new Node<T>(type)});
    return true;
}

template <class T>
bool Graph<T>::removeNode(const T &type) {
    for(auto it = nodes.begin(); it != nodes.end(); it++) {
        if((*it).second->getType() == type) {
            auto n = *it;
            nodes.erase(it);
            for(auto u : nodes) {
                u.second->removePipe(n.second);
            }
            return true;
        }
    }
    return false;
}

template<class T>
bool Graph<T>::addBidirectionalPipe(const T &source, const T &dest, double capacity) {
    auto v1 = findNode(source);
    auto v2 = findNode(dest);

    if(v1 == nullptr || v2 == nullptr) { return false; }

    Pipe<T> *e1 = v1->addPipe(v2,capacity);
    Pipe<T> *e2 = v2->addPipe(v1,capacity);

    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

template<class T>
bool Graph<T>::addPipe(const T &source, const T &dest, double capacity) {
    auto v1 = findNode(source);
    auto v2 = findNode(dest);
    if(v1 == nullptr || v2 == nullptr)
        return false;
    v1->addPipe(v2,capacity);
    return true;
}

template<class T>
bool Graph<T>::removePipe(const T &source, const T &dest) {
    auto v1 = findNode(source);
    auto v2 = findNode(dest);
    if(v1 == nullptr || v2 == nullptr) {
        return false;
    }
    return v1->removePipe(v2);
}

template <class T>
std::vector<T> Graph<T>::dfs() const {
    std::vector<T> res;
    for(Node<T> *node : getNodeSet()) {
        node->setVisited(false);
    }
    for(Node<T> *node: getNodeSet()) {
        if(!node->isVisited()) {
            dfsVisit(node,res);
        }
    }
    return res;
};

template <class T>
std::vector<T> Graph<T>::dfs(const T & source) const {
    std::vector<T> res;
    for(Node<T> *node : getNodeSet()) {
        node->setVisited(false);
    }
    Node<T> *targetNode = findNode(source);
    if(targetNode == nullptr) return std::vector<T>();
    dfsVisit(targetNode,res);
    return res;
}

template <class T>
void Graph<T>::dfsVisit(Node<T> *v, std::vector<T> & res) const {
    v->setVisited(true);
    res.push_back(v->getType());
    for(Pipe<T> *pipe : v->getPipes()) {
        Node<T> *destNode = pipe->getDest();
        if(!destNode->isVisited()) {
            dfsVisit(destNode,res);
        }
    }
    return;
}

template <class T>
std::vector<T> Graph<T>::bfs(const T &source) const {
    std::vector<T> res;
    Node<T> *targetNode = findNode(source);
    std::queue<Node<T> *> nodesQueue;
    if(targetNode == nullptr) return res;

    for(Node<T> * node : getNodeSet()) {
        node->setVisited(false);
    }

    targetNode->setVisited(true);
    nodesQueue.push(targetNode);

    while (!nodesQueue.empty()) {
        auto currentNode = nodesQueue.front();
        nodesQueue.pop();

        res.push_back(currentNode->getType());
        for(Pipe<T> *pipe : currentNode->getPipes()) {
            Node<T> *adjNode = pipe->getDest();
            if(!adjNode->isVisited()) {
                nodesQueue.push(adjNode);
                adjNode->setVisited(true);
            }
        }
    }

    return res;
}

template <class T>
T Node<T>::getType() const { return type; }

template <class T>
void Node<T>::setType(T type) const { this->type = type; }

template <class T>
bool Node<T>::isVisited() const { return visited; };

template <class T>
void Node<T>::setVisited(bool v) { this->visited = v;};

template <class T>
bool Node<T>::isProcessing() const { return this->processing; }

template <class T>
void Node<T>::setProcessing(bool p) { this->processing = p; };

template <class T>
int Node<T>::getInDegree() const { return this->inDegree; }

template <class T>
void Node<T>::setInDegree(int inDegree) { this->inDegree = inDegree; }

template <class T>
void Node<T>::setLow(int low) { this->low = low; };

template <class T>
void Node<T>::setNum(int num) { this->num = num; };

template <class T>
int Node<T>::getNum() const { return this->num; }

template <class T>
int Node<T>::getLow() const { return this->low; }

template <class T>
std::vector<Pipe<T>*> Node<T>::getPipes() const { return this->pipes; }

template <class T>
void Node<T>::setPipes(const std::vector<Pipe<T>*> pipes) { this->pipes = pipes; }

template <class T>
Pipe<T> * Node<T>::addPipe(Node<T> *dest, double capacity) {
    auto newPipe = new Pipe<T>(this,dest,capacity);
    this->pipes.push_back(newPipe);
    dest->incoming.push_back(newPipe);
    return newPipe;
}

template <class T>
bool Node<T>::removePipe(Node<T> *dest) {
    for(auto it = pipes.begin(); it != pipes.end(); it++) {
        if((*it)->getDest() == dest) {
            pipes.erase(it);
            return true;
        }
    }
    return false;
}

template <class T>
bool Node<T>::deletePipe(Pipe<T> *pipe) {
    Node<T> *dest = pipe->getDest();
    auto it = dest->incoming.begin();
    while(it != dest->incoming.end()) {
        if((*it)->getOrig()->getType() == this->type) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete pipe;
}

template<class T>
Pipe<T>::Pipe(Node<T> *orig, Node<T> *dest, double c) {
    this->orig = orig;
    this->dest = dest;
    this->capacity = c;
}

template <class T>
Node<T>* Pipe<T>::getDest() const { return this->dest; }

template <class T>
void Pipe<T>::setDest(Node<T> *dest) { this->dest = dest; };

template <class T>
double Pipe<T>::getCapacity() const { return this->capacity; };

template <class T>
void Pipe<T>::setCapacity(double capacity) { this->capacity = capacity; };