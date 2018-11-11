#ifndef LOG_KRUSKAL_H
#define LOG_KRUSKAL_H


#include "../ADTStructures/Graph.h"
#include <list>

class Kruskal {
public:
    static std::list<Cell<int>*>* findPath(Graph* graph, int iTarget, int jTarget, int iPlayer, int jPlayer);

private:
    static Graph* MST;
    static int xTarget;
    static int yTarget;

    //se crea un arbol de expansion minima para un solo nodo objetivo. Si este cambia, se recalculara

    static void findMST(Graph* graph, int iStart, int jStart, int iPlayer, int jPlayer);
    static void printpath(std::list<Cell<int>*> path);
    static void printpath(std::vector<Cell<int>*> path);
};


#endif //LOG_KRUSKAL_H