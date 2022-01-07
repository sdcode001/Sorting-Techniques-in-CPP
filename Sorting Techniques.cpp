#include<bits/stdc++.h>
using namespace std;
void swap(int& a,int& b){
  int temp=a;
  a=b;
  b=temp;
}
//bubbel sort generally sort takes O(n^2) time but when list is already sorted then it takes min time O(n).here we use flag to detect if it is already sorted or not,it it is then we do only one iteration and break loop. bubble sort is stable sort and also adaptive sort.
int Bubbel_Sort(int arr[],int n){
  for(int i=0;i<n;i++){
     int flag=0;
    for(int j=0;j<n-i;j++){
      if(arr[j]>arr[j+1]){swap(arr[j],arr[j+1]); flag=1;}
    }
    if(flag==0){break;}
  }
}

//if list is already sorted then selections sort takes min time(O(n)) so it is adaptive and selection sort is also stable.
void Insertion_Sort(int arr[],int n){
    //assuming arr[0] already in the sorted list so we start from index 1.
    int j,temp;
    for(int i=1;i<n;i++){
      j=i; temp=arr[i];
      while(j>0 && temp<arr[j-1]){
        arr[j]=arr[j-1];
        j--;
      }
      arr[j]=temp;
    }
 }

 void Selection_Sort(int arr[], int n){
    int j,k;
    for(int i=0;i<n;i++){
      j=i; k=i;
      while(j<n){
        j++;
        if(arr[j]<arr[k]){k=j;}
      }
      swap(arr[i],arr[k]);
    }
 }
 //---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Quick Sort:
int partition(int arr[],int l,int h){
  int pivot=arr[l];
  int i=l,j=h;
  do{
    do{i++;}while(arr[i]<=pivot);
    do{j--;}while(arr[j]>pivot);
    if(i<j){swap(arr[i],arr[j]);}
  }while(j>i);
  swap(arr[l],arr[j]);
  return j;
}

void Quick_Sort(int arr[],int l,int h){        //initially l=0 and h=size of arr.
   int partition_point;
   if(l<h){
     partition_point=partition(arr,l,h);
     Quick_Sort(arr,l,partition_point);
     Quick_Sort(arr,partition_point+1,h);
   }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// count sort is useful when max element is not too large.
void Count_Sort(int arr[],int n){
  int max=arr[0];
  for(int i=1;i<n;i++){
    if(arr[i]>max){max=arr[i];}
  }
  int aux[max+1]={0};
  for(int i=0;i<n;i++){
    aux[arr[i]]++;
  }
  int j=0;
  for(int i=0;i<max+1;i++){
    if(aux[i]!=0){
      while(aux[i]!=0){
        arr[j]=i;
        aux[i]--;
        j++;}}
    }
 }


int* Merge(int a[],int n,int b[],int m){    //it takes two sorted list a of size n and b of size m and merge them into a single sorted list.
  int* res=new int[m+n];
  int i=0,j=0,k=0;
  while(i!=n||j!=m){
    if(a[i]<=b[j]){res[k]=a[i];k++;i++;}
    else{res[k]=b[j];k++;j++;}
  }
  while(i<n){res[k]=a[i];k++;i++;}
  while(j<m){res[k]=b[j];k++;j++;}
  return res;
}


void Iterative_MergeSort(int arr[],int n){      //this is a two way sort.so list size must be 2^n(1,2,3,......n)
  int windowSize=2;
  while(windowSize<=n){
  int l=0,h=windowSize-1;
   while(h<n){
     int mid=(l+h)/2;
     int i=l,j=mid+1;
     vector<int> v;
     while(i<=mid&&j<=h){
       if(arr[i]<=arr[j]){v.push_back(arr[i]);i++;}
       else{v.push_back(arr[j]);j++;}
     }
     while(i!=mid+1){v.push_back(arr[i]);i++;}
     while(j!=h+1){v.push_back(arr[j]);j++;}
     int q=0;
     for(int p=l;p<=h;p++){arr[p]=v[q];q++;}
     l+=windowSize;
     h+=windowSize;
   }
   windowSize*=2;
  }
}


void Recursive_MergeSort(int arr[],int l,int h){   //this is a two way sort.so list size must be 2^n(1,2,3,......n)
      if(l<h){                                      //initially l=0 and h=list size-1
          int mid=(l+h)/2;
          Recursive_MergeSort(arr,l,mid);
          Recursive_MergeSort(arr,mid+1,h);
          //applying merging.
          int i=l,j=mid+1;
          vector<int> v;
          while(i<=mid&&j<=h){
            if(arr[i]<=arr[j]){v.push_back(arr[i]);i++;}
            else{v.push_back(arr[j]);j++;}
          }
          while(i!=mid+1){v.push_back(arr[i]);i++;}
          while(j!=h+1){v.push_back(arr[j]);j++;}
          int q=0;
          for(int p=l;p<=h;p++){arr[p]=v[q];q++;}
      }
  }
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//it is a index based sort and also bucket sort.so it nead bucket/node to store elements.
class Node{
public:
  int val;
  Node* ptr;
 };

  void Radix_Sort(int arr[],int n){
    int max=arr[0];
    for(int i=1;i<n;i++){
      if(arr[i]>max){max=arr[i];}
    }

    Node* aux[10]; //list of buckets
    for(int i=0;i<10;i++){aux[i]=NULL;}  //making all buckets empty/null.
    int div=1;
    while(max%10!=0){
     //inserting element from arr to aux.
     int index;
     for(int i=0;i<n;i++){
       index=(arr[i]/div)%10;
        Node* p;
        if(aux[index]==NULL){
          aux[index]=new Node;
          aux[index]->val=arr[i];
          aux[index]->ptr=NULL;
        }
        else{
          p=aux[index];
          while(p->ptr!=NULL){p=p->ptr;}
            p->ptr=new Node;
            Node* q=p->ptr;
            q->val=arr[i];
            q->ptr=NULL;}
        }

   //again putting elements from aux to arr.
     int h=0;
     for(int k=0;k<10;k++){
       if(aux[k]!=NULL){
         while(aux[k]!=NULL){
           Node* m=aux[k];
           arr[h]=m->val;
           h++;
           aux[k]=m->ptr;
           m->ptr=NULL;
           delete m;}
         }
      }
     div*=10;
     max/=10;
    }
  }
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Display(int arr[],int n){
  for(int i=0;i<n;i++){cout<<arr[i]<<" ";}
}


int main(){
//int list1[5]={3,5,7,9,11};
//int list2[8]={2,4,7,8,10,12,14,16};
int list[10]={6,8,3,10,15,6,9,12,6,3};
//Selection_Sort(list,7);
//Quick_Sort(list,0,9);
//Quick_Sort(list,0,9);
//Count_Sort(list,11);
//int* list3=Merge(list1,5,list2,8);
//Iterative_MergeSort(list,8);
//Recursive_MergeSort(list,0,8-1);
Radix_Sort(list,10);
Display(list,10);
//delete[]list3;
  return 0;
}
