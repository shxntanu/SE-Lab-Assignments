#include <iostream>
using namespace std;

class Node
{
  string data;
  int id;
  Node *next;
public:
  Node()
  {
    data=" ";
    id=0;
    next=NULL;
  }
  
  Node(string value,int i)
  {
    data=value;
    id=i;
    next=NULL;
  }
  
  friend class Graph;
  friend class Queue;
};


class Queue{
public:
  int f,r;
  Node *queue[10];
public:
  Queue(){
    f=-1;
    r=-1;
    for(int i=0;i<10;i++){
      queue[i]=NULL;
    }
  }

  bool empty(){
    if(f==-1)  
      return true;
    return false;
  }

  bool full(){
    if(f==(r+1)%9)
      return true;
    return false;
  }

  void push(Node *x){
    if(full())
      return;

    if(f==-1)
      f++;
    r = (r+1)%9;
    queue[r]=x;
    return;

  }
  Node* pop(){
    if(empty())
      return NULL;

    Node *temp = queue[f];
    if(f==r){
      f=-1;
      r=-1;
    }
    else
      f = (f+1)%9;
    return temp;
  }
};


class Graph
{
  Node *temp, *entry;
  int total, no;
  string val, name;
  int dest_id, c_id;
  Node *adj[10];
    int *visited;
  int indegree[10];
  int outdegree[10];
public:
  Graph()
  {
    for(int i=0;i<10;i++){
      adj[i]=NULL;
    }
  }
  
  void read();
  void bfs(int);
  void dfs(int);
  void traverse(int[], int);
  void in();
  void out();
    void connected();
  void display();
};


void Graph::read(){
  cout<<"\nEnter total vertices in graph: ";
  cin>>total;

  for(int i=0;i<total;i++){
    cout<<"\nEnter the vertex name: ";
    cin>>name;
        cout<<"Enter vertex id: ";
        cin>>dest_id;
    temp=new Node(name,dest_id);
    adj[i]=temp;
    cout<<"Enter the no. of vertices connected to "<<i<<"th vertex: ";
    cin>>no;
    outdegree[i] = no;
    indegree[i] = no;
    for(int j=0;j<no;j++){
      cout<<"Enter the adjacent vertex name: ";
      cin>>val;
      cout<<"Enter the adjacent vertex id: ";
      cin>>c_id;
      entry=new Node(val,c_id);
      temp->next=entry;
      temp=entry;
    }
  }
}


void Graph:: display()
{
  Node* temp;
  for(int i=0;i<total;i++){
    cout<<i<<" | ";
    temp=adj[i];
    while(temp!=NULL){
      cout<<temp->data<<"-->";
      temp=temp->next;
    }
    cout<<endl;
  }
}


void Graph::bfs(int key)
{
    cout<<"BFS Traversal: ";
  visited = new int[total];
  for(int i=0;i<total;i++){
    visited[i]=0;
  }
  
  Queue q;
  Node* curr;
  int curr_id;
  Node* temp=adj[key];
  visited[key]=1;
  q.push(temp);
  while(!q.empty()){
    curr=q.pop();
    cout<<curr->id<<"-"<<curr->data<<"  ";

    for(int j=key;j<=total;j++){
        Node* ptr=adj[j];
        
        while(ptr!=NULL){
          curr_id=ptr->id;
          if(visited[curr_id]==0){
            q.push(ptr);
            visited[curr_id]=1;
          }
      ptr=ptr->next;
        }
    }
    }
    cout<<endl;
}


void Graph::traverse(int v[], int key)
{
    Node *temp = adj[key];
    cout<<temp->id<<"-"<<temp->data<<"  ";
    v[key] = 1;
    while (temp != NULL)
    {
        if (v[temp->id] == 0)
        {
            traverse(v, temp->id);
        }
        temp = temp->next;
    }
}

void Graph::dfs(int key){
  cout<<"DFS Traversal: ";
  
  visited = new int[total];
  for(int i=0;i<total;i++){
    visited[i]=0;
  }

    traverse(visited, key);
    cout<<endl;
}


void Graph::in()
{
    Node *temp = adj[0];
    cout<<"\nIndegrees: \n";
    for (int i=0; i<total; i++)
    {
        cout<<temp->id<<"-"<<temp->data<<": "<<indegree[i]<<endl;
        temp = temp->next;
    }
    cout<<endl;
}


void Graph::out()
{
    Node *temp = adj[0];
    cout<<"\nOutdegrees: \n";
    for (int i=0; i<total; i++)
    {
        cout<<temp->id<<"-"<<temp->data<<": "<<outdegree[i]<<endl;
        temp = temp->next;
    }
    cout<<endl;
}


void Graph::connected()
{
    bool con = true;
    for (int i=0; i<total; i++)
    {
        if (visited[i] == 0)
        {
            con = false;
            break;
        }
    }
    if (con)
        cout<<"Graph is connected";
    else
        cout<<"Graph is not connected";
}


int main(){
  int ch;
  char choice;
  int val;
  Graph gp;
  do{
    cout<<"\nOPERATIONS:\n";
    cout<<"1.Insert\n2.BFS\n3.DFS\n4.Indegree\n5.Outdegree\n6.Check if Connected\n7.Display Adjacency List\n";
    cout<<"Enter your choice: ";
    cin>>ch;
    switch(ch){
    case 1:
      gp.read();
      break;
    case 2:
      cout<<"Enter the starting vertex: ";
      cin>>val;
      gp.bfs(val);
      break;
    case 3:
      cout<<"Enter the starting vertex: ";
      cin>>val;
      gp.dfs(val);
      break;
    case 4:
        gp.in();
        break;
    case 5:
        gp.out();
        break;
    case 6:
            gp.connected();
            break;
        case 7:
      gp.display();
      break;
    }
    cout<<"\nContinue? (y/n): ";
    cin>>choice;
  }while(choice=='y' || choice=='Y');
  return 0;
}
