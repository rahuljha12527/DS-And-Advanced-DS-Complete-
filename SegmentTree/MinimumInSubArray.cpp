#include<iostream>
#include<climits>
#include<algorithm>

using namespace std;

void buildTree(int *arr,int *tree,int start,int end,int treeNode){

    if(start==end){
      
      tree[treeNode]=arr[start];
      return;
    }
    
    int mid=(start+end)/2;
    buildTree(arr,tree,start,mid,2*treeNode);
    buildTree(arr,tree,mid+1,end,2*treeNode+1);


    tree[treeNode]=min(tree[2*treeNode],tree[2*treeNode+1]);
}

void updateTree(int *arr,int *tree,int start,int end,int treeNode,int idx,int value){

    if(start==end){
       arr[idx]=value;
       tree[treeNode]=value;
       return;       
    }

    int mid=(start+end)/2;
    if(idx>mid){
        updateTree(arr,tree,mid+1,end,2*treeNode+1,idx,value);
    }
    else{
        updateTree(arr,tree,start,mid,2*treeNode,idx,value);
    }


    tree[treeNode]=min(tree[2*treeNode],tree[2*treeNode+1]);



}

int query(int *tree,int start,int end,int treeNode,int left,int right){

    if(start>right || end<left){
        return INT_MAX;

    }

    if(start>=left && end<=right ){
        return tree[treeNode];  
    }
    int mid=(start+end)/2;
    int ans1=query(tree,start,mid,2*treeNode,left,right);
    int ans2=query(tree,mid+1,end,2*treeNode+1,left,right);
    return min(ans1,ans2);
}

int main(){
    int n,q;
    cin>>n>>q;
    

    int *arr=new int[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    int *tree=new int[4*n];
    buildTree(arr,tree,0,n-1,1);

    while(q--){
        char query_T;
         cin>>query_T;
        if(query_T=='q'){
          int l,r;
          cin>>l>>r;
          
          cout<<query(tree,0,n-1,1,l-1,r-1)<<endl;
        }
        else{
           int x,y;
           cin>>x>>y;
           
           updateTree(arr,tree,0,n-1,1,x-1,y);
        }

    }


}