#include<iostream>
#include<fstream>
#include<string>


using namespace std;

/* MOD-2 ������ �����ϴ� �Լ�, ù��° ���ڷ� �޴� tempFrame�� �� ��° ���ڷ� �޴� GENERATOR�� mod-2 ������ ����*/  
string mod2Op(string tempFrame, string GENERATOR) {


	for (int i = 0; tempFrame.length() >= GENERATOR.length(); i++)//tempFrame �� ���̰� generator���� ª���� ������ ���� ����
	{
		if (tempFrame[0] == '1')
		{ //���ڿ��� ó���� 1�� ��쿡 xor ���� ����
			for (int j = 0; j < GENERATOR.length(); j++)
			{ // GENERATOR�� ���̸�ŭ XOR ������ �����մϴ�.
				if ((tempFrame[j] ^ GENERATOR[j]) == 0)
					tempFrame.replace(j, 1, "0"); // gen�� XOR ���� ��� 0�ϰ�� �ش� ���ڿ��� �ε����� 0���� ��ü
				else if ((tempFrame[j] ^ GENERATOR[j]) == 1)
					tempFrame.replace(j, 1, "1"); // GEN�� XOR ���� ��� 1�� ��� �ش� ���ڿ��� �ε����� 1�� ��ü 
			}
		}
		while (tempFrame[0] == '0') { // ���ڿ��� ó���� 1�� �ɶ����� ���ڿ� �ֻ����� 0�� ������. �� ���� ���� ���ڿ��� ���̰� ª����. 
				tempFrame.erase(0, 1);
			}
	}
	return tempFrame; // mod-2������ ���� ������ ���ڿ� ��ȯ(mod-2 ������remainder)

}

int main() {

	string FRAME; // ���� ��� FRAME ����ڰ� ������ ���� �Է�
	string GENERATOR; // ���� ��� GENERATOR  ����ڰ� ������ ���� �Է�, CRC�� �� G(X)�� ���� ������ �̹� ������ ����.
	string remainder; // FRAME�� GEN ���� mod-2���� �� �������� ��ȯ�Ǵ� ����

	/* ǥ�� �Է����� FRAME�� GEN�� �Է� �޽��ϴ�.*/ 
	getline(cin,FRAME);
	getline(cin,GENERATOR);
	string tempFrame = FRAME;

	/* CRC ���ǿ� ���� GEN�� �ְ������� �� ��ŭ 0�� FRAME�� ������.*/
	for (int i = 0; i < (GENERATOR.length()-1); i++) {

		tempFrame = tempFrame + "0";
	}
	/*  tempFrame�� GEN�� mod-2���� ���� �� ��ȯ ���� remainder�� ����*/
	remainder=mod2Op(tempFrame, GENERATOR);
	
	/* minus remainder */
	for (int i = 0; remainder.length() < GENERATOR.length() - 1; i++) {
		
		remainder = "0" + remainder;
	}
	/* remainder appending to FRAME*/
	FRAME = FRAME + remainder;
	
	/* ������ FRAME �� GEN ǥ�� ���*/
	cout << FRAME << endl;
	cout << GENERATOR << endl;

	return 0;
}
