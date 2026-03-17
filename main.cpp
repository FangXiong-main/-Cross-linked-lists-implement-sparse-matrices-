//
//  main.cpp
//  稀疏矩阵的链式存储
//
//  Created by Fang Xiong on 2024/10/18.
//

#include <iostream>
using namespace std;
typedef int Element;
typedef class Matrix_Node
{
public :
    int line;
    int row;
    Element Ele;
    Matrix_Node * Down;
    Matrix_Node * Right;
}Node;
Node *BaseNode=new Node();
Node *BaseNode_TransPose_Matrix=NULL;
void Initialize_Node() //创建链表式矩阵（兼容稀疏矩阵）
{
    Node * Line_Tail=BaseNode;
    Node * Row_Tail=BaseNode;
    int line,row,element;
    cout<<"请输入矩阵的行数：";
    cin>>line;
    cout<<"请输入矩阵的列数：";
    cin>>row;
    BaseNode->line=line;
    BaseNode->row=row;
    for(int i=1;i<=line;i++)
    {
        Node * New_Node_Line=new Node();
        New_Node_Line->line=i;
        Line_Tail->Down=New_Node_Line;
        Line_Tail=New_Node_Line;
    }
    Line_Tail->Down=BaseNode;
    for(int j=1;j<=row;j++)
    {
        Node * New_Node_Row=new Node();
        New_Node_Row->row=j;
        Row_Tail->Right=New_Node_Row;
        Row_Tail=New_Node_Row;
    }
    Row_Tail->Right=BaseNode;
    
    Node * Current_Line=BaseNode->Down;
    Node * Current_Row=BaseNode->Right;
    
    Line_Tail=BaseNode->Down;
    Row_Tail=BaseNode->Right;
    for(int i=1;i<=line;i++)
    {
        for(int j=1;j<=row;j++)
        {
            while(Row_Tail->Down!=NULL&&Row_Tail->Down!=Current_Row)
            {
                Row_Tail=Row_Tail->Down;
            }
            cout<<"请输入第 "<<i<<" 行"<<",第 "<<j<<" 列的元素：";
            cin>>element;
            if(element==0) //值得注意的地方
            {
                if(Current_Row->row==row)
                {
                    Current_Row=BaseNode->Right;
                    //若第一行全是0
                    //Current_Row不复位会指向BaseNode从而导致后面的指针错位
                }
                else
                {
                    Current_Row=Current_Row->Right;
                }//这两条不能少，否则添加0会使指针错位！
                Row_Tail=Current_Row;
                continue;
            }
            Node * New_Node=new Node();
            New_Node->line=i;New_Node->row=j;
            New_Node->Ele=element;
            Line_Tail->Right=New_Node;
            Row_Tail->Down=New_Node;
            New_Node->Down=Current_Row;
            Line_Tail=New_Node;
            if(Current_Row->row==row)
            {
                Current_Row=BaseNode->Right;
                New_Node->Right=Current_Line;
            }
            else
            {
                Current_Row=Current_Row->Right;
            }
            Row_Tail=Current_Row;
        }
        Line_Tail->Right=Current_Line;
        Current_Line=Current_Line->Down;
        Line_Tail=Current_Line;
    }
}

