#include<iostream>
#include<fstream>
#include<string>


using namespace std;
/* MOD-2 연산을 수행하는 함수, 첫번째 인자로 받는 tempFrame을 두 번째 인자로 받는 GENERATOR가 mod-2 연산을 수행*/  
string mod2Op(string tempFrame, string GENERATOR) {


	for (int i = 0; tempFrame.length() >= GENERATOR.length(); i++)//tempFrame 의 길이가 generator보다 짧아질 때까지 연산 수행
	{
		if (tempFrame[0] == '1')
		{//문자열의 처음이 1일 경우에 xor 연산 수행
			for (int j = 0; j < GENERATOR.length(); j++)
			{
				if ((tempFrame[j] ^ GENERATOR[j]) == 0)
					tempFrame.replace(j, 1, "0"); // gen과 XOR 연산 결과 0일경우 해당 문자열의 인덱스를 0으로 교체
				else if ((tempFrame[j] ^ GENERATOR[j]) == 1)
					tempFrame.replace(j, 1, "1");// GEN과 XOR 연산 결과 1일 경우 해당 문자열의 인덱스를 1로 교체 
			}
		
		}
		while (tempFrame[0] == '0') {// 문자열의 처음이 1이 될때까지 문자열 최상위의 0을 제거함. 이 연산 이후 문자열의 길이가 짧아짐.
				tempFrame.erase(0, 1);
			}
	}
	return tempFrame; // mod-2연산을 통해 가공된 문자열 반환(mod-2 연산의remainder)

}

int main(){
	/* 변수 선언 */
	string FRAME; // 전송된 FRAME 표준 입력을 통해 verifier로 넘어옴.
	string GENERATOR; // 전송된 GEN, 표준 입력을 통해 verifier로 넘어옴.  
	string remainder; // FRAME을 GEN으로 MOD-2 연산결과 저장 변수
	
	/*line 단위 표준 입력*/
	getline(cin,FRAME);
	getline(cin,GENERATOR);

	/*remainder string에 mod2 결과 저장*/
	remainder=mod2Op(FRAME,GENERATOR);
	
	/*remaider의 상태에 따라 error 여부 결정-remainder 발생시 error message 출력*/
	if(remainder==""){
		cout << "received : " << FRAME << endl;
		cout << "GENERATOR : " << GENERATOR << endl;
		cout << "remainder : " << remainder << endl;
		cout << "no error detected!" << endl;
	}
	else {
		cout << "received : " << FRAME << endl;
		cout << "GENERATOR : " << GENERATOR << endl;
		cout << "remainder : " << remainder << endl;
		cout << "error detected!" << endl;
	}

	return 0;

}
