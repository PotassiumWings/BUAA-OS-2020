#include<stdio.h>
int main()
{
	int i,n,flag=0,top=0,sta[10]={0};
	scanf("%d",&n);
	while(n){
		sta[top++]=n%10;
		n/=10;
	}
	for(i=0;i<top;i++){
		if(sta[i]!=sta[top-1-i])flag=1;
	}
	if(flag==0){
		printf("Y");
	}else{
		printf("N");
	}
	return 0;
}
