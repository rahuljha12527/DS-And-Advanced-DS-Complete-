#include<iostream>
#include<utility>
#include<algorithm>
#include<climits>
using namespace std;



void buildTree(int *arr,pair<int,int> *tree,int start,int end,int treeNode){
   if(start==end){
        tree[treeNode]=make_pair(arr[start],INT_MIN);
       return;
   }

   int mid=(start+end)/2;
   buildTree(arr,tree,start,mid,2*treeNode);
   buildTree(arr,tree,mid+1,end,2*treeNode+1);

   pair<int,int> left=tree[2*treeNode];
   pair<int,int> right=tree[2*treeNode+1];

  tree[treeNode].first=max(left.first,right.first);
  tree[treeNode].second=min(max(left.first,right.second),max(left.second,right.first));

  return;   



   
}

pair<int,int> query(pair<int,int> *tree,int start,int end,int treeNode,int left,int right){
   
   if(start>right || end<left){
       pair<int,int> ans=make_pair(INT_MIN,INT_MIN);
       return ans;
   }

   if(start >=left && end<=right){
       return tree[treeNode];
   }

   int mid=(start+end)/2;

   pair<int ,int> l=query(tree,start,mid,2*treeNode,left,right);
   pair<int ,int> r=query(tree,mid+1,end,2*treeNode+1,left,right);

   pair<int ,int> ans;
   ans.first=max(l.first,r.first);
   ans.second=min(max(l.first,r.second),max(l.second,r.first));

   return ans;
}

void  updateTree(int *arr,pair<int,int> *tree,int start,int end,int treeNode,int idx,int value){
     
     if(start==end){
          arr[idx]=value;
          tree[treeNode]=make_pair(value,INT_MIN);
       return;   
     }

     int mid=(start+end)/2;
     if(idx>mid){
         updateTree(arr,tree,mid+1,end,2*treeNode+1,idx,value);
     }
     else{
         updateTree(arr,tree,start,mid,2*treeNode,idx,value);
     }

     pair<int,int> left=tree[2*treeNode];
     pair<int,int> right=tree[2*treeNode+1];

    tree[treeNode].first=max(left.first,right.first);
    tree[treeNode].second=min(max(left.first,right.second),max(left.second,right.first));
    return;


}
int main(){

    int n;
    cin>>n;

    int *arr=new int[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    pair<int,int> *tree=new pair<int,int>[3*n];
    buildTree(arr,tree,0,n-1,1);
    int q;
    cin>>q;

    while(q--){
        char queryType;
        
        cin>> queryType;
        if(queryType=='Q'){

          int l,r;
          cin>>l>>r;
          pair<int ,int> ans= query(tree,0,n-1,1,l-1,r-1);
          cout<<ans.first+ans.second<<endl;  
        }   
        else{
           int x,y;
           cin>>x>>y;
           updateTree(arr,tree,0,n-1,1,x-1,y);         
        }   
    }
    return 0;
}