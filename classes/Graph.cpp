#include "Graph.h"
#include <iostream>

Node* Graph::findNode(const std::string &code) const {
   for(auto it = this->nodes.begin(); it != nodes.end(); it++) {
      if(it->first == code) {
         return it->second;
      }
   }
   return nullptr;
}

std::vector<Node*> Graph::getNodeSet() const {
   std::vector<Node*> nodesKeys;
   nodesKeys.reserve(nodes.size());
   for(auto kv: nodes) {
      nodesKeys.push_back(kv.second);
   }
   return nodesKeys;
}

bool Graph::addNode(const std::string &s, NetworkPoint *info) {
   if(findNode(s) != NULL)
      return false;
   nodes.insert({s, new Node(info)});
   return true;
}

bool Graph::removeNode(const NetworkPoint &info) {
   auto n = findNode(info.getCode());
   for(auto p: n->getPipes()){
       removePipe(info.getCode(), p->getDest()->getInfo()->getCode());
   }
   for(auto p: n->getIncoming()){
       removePipe(p->getOrig()->getInfo()->getCode(), info.getCode());
   }
   return false;
}

bool Graph::addBidirectionalPipe(const std::string &source, const std::string &dest, double capacity) {
   auto v1 = findNode(source);
   auto v2 = findNode(dest);

   if(v1 == nullptr || v2 == nullptr) { return false; }

   Pipe *e1 = v1->addPipe(v2,capacity);
   Pipe *e2 = v2->addPipe(v1,capacity);

   e1->setReverse(e2);
   e2->setReverse(e1);
   return true;
}

bool Graph::addPipe(const std::string &source, const std::string &dest, double capacity) {
   auto v1 = findNode(source);
   auto v2 = findNode(dest);
   if(v1 == nullptr || v2 == nullptr)
      return false;
   v1->addPipe(v2,capacity);
   return true;
}

bool Graph::removePipe(const std::string &source, const std::string &dest) {
   auto v1 = findNode(source);
   auto v2 = findNode(dest);
   if(v1 == nullptr || v2 == nullptr) {
      return false;
   }
   return v1->removePipe(v2);
}

std::vector<NetworkPoint> Graph::dfs() const {
   std::vector<NetworkPoint> res;
   for(Node *node : getNodeSet()) {
      node->setVisited(false);
   }
   for(Node *node: getNodeSet()) {
      if(!node->isVisited()) {
         dfsVisit(node,res);
      }
   }
   return res;
};

std::vector<NetworkPoint> Graph::dfs(const std::string &source) const {
   std::vector<NetworkPoint> res;
   for(Node *node : getNodeSet()) {
      node->setVisited(false);
   }
   Node *targetNode = findNode(source);
   if(targetNode == nullptr) return std::vector<NetworkPoint>();
   dfsVisit(targetNode,res);
   return res;
}

void Graph::dfsVisit(Node *v, std::vector<NetworkPoint> &res) const {
   v->setVisited(true);
   res.push_back(*(v->getInfo()));
   for(Pipe *pipe : v->getPipes()) {
      Node *destNode = pipe->getDest();
      if(!destNode->isVisited()) {
         dfsVisit(destNode, res);
      }
   }
   return;
}

std::vector<NetworkPoint> Graph::bfs(const std::string &source) const {
   std::vector<NetworkPoint> res;
   Node *targetNode = findNode(source);
   std::queue<Node *> nodesQueue;
   if(targetNode == nullptr) return res;

   for(Node * node : getNodeSet()) {
      node->setVisited(false);
   }

   targetNode->setVisited(true);
   nodesQueue.push(targetNode);

   while (!nodesQueue.empty()) {
      auto currentNode = nodesQueue.front();
      nodesQueue.pop();

      res.push_back(*(currentNode->getInfo()));
      for(Pipe *pipe : currentNode->getPipes()) {
            Node *adjNode = pipe->getDest();
            if(!adjNode->isVisited()) {
               nodesQueue.push(adjNode);
               adjNode->setVisited(true);
            }
      }
   }

   return res;
}

Pipe* Node::addPipe(Node *dest, double capacity) {
   Pipe* newPipe = new Pipe(this,dest,capacity);
   this->pipes.push_back(newPipe);
   dest->incoming.push_back(newPipe);
   return newPipe;
}

bool Node::removePipe(Node *dest) {
   for(auto it = pipes.begin(); it != pipes.end(); it++) {
      if((*it)->getDest() == dest) {
         pipes.erase(it);
         return true;
      }
   }
   return false;
}

bool Node::deletePipe(Pipe *pipe) {
   Node *dest = pipe->getDest();
   auto it = dest->incoming.begin();
   while(it != dest->incoming.end()) {
      if((*it)->getOrig()->getInfo() == this->info) {
         it = dest->incoming.erase(it);
      }
      else {
         it++;
      }
   }
   delete pipe;
   return true;
}