void TransPose_Matrix()
{
    BaseNode_TransPose_Matrix=new Node();
    BaseNode_TransPose_Matrix->line=BaseNode->row;
    BaseNode_TransPose_Matrix->row=BaseNode->line;
    Node * Row_Search=BaseNode->Right;
    Node * Current_Row_Search=BaseNode->Right->Down;
    Node * Current_Line_Search=BaseNode->Down;
    int line=BaseNode_TransPose_Matrix->line;int row=BaseNode_TransPose_Matrix->row;int element = 0;
    Node * Line_Tail=BaseNode_TransPose_Matrix;
    Node * Row_Tail=BaseNode_TransPose_Matrix;
    for(int i=1;i<=line;i++)
    {
        Node * New_Node_Line=new Node();
        New_Node_Line->line=i;
        Line_Tail->Down=New_Node_Line;
        Line_Tail=New_Node_Line;
    }
    Line_Tail->Down=BaseNode_TransPose_Matrix;
    for(int j=1;j<=row;j++)
    {
        Node * New_Node_Row=new Node();
        New_Node_Row->row=j;
        Row_Tail->Right=New_Node_Row;
        Row_Tail=New_Node_Row;
    }
    Row_Tail->Right=BaseNode_TransPose_Matrix;
    
    Node * Current_Line=BaseNode_TransPose_Matrix->Down;
    Node * Current_Row=BaseNode_TransPose_Matrix->Right;
    
    Line_Tail=BaseNode_TransPose_Matrix->Down;
    Row_Tail=BaseNode_TransPose_Matrix->Right;
    for(int i=1;i<=line;i++)
    {
        for(int j=1;j<=row;j++)
        {
            while(Row_Tail->Down!=NULL&&Row_Tail->Down!=Current_Row)
            {
                Row_Tail=Row_Tail->Down;
            }
            if(Row_Search!=BaseNode)
            {
                if(Current_Line_Search!=BaseNode)
                {
                    if(Current_Row_Search==NULL||Current_Row_Search->line!=Current_Line_Search->line)
                    {
                        element=0;
                        Current_Line_Search=Current_Line_Search->Down;
                    }
                    else
                    {
                        element=Current_Row_Search->Ele;
                        Current_Row_Search=Current_Row_Search->Down;
                        Current_Line_Search=Current_Line_Search->Down;
                    }
                }
                if(Current_Line_Search==BaseNode)
                {
                    Current_Line_Search=BaseNode->Down;
                    Row_Search=Row_Search->Right;
                    Current_Row_Search=Row_Search->Down;
                }
            }
            if(element==0) //值得注意的地方
            {
                if(Current_Row->row==row)
                {
                    Current_Row=BaseNode_TransPose_Matrix->Right;
                    //若第一行全是0
                    //Current_Row不复位会指向BaseNode从而导致后面的指针错位
                }
                else
                {
                    Current_Row=Current_Row->Right;
                }//这两条不能少，否则添加0会使指针错位！
                Row_Tail=Current_Row;
                continue;
            }
            Node * New_Node=new Node();
            New_Node->line=i;New_Node->row=j;
            New_Node->Ele=element;
            Line_Tail->Right=New_Node;
            Row_Tail->Down=New_Node;
            New_Node->Down=Current_Row;
            Line_Tail=New_Node;
            if(Current_Row->row==row)
            {
                Current_Row=BaseNode_TransPose_Matrix->Right;
                New_Node->Right=Current_Line;
            }
            else
            {
                Current_Row=Current_Row->Right;
            }
            Row_Tail=Current_Row;
        }
        Line_Tail->Right=Current_Line;
        Current_Line=Current_Line->Down;
        Line_Tail=Current_Line;
    }
}

void Show_TransPose_Matrix()
{
    Node * Row=BaseNode->Right;
    Node * Current_Row=BaseNode->Right;
    Node * Current_Line=BaseNode->Down;
    while(Row!=BaseNode)
    {
        Current_Row=Row->Down;
        while(Current_Line!=BaseNode)
        {
            if(Current_Row==NULL||Current_Row->line!=Current_Line->line)
            {
                cout<<"0\t";
                Current_Line=Current_Line->Down;
            }
            else
            {
                cout<<Current_Row->Ele<<"\t";
                Current_Row=Current_Row->Down;
                Current_Line=Current_Line->Down;
            }
        }
        cout<<"\n";
        Current_Line=BaseNode->Down;
        Row=Row->Right;
    }
    cout<<"\n";
}

void Show_Matrix(Node * Matrix)
{
    Node * Line=Matrix->Down;
    Node * Row=Matrix->Right;
    Node * Current_Line=Line->Right;
   //Node * Current_Row=Row->Down;
    while(Line!=Matrix)
    {
        while(Row!=Matrix)
        {
            if(Current_Line->Right==NULL||Current_Line->row!=Row->row)
            {
                cout<<"0\t";
                Row=Row->Right;
            }
            else
            {
                cout<<Current_Line->Ele<<"\t";
                Current_Line=Current_Line->Right;
                Row=Row->Right;
            }
        }
        cout<<"\n";
        Row=Matrix->Right;
        Line=Line->Down;
        Current_Line=Line->Right;
    }
    cout<<"\n";
}
void Distory_Link_Matrix(Node * Dis)
{
    Node * Dis_Right=Dis->Right;
    Node * Dis_Down=NULL;Node * Delete_Node=NULL;
    while(Dis_Right!=Dis)
    {
        Dis_Down=Dis_Right->Down;
        while(Dis_Down!=Dis_Right)
        {
            Delete_Node=Dis_Down;
            Dis_Down=Dis_Down->Down;
            delete Delete_Node;
        }
        Dis_Right=Dis_Right->Right;
    }
    Dis_Right=Dis->Right;Dis_Down=Dis->Down;
    while(Dis_Right!=Dis)
    {
        Delete_Node=Dis_Right;
        Dis_Right=Dis_Right->Right;
        delete Delete_Node;
    }
    while(Dis_Down!=Dis)
    {
        Delete_Node=Dis_Down;
        Dis_Down=Dis_Down->Down;
        delete Delete_Node;
    }
    delete Dis;
    Dis=NULL;
    cout<<"已销毁原始矩阵\n"<<endl;
}
int main()
{
    int choice=0;
    Initialize_Node();
    cout<<"————下面是矩阵的原始输出————"<<endl;
    Show_Matrix(BaseNode);
    TransPose_Matrix();
    cout<<"\n是否销毁原始矩阵？"<<endl;
    cout<<"1-是 2-否"<<endl;
    cout<<"请选择：";
    cin>>choice;
    if(choice==1)
    {
        Distory_Link_Matrix(BaseNode);
    }
    cout<<"\n\n————下面是转置矩阵的输出————"<<endl;
    Show_Matrix(BaseNode_TransPose_Matrix);
}
