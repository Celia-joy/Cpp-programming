#include <iostream>
using namespace std;
int main(){
	for(int i=0; i<1000; i++){
	    for(int j=0; j<1000;j++){
		    if((i%10==0)&&(j%10==0)){
			    cout<< "i="<<i<<"j="<<j<<" and i*j= "<<i*j<<endl;
		    }
	    }
    }
    return 0;	
}
