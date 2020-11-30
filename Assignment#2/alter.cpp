#include<iostream>
#include<string>


using namespace std;

/* generator의 표준 출력의 비트를 임의로 변경시키기 위해서 사용하는 함수*/
int main(int argc, char *argv[]){ // 사용자로부터 실행 인자로 정수를 입력 받음

	int changeIndex = atoi(argv[1]); // argv[1]로 전해진 char* 형태의 변수를 atoi()함수를 통해 정수로 변환합니다.

	string FRAME;
	string GENERATOR;
	
	/*표준입력*/	
	getline(cin,FRAME);
	getline(cin,GENERATOR);

	/*사용자가 FRAME의 size를 over 했을 경우 alter 하지 않고 종료*/ 
	if(changeIndex>FRAME.length())
		return 0;
	else{
		/*사용자가 입력한 정수에 해당하는 index의 값을 반전시킵니다. 0->1 , 1->0*/
		if(FRAME[changeIndex]=='1')
			FRAME[changeIndex]='0';
		else
			FRAME[changeIndex]='1';
	}
	
	/*표준출력*/
	cout<<FRAME<<endl;
	cout<<GENERATOR<<endl;

	return 0;
}
