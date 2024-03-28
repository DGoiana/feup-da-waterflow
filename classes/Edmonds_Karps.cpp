#include "Edmonds_Karps.h"

float edmondsKarp(Graph *g, std::string source, std::string dest) {
    Node* s = g->findNode(source);
    Node* t = g->findNode(dest);

    for(Node* node : g->getNodeSet()) {
        for(Pipe *p : node->getPipes()) {
            p->setFlow(0);
        }
    }

    float minFlow;
    float maxFlow = 0;

    while(findPath(g,s,t)) {
        minFlow = getMinFlow(s,t);
        augmentGraph(s,t,minFlow);
        maxFlow += minFlow;
    }

    return maxFlow;
}

bool findPath(Graph *g,Node *s, Node *t) {
    for(Node *n : g->getNodeSet()) {
        n->setVisited(false);
    }

    s->setVisited(true);
    std::queue<Node *> q;
    q.push(s);

    while(!q.empty() && !t->isVisited()) {
        Node *w = q.front();
        q.pop();

        for(Pipe *p: w->getPipes()) {
            auto pipeDest = p->getDest();
            if(!pipeDest->isVisited() && p->getCapacity() - p->getFlow() > 0) {
                pipeDest->setVisited(true);
                pipeDest->setPath(p);
                q.push(pipeDest);
            }
        }

        for(Pipe *p: w->getIncoming()) {
            auto pipeOrig = p->getOrig();
            if(!pipeOrig->isVisited() && p->getFlow() > 0) {
                pipeOrig->setVisited(true);
                pipeOrig->setPath(p);
                q.push(pipeOrig);
            }
        }
    }

    return t->isVisited();
}

float getMinFlow(Node *s, Node *t) {
    float minFlow = INF;
    for(Node *currentNode = t; currentNode != s;){
        auto p = currentNode->getPath();
        if(p->getDest() == currentNode) {
            minFlow = std::min(minFlow,(float) (p->getCapacity() - p->getFlow()));
            currentNode = p->getOrig();
        } else {
            minFlow = std::min(minFlow,(float) (p->getFlow()));
            currentNode = p->getDest();
        }
    }
    return minFlow;
}

void augmentGraph(Node *s, Node *t,float minFlow) {
    for(auto currentNode = t; currentNode != s;) {
        auto p = currentNode->getPath();
        if(p->getDest() == currentNode) {
            p->setFlow(p->getFlow() + minFlow);
            currentNode = p->getOrig();
        } else {
            p->setFlow(p->getFlow() - minFlow);
            currentNode = p->getDest();
        }
    }
}