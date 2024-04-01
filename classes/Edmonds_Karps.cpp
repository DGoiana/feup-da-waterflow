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

void testVisit(std::queue<Node *> &q, Pipe *e, Node *w, double residual){
    if(!w->isVisited() && residual > 0){
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
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
            testVisit(q, p, p->getDest(), p->getCapacity() - p->getFlow());
        }

        for(Pipe *p: w->getIncoming()) {
            testVisit(q, p, p->getOrig(), p->getFlow());
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

void augmentGraph(Node *s, Node *t, float minFlow) {
    for(auto currentNode = t; currentNode != s;) {
        auto p = currentNode->getPath();
        double flow = p->getFlow();
        if(p->getDest() == currentNode) {
            p->setFlow(flow + minFlow);
            currentNode = p->getOrig();
        } else {
            p->setFlow(flow - minFlow);
            currentNode = p->getDest();
        }
    }
}