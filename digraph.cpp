#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<limits>

#define LONGMAX 99999L

using namespace std;

struct AdjNode {
    long weight;
    int vtx;
    struct AdjNode* next;

    AdjNode() {
        weight=(long)LONGMAX;
        vtx=-1;
        next=NULL;
    }

    AdjNode(int vert, long wt) {
        weight=wt;
        vtx=vert;
        next=NULL;
    }
};

typedef struct {
    AdjNode* head;
    AdjNode* tail;
} AdjList;

class Graph {
private:
    int E;
    int V;
    bool weighted, directed;
    AdjList* alist;
    //members for shortest_path lookup
    char *known;
    int *pred;
    long *cost;

public:
    Graph() { 
        V=0; weighted=false; directed=false; E=0;alist=NULL;
        cost=NULL;known=NULL;pred=NULL;
    }

    Graph(int vcount, bool iweighted=false, bool idirected=false) {
        V=vcount;
        E=0;
        weighted=iweighted;
        directed=idirected;
        alist=(AdjList*)malloc(V*sizeof(AdjList));
        for(int i=0;i<V;i++) {
            alist[i].head=new AdjNode;
            alist[i].head->weight=99999L;
            alist[i].head->vtx=i;
            alist[i].head->next=NULL;
            alist[i].tail=alist[i].head;
        }

        //Initialize shortest_path lookup members
        known = new char(V);
        pred = new int(V);
        cost = new long(V);
        for(int i=0;i<V;i++) {
            cost[i]=99999L;
            pred[i]=-1;
            known[i]=0;
        }
    }

    ~Graph() {
        for(int i=0;i<V;i++) {
            while(alist[i].head->next) {
                AdjNode* nd=alist[i].head->next;
                alist[i].head->next=nd->next;
                delete nd;
            }
            delete alist[i].head;
            alist[i].head=alist[i].tail=NULL;
        }
        delete known;
        delete pred;
        delete cost;
    }

    inline int getVertices() { return V;}

    bool isweighted() { return weighted; }
    bool isdirected() { return directed; }

    void add_edge(int src, int tgt, long weight) {
        AdjNode *nd = alist[src].head;
        if(alist[src].tail->weight <= weight) {
            alist[src].tail->next=new AdjNode(tgt,weight);
            alist[src].tail=alist[src].tail->next;
            return;
        }
        while(nd->next && nd->next->weight<= weight) {
            if(nd->next->weight == weight && tgt < nd->next->vtx)
                break;
            nd=nd->next;
        }
        AdjNode *newv = new AdjNode(tgt,weight);
        newv->next=nd->next;
        nd->next=newv;
        E++;
    }

    bool BFS(int src, int dest) {
        queue<int> ndQueue;
        bool found = false;
        AdjNode *nd = NULL;
        ndQueue.push(src);
        char *visited = new char(this->V);
        memset(visited, 0, this->V);
        pred[src]=-1;
        while(!ndQueue.empty() && !found) {
            int indx = ndQueue.front();
            ndQueue.pop();
            nd = alist[indx].head;
            if(nd) visited[nd->vtx] = 1;
            while(nd) {
                if(nd->vtx == dest) {
                    found = true;
                    pred[nd->vtx]=indx;
                    break;
                }
                if(!visited[nd->vtx]) {
                    ndQueue.push(nd->vtx);
                    pred[nd->vtx]=indx;
                }
                nd=nd->next;
            }
        }
        return found;
    }

    void DFS(AdjNode *nd, long runcost) {
        cout<<"\nDFS:"<<nd->vtx<<"runcost("<<runcost<<")"<<endl;
        AdjNode *t = nd->next;
        while(t) {
            cout<<"t:"<<t->vtx<<"("<<cost[t->vtx]<<")-->"<<(runcost+t->weight);
            if(cost[t->vtx] > (runcost+t->weight)) {
                cost[t->vtx] = runcost+t->weight;
                known[t->vtx] = 1;
                pred[t->vtx] = nd->vtx;
                DFS(alist[t->vtx].head, runcost+t->weight);
            }
            t=t->next;
            cout<<endl<<"---------------"<<endl;
        }
        cout<<endl<<"+++++++++++++++++++"<<endl;
    }

    void print_route(int src, int dest) {
        int ind=dest;
        string route;
        char element[4]={0};
        route=to_string(dest);
        cout<<"print_route:"<<endl;
        ind=pred[ind];
        while(ind != src) {
            snprintf(element, 4, "%d->", ind);
            route=element+route;
            ind=pred[ind];
        }
        snprintf(element, 4, "%d->", ind);
        route=element+route;

        cout<<"\t"<<route<<endl;
    }

    void shortest_path(int src, int dest) {
        cost[src]=0;
        known[src]=1;
        pred[src]=-1;
        cout<<"alist[src].head:"<<alist[src].head->vtx<<"("<<cost[src]<<")"<<endl;
        DFS(alist[src].head, cost[src]);
        //stack<int> route;
        if(known[dest]) {
            cout<<"Shorted path cost from "<<src<<" to "<<dest<<": "<<cost[dest]<<endl;
            print_route(src, dest);
        }
        else
            cout<<"DFS:"<<src<<" and "<<dest<<" are not connected"<<endl;
    }

    void print() {
        cout<<"Total edges in graph:"<<E<<endl;
        cout<<"Adjecency lists for ";
        for(int i=0;i<V;i++) {
            AdjNode* nd = alist[i].head;
            cout<<endl<<"\tVert["<<nd->vtx<<"]-->";
            nd=nd->next;
            while(nd) {
                cout<<nd->vtx<<"("<<nd->weight<<")-->";
                nd=nd->next;
            }
            cout<<"NULL";
        }
        cout<<endl;
    }
};

void create_graph_from_file(Graph &G, ifstream &ifs ) {

    int v1,v2;
    long wt;
    int counter=0;
    ifs>>counter;
    while(ifs.good() && counter) {
        if(G.isweighted())
            ifs>>v1>>v2>>wt;
        else {
            ifs>>v1>>v2;
            wt=1;
        }
        --counter;
        if(v1>=G.getVertices() || v2>=G.getVertices() || v1==v2) {
            cout<<"v1 and v2 should not be same and in limits of 0-"<<G.getVertices()-1<<endl;
            continue;
        }
        else cout<<v1<<" "<<v2<<" "<<wt<<endl;
        G.add_edge(v1,v2,wt);
        if(!G.isdirected())
            G.add_edge(v2,v1,wt);
    }
}

int main() {
    int vcount, v1, v2;
    char fname[1024] = {0};

    cout<<"Enter input file name:";
    //Input file should be of the below format
    /*
    m<vertices>
    n<edges>
    <start> <end> weight
    :(n rows )
    <start v> <end v> for BFS
    */
    cin>>fname;
    std::ifstream ifs(fname, ifstream::in);

    ifs>>vcount;
    Graph g(vcount, true, true);
    create_graph_from_file(g, ifs);
    g.print();

    ifs>>v1>>v2;
    cout<<"start and end vertices for BFS:"<<v1<<" "<<v2<<endl;
    if(g.BFS(v1, v2)) {
        cout<<"BFS:"<<v1<<" and "<<v2<<" are connected"<<endl;
        g.print_route(v1, v2);
    }
    else
        cout<<v1<<" and "<<v2<<" are not connected"<<endl;
    g.shortest_path(v1, v2);
    return 0;
}

