//
// Created by Joseph Luis González Pastora on 8/10/18.
//

#ifndef ADTLIBRARY_NODEGRAPH_H
#define ADTLIBRARY_NODEGRAPH_H

template <typename T>
class NodeGraph {
public:
    NodeGraph(T Xpos,T Ypos, int objectID = 0);

    int getObjectID() const;

    void setObjectID(int ObjectID);

    T getXpos() const;

    void setXpos(T Xpos);

    T getYpos() const;

    void setYpos(T Ypos);

    int getHeuristic() const;

    void setHeuristic(int Heuristic);

    int getG() const;

    void setG(int g);

    NodeGraph<T> *getPrevious() const;

    void setPrevious(NodeGraph<T> *previous);

    int getF() const;

    void setF(int F);

private:
    T Xpos;
    T Ypos;
    int ObjectID;
    int g;
    int Heuristic;
    int F;
    NodeGraph<T>* previous;


};


#endif //ADTLIBRARY_NODEGRAPH_H