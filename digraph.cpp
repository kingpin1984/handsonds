#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<queue>
#include<limits>

#define LONGMAX std::numeric_limits<long long>::max()

using namespace std;

struct AdjNode {
    double weight;
    int vtx;
    struct AdjNode* next;

    AdjNode() {
        weight=(double)LONGMAX;
        vtx=-1;
        next=NULL;
    }

    AdjNode(int vert, double wt) {
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
public:
    int E;
    int V;
    AdjList* alist;

    Graph() { V=0; E=0;alist=NULL;}

    Graph(int vcount) {
        V=vcount;
        E=0;
        alist=(AdjList*)malloc(V*sizeof(AdjList));
        for(int i=0;i<V;i++) {
            alist[i].head=new AdjNode;
            alist[i].head->weight=LONGMAX;
            alist[i].head->vtx=i;
            alist[i].head->next=NULL;
            alist[i].tail=alist[i].head;
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
    }

    void add_edge(int src, int tgt, double weight) {
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
        double spath_wt = 0, this_wt=0;
        char *visited = new char(this->V);
        while(!ndQueue.empty()) {
            int indx = ndQueue.front();
            ndQueue.pop();
            nd = alist[indx].head;
            if(nd) visited[nd->vtx] = 1;
            while(nd) {
                if(nd->vtx == dest) found = true;
                if(!visited[nd->vtx])
                    ndQueue.push(nd->vtx);
                nd=nd->next;
            }
        }
        return found;
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
    double wt;
    int counter=0;
    ifs>>counter;
    while(ifs.good() && counter) {
        ifs>>v1>>v2>>wt;
        --counter;
        if(v1>=G.V || v2>=G.V || v1==v2) {
            cout<<"v1 and v2 should not be same and in limits of 0-"<<G.V-1<<endl;
            continue;
        }
        else cout<<v1<<" "<<v2<<" "<<wt<<endl;
        G.add_edge(v1,v2,wt);
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
    Graph g(vcount);
    create_graph_from_file(g, ifs);
    g.print();

    ifs>>v1>>v2;
    cout<<"start and end vertices for BFS:"<<v1<<" "<<v2<<endl;
    if(g.BFS(v1, v2))
        cout<<v1<<" and "<<v2<<" are connected"<<endl;
    else
        cout<<v1<<" and "<<v2<<" are not connected"<<endl;
    return 0;
}

