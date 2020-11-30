#include<iostream>
#include<fstream>
#include<string>


using namespace std;

/* MOD-2 연산을 수행하는 함수, 첫번째 인자로 받는 tempFrame을 두 번째 인자로 받는 GENERATOR가 mod-2 연산을 수행*/  
string mod2Op(string tempFrame, string GENERATOR) {


	for (int i = 0; tempFrame.length() >= GENERATOR.length(); i++)//tempFrame 의 길이가 generator보다 짧아질 때까지 연산 수행
	{
		if (tempFrame[0] == '1')
		{ //문자열의 처음이 1일 경우에 xor 연산 수행
			for (int j = 0; j < GENERATOR.length(); j++)
			{ // GENERATOR의 길이만큼 XOR 연산을 수행합니다.
				if ((tempFrame[j] ^ GENERATOR[j]) == 0)
					tempFrame.replace(j, 1, "0"); // gen과 XOR 연산 결과 0일경우 해당 문자열의 인덱스를 0으로 교체
				else if ((tempFrame[j] ^ GENERATOR[j]) == 1)
					tempFrame.replace(j, 1, "1"); // GEN과 XOR 연산 결과 1일 경우 해당 문자열의 인덱스를 1로 교체 
			}
		}
		while (tempFrame[0] == '0') { // 문자열의 처음이 1이 될때까지 문자열 최상위의 0을 제거함. 이 연산 이후 문자열의 길이가 짧아짐. 
				tempFrame.erase(0, 1);
			}
	}
	return tempFrame; // mod-2연산을 통해 가공된 문자열 반환(mod-2 연산의remainder)

}

int main() {

	string FRAME; // 전송 대상 FRAME 사용자가 파일을 통해 입력
	string GENERATOR; // 전송 대상 GENERATOR  사용자가 파일을 통해 입력, CRC는 이 G(X)에 대해 정보를 이미 가지고 있음.
	string remainder; // FRAME을 GEN 으로 mod-2연산 후 나머지가 반환되는 변수

	/* 표준 입력으로 FRAME과 GEN을 입력 받습니다.*/ 
	getline(cin,FRAME);
	getline(cin,GENERATOR);
	string tempFrame = FRAME;

	/* CRC 정의에 따라 GEN의 최고차항의 수 만큼 0을 FRAME에 더해줌.*/
	for (int i = 0; i < (GENERATOR.length()-1); i++) {

		tempFrame = tempFrame + "0";
	}
	/*  tempFrame과 GEN의 mod-2연산 수행 후 반환 값을 remainder에 저장*/
	remainder=mod2Op(tempFrame, GENERATOR);
	
	/* minus remainder */
	for (int i = 0; remainder.length() < GENERATOR.length() - 1; i++) {
		
		remainder = "0" + remainder;
	}
	/* remainder appending to FRAME*/
	FRAME = FRAME + remainder;
	
	/* 가공된 FRAME 과 GEN 표준 출력*/
	cout << FRAME << endl;
	cout << GENERATOR << endl;

	return 0;
}
