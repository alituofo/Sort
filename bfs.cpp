//�����ڽӱ��ʾͼ�����������������
#define MAXQSIZE 100
#include <iostream>
using namespace std;

#define MVNum 100							//��󶥵���
typedef char VerTexType;					//���趥�����������Ϊ�ַ��� 
typedef int ArcType; 
//-------------ͼ���ڽӱ�---------------------
typedef struct ArcNode{                		//�߽�� 
    int adjvex;                          	//�ñ���ָ��Ķ����λ�� 
    struct ArcNode *nextarc;          		//ָ����һ���ߵ�ָ�� 
}ArcNode; 

typedef struct VNode{ 
    VerTexType data;                    	//������Ϣ
    ArcNode *firstarc;                		//ָ���һ�������ö���ıߵ�ָ�� 
}VNode, AdjList[MVNum];               		//AdjList��ʾ�ڽӱ����� 

typedef struct{
    AdjList vertices;                 		//�ڽӱ� 
    int vexnum, arcnum;              		//ͼ�ĵ�ǰ�������ͱ��� 
}ALGraph;

bool visited[MVNum];           				//���ʱ�־���飬���ֵΪ"false" 

typedef struct{
	ArcType *base;							//��ʼ���Ķ�̬����洢�ռ�
	int front;								//ͷָ�룬�����в��գ�ָ���ͷԪ��
	int rear;								//βָ�룬�����в��գ�ָ���βԪ�ص���һ��λ��
}sqQueue;


void InitQueue(sqQueue &Q){
	//����һ���ն���Q
	Q.base = new ArcType[MAXQSIZE];
	if(!Q.base)     exit(1);				//�洢����ʧ��
	Q.front = Q.rear = 0;
}//InitQueue

void EnQueue(sqQueue &Q, ArcType e){
	//����Ԫ��eΪQ���µĶ�βԪ��
	if((Q.rear + 1) % MAXQSIZE == Q.front)
		return;
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
}//EnQueue

bool QueueEmpty(sqQueue Q){
	//�ж��Ƿ�Ϊ�ն�
	if(Q.rear == Q.front)
		return true;
	return false;
}//QueueEmpty

void DeQueue(sqQueue &Q, ArcType &u){
	//��ͷԪ�س��Ӳ���Ϊu 
	u = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
}//DeQueue   								
//--------------------------------------------------

int LocateVex(ALGraph G , VerTexType v){
	//ȷ����v��G�е�λ��
	for(int i = 0; i < G.vexnum; ++i)
		if(G.vertices[i].data == v)
			return i;
		return -1;
}//LocateVex

void CreateUDG(ALGraph &G){ 
	//�����ڽӱ��ʾ������������ͼG
	int i , k;
	
	cout <<"�������ܶ��������ܱ������Կո����:";
	cin >> G.vexnum >> G.arcnum;				//�����ܶ��������ܱ��� 
    cout << endl;
	
	cout << "���������ƣ���a" << endl;

	for(i = 0; i < G.vexnum; ++i){          	//������㣬�����ͷ����
		cout << "�������" << (i+1) << "���������:";
		cin >> G.vertices[i].data;           	//���붥��ֵ 
		G.vertices[i].firstarc=NULL;			//��ʼ����ͷ����ָ����ΪNULL 
    }//for
	cout << endl;
    
	cout << "����������Ķ��㣬��a b" << endl;

	for(k = 0; k < G.arcnum;++k){        		//������ߣ������ڽӱ�
		VerTexType v1 , v2;
		int i , j;
		cout << "�������" << (k + 1) << "���������Ķ���:";
		cin >> v1 >> v2;                 		//����һ������������������
		i = LocateVex(G, v1);  j = LocateVex(G, v2);
		//ȷ��v1��v2��G��λ�ã���������G.vertices�е���� 
		
		ArcNode *p1=new ArcNode;               	//����һ���µı߽��*p1 
		p1->adjvex=j;                   		//�ڽӵ����Ϊj 
		p1->nextarc= G.vertices[i].firstarc;  G.vertices[i].firstarc=p1;  
		//���½��*p1���붥��vi�ı߱�ͷ��
		
		ArcNode *p2=new ArcNode;                //������һ���ԳƵ��µı߽��*p2 
		p2->adjvex=i;                   		//�ڽӵ����Ϊi 
		p2->nextarc= G.vertices[j].firstarc;  G.vertices[j].firstarc=p2;  
		//���½��*p2���붥��vj�ı߱�ͷ�� 
    }//for 
}//CreateUDG

void bfs(ALGraph G, int v)
{
    
	ArcType u;
	ArcType w;
	sqQueue Q;
    InitQueue(Q);
	
	cout << G.vertices[v].data << "   ";  
	visited[v] = true;    						//���ʵ�v�����㣬���÷��ʱ�־������Ӧ����ֵΪtrue 
	ArcNode *p = G.vertices[v].firstarc;		//pָ��v�ı�����ĵ�һ���߽�� 
	
    EnQueue(Q, v); 
    
    while(!QueueEmpty(Q)){
 
        DeQueue(Q, u);
        p = G.vertices[u].firstarc;
        while(p!=NULL){
 
			w = p->adjvex;
			if(!visited[w]){	           										//wΪu����δ���ʵ��ڽӶ��� 
				cout << G.vertices[w].data<< "  ";   
				EnQueue(Q, w);
				visited[p->adjvex] = 1;													//w���� 
			}//if 
			p = p->nextarc;
		}//for

    }
}



int main(){
	cout << "************�����ڽӱ��ʾͼ�����������������**************" << endl << endl;
	ALGraph G;
	CreateUDG(G);
	cout << endl;
	cout << "������ͨͼG������ɣ�" << endl << endl;

	cout << "�����������ͨͼ����ʼ�㣺";
	VerTexType c;
	cin >> c;
	
	int i;
	for(i = 0 ; i < G.vexnum ; ++i){
		if(c == G.vertices[i].data)
			break;
	}
	cout << endl;
	while(i >= G.vexnum){
		cout << "�õ㲻���ڣ����������룡" << endl;
		cout << "�����������ͨͼ����ʼ�㣺";
		cin >> c;
		for(i = 0 ; i < G.vexnum ; ++i){
			if(c == G.vertices[i].data)
				break;
		}
	}

	cout << "���������������ͼ�����" << endl;
	bfs(G , i);
	
	cout <<endl;
	return 0;
}//main
