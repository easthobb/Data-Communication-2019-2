#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

#define BUFSIZE 60
using namespace std;
/*transmitter class - each input station & sendingbit*/
class transmitter
{
	int station[8] = {0};
	int temp[8] = {0};
	int tempBit = -1; //status 1,0
public:
	transmitter(){cout<<"generate transmitter!"<<endl;};
	void setStation(int *arr); // setting station's value 
	void inputBit(int bit) {this->tempBit = bit;}; // setting input bit;
	int* getSequence(); // return calculated transmitter's sequence!!
};
void transmitter::setStation(int *arr)
{
	for(int i=0;i<8;i++)
	{
		this->station[i] = arr[i];
	}
}

int* transmitter::getSequence(){

	//int this->temp[8]={0};
	for(int i=0;i<8; i++) // station copy
	{	
		this->temp[i]=this->station[i];
	}
	if(this->tempBit==0) // if this transmitter's input bit is 0 then, bosu sending
	{
		for(int i=0;i<8;i++)
		{
			this->temp[i] = this->temp[i] *(-1);
		}
		return this->temp;
	}
	else if(this->tempBit==1) // if this transmitter's input bit is 1 then, return stationvalue
	{
		for(int i=0;i<8;i++)
		{
			this->temp[i] = this->temp[i] *(1);
		}
		return this->temp;
	}
}
/*receiver class - each input station & from joiner sigma of seq*/

class receiver
{
	int station[8] = {0};
	int inputBit[8] = {0}; //input S from joiner
	int outputBit = 0; //finally returned
public:
	receiver(){cout<<"generate receiver!"<<endl;};
	void setStation(int *arr);
	void inputSumming(int *arr);
	int getOutputBit() {return this->outputBit;};
	void calculateOut();
};
void receiver::setStation(int *arr)
{	
	for(int i=0;i<8;i++)
	{
		this->station[i] = arr[i];
	}
}
void receiver::inputSumming(int *arr)
{	
	for(int i=0;i<8;i++)
	{
		this->inputBit[i]=arr[i];
	}
}
void receiver::calculateOut()
{
	int temp=0;
	for(int i=0; i<8 ; i++)
	{	//innerproduct
		temp=temp+(this->station[i])*(this->inputBit[i]);
	}
	if(temp/8==(-1)) // if temp is -1 then, change 0 because of unity.
	{
		this->outputBit=0;
	}
	else
	{
		this->outputBit=temp/8;
	}
}

int main()

{
	cout<<"<<<<<<<<<<<<<<<<<<<<<start CDMA>>>>>>>>>>>>>>>>>>>" << endl;
	cout<<"<<you have to input station number as orthogonal>>" << endl;
	cout<<"<<<<<<<<<<<<<please input +1 or -1>>>>>>>>>>>>>>>>" << endl;

	/* sets of transmitter and joiner pipes */
	int tfds00[2], tfds01[2], tfds10[2], tfds11[2], tfds20[2], tfds21[2], tfds30[2], tfds31[2];
	/* sets of receiver and joiner pipes */
	int rfds00[2], rfds01[2], rfds10[2], rfds11[2], rfds20[2], rfds21[2], rfds30[2], rfds31[2];

	int summing[8]={0}; // Joiners Sigma
	int buf[BUFSIZE];

	pid_t trans_pid[4]; // transmitter process arr 
	pid_t receive_pid[4]; //receiver process arr

   	int stationA[8]={0};
   	int stationB[8]={0}; 
   	int stationC[8]={0};
   	int stationD[8]={0};//station array 

   	int sendingBits[4]={0}; //bits to transmitter
   	int outputBits[4]={0}; // output bits if it is same as outputBits, then success CDMA 
   	pipe(tfds00),pipe(tfds01),pipe(tfds10),pipe(tfds11),pipe(tfds20),pipe(tfds21),pipe(tfds30),pipe(tfds31);
   	pipe(rfds00),pipe(rfds01),pipe(rfds10),pipe(rfds11),pipe(rfds20),pipe(rfds21),pipe(rfds30),pipe(rfds31);


	// from user input CDMA stations

		for(int j=0;j<8;j++)
		{	
			cout << "stationA" <<"[" << j <<"] : " ;
			cin >> stationA[j];
			cout << endl;
		}
		for(int j=0;j<8;j++)
		{	
			cout << "stationB" <<"[" << j <<"] : " ;
			cin >> stationB[j];
			cout << endl;
		}
		for(int j=0;j<8;j++)
		{	
			cout << "stationC" <<"[" << j <<"] : " ;
			cin >> stationC[j];
			cout << endl;
		}
		for(int j=0;j<8;j++)
		{	
			cout << "stationD" <<"[" << j <<"] : " ;
			cin >> stationD[j];
			cout << endl;
		}
	//inputting sending bit
		cout << " <<<<input bits that you want sends>>>>" << endl;
		cout << " <<<<<<< please input 1 or 0 >>>>>>>>>>" << endl;
		for(int i =0 ; i<4 ; i++)
			{	cout << "bit[" << i <<"] : ";
				cin >> sendingBits[i];}
		
	// transmiting process forking



		trans_pid[0]=fork(); //stationA
		if(trans_pid[0]==0)
		{	// it execute at jasic process
			cout << getpid() << "is forking!" << endl;
			read(tfds01[0],buf,BUFSIZE); // pipe reading for setting station
			transmitter A = transmitter(); // instance generating
			A.setStation(buf); // set.
			read(tfds01[0],buf,BUFSIZE); //pipe reading for setting inputbit
			A.inputBit(buf[0]);
			int * p = A.getSequence();
			write(tfds00[1],p,BUFSIZE);
			cout << "transmitterA is sending to joiner"  << " :  ";
			for(int i=0;i<8;i++)
			{
				cout << *(p + i) << " ";
			}
			cout << endl;
		;
			exit(getpid());
		}
		else{ //it execute at parents process
			write(tfds01[1],stationA,BUFSIZE);// piple writting for setting station
			sleep(1);
			int temp = sendingBits[0];
			write(tfds01[1],&temp,BUFSIZE); // pipe writting for setting inputbit
			read(tfds00[0],buf,BUFSIZE);
			for(int k = 0; k<8 ; k++)
			{
					summing[k]=summing[k]+buf[k]; 

			}
		
		}




		trans_pid[1]=fork(); //stationB
		if(trans_pid[1]==0)
		{	
			cout << getpid() << "is forking!" << endl;
			read(tfds11[0],buf,BUFSIZE);
			transmitter B = transmitter();
			B.setStation(buf);
			read(tfds11[0],buf,BUFSIZE);
			B.inputBit(buf[0]);
			int * p = B.getSequence();
			write(tfds10[1],p,BUFSIZE);
			cout << "transmitterB is sending to joiner"  << " :  ";
			for(int i=0;i<8;i++)
			{
				cout << *(p + i) << " ";
			}cout << endl;
			
			exit(getpid());
		}
		else{
			write(tfds11[1],stationB,BUFSIZE);
			sleep(1);
			int temp = sendingBits[1];
			write(tfds11[1],&temp,BUFSIZE);
			read(tfds10[0],buf,BUFSIZE);
			for(int k = 0; k<8 ; k++)
			{
					summing[k]=summing[k]+buf[k];

			}
		}





		trans_pid[2]=fork(); //stationC
		if(trans_pid[2]==0)
		{	
			cout << getpid() << "is forking!" << endl;
			read(tfds21[0],buf,BUFSIZE);
			transmitter C = transmitter();
			C.setStation(buf);
			read(tfds21[0],buf,BUFSIZE);
			C.inputBit(buf[0]);
			int * p = C.getSequence();
			write(tfds20[1],p,BUFSIZE);
			cout << "transmitterC is sending to joiner"  << " :  ";
			for(int i=0;i<8;i++)
			{
				cout << *(p + i) << " ";
			}cout << endl;
			
			exit(getpid());
		}
		else{
			write(tfds21[1],stationC,BUFSIZE);
			sleep(1);
			int temp = sendingBits[2];
			write(tfds21[1],&temp,BUFSIZE);
			read(tfds20[0],buf,BUFSIZE);
			for(int k = 0; k<8 ; k++)
			{
					summing[k]=summing[k]+buf[k];

			}
		}





		trans_pid[3]=fork(); //stationD
		if(trans_pid[3]==0)
		{	
			cout << getpid() << "is forking!" << endl;
			read(tfds31[0],buf,BUFSIZE);
			transmitter D = transmitter();
			D.setStation(buf);
			read(tfds31[0],buf,BUFSIZE);
			D.inputBit(buf[0]);
			int * p = D.getSequence();
			cout << "transmitterD is sending to joiner"  << " :  ";
			write(tfds30[1],p,BUFSIZE);
			for(int i=0;i<8;i++)
			{
				cout << *(p + i) << " ";
			}cout << endl;
		
			exit(getpid());
		}
		else{
			write(tfds31[1],stationD,BUFSIZE);
			sleep(1);
			int temp = sendingBits[3];
			write(tfds31[1],&temp,BUFSIZE);
			read(tfds30[0],buf,BUFSIZE);
			for(int k = 0; k<8 ; k++)
			{
					summing[k]=summing[k]+buf[k];

			}
		}




		//transprocess can't access here
		if(trans_pid[0]!=0&&trans_pid[1]!=0&&trans_pid[2]!=0&&trans_pid[3]!=0)
		{

			//summing all signal from transmitter;
			sleep(2);
			cout << "S = (";
			for(int i = 0; i<8 ; i++)
			{
				cout<<summing[i]<<", ";
			}
			cout<< ")";
			sleep(2);
		}



		/*receiver*/
		
		receive_pid[0]=fork(); //stationA
		cout << getpid() << "is forking!" << endl;
		if(receive_pid[0]==0)
		{	//it is execute at child process
			cout << getpid() << "is forking!" << endl;
			read(rfds01[0],buf,BUFSIZE); //reading for set station
			receiver A = receiver(); // generating instance
			A.setStation(buf);
			A.inputSumming(summing);
			A.calculateOut();
			int temp = A.getOutputBit(); //output bit return
			write(rfds00[1],&temp,sizeof(&temp));
			exit(getpid());
		}
		else{ // it is execute at parent process
			write(rfds01[1],stationA,BUFSIZE);
			sleep(2);
			read(rfds00[0],buf,BUFSIZE);
			cout << "ReceiverA's received bit: " <<buf[0] <<endl;
			outputBits[0]=buf[0];
		
		}


		receive_pid[1]=fork(); //stationB
		cout << getpid() << "is forking!" << endl;
		if(receive_pid[1]==0)
		{	
			cout << getpid() << "is forking!" << endl;
			read(rfds11[0],buf,BUFSIZE);
			receiver B = receiver();
			B.setStation(buf);
			B.inputSumming(summing);
			B.calculateOut();
			int temp = B.getOutputBit();
			write(rfds10[1],&temp,sizeof(&temp));
			exit(getpid());
		}
		else{
			write(rfds11[1],stationB,BUFSIZE);
			sleep(2);
			read(rfds10[0],buf,BUFSIZE);
			cout << "ReceiverB's received bit: " <<buf[0] <<endl;
			outputBits[1]=buf[0];
		
		}


		
		
		receive_pid[2]=fork(); //stationC
		cout << getpid() << "is forking!" << endl;
		if(receive_pid[2]==0)
		{	
			cout << getpid() << "is forking!" << endl;
			read(rfds21[0],buf,BUFSIZE);
			receiver C = receiver();
			C.setStation(buf);
			C.inputSumming(summing);
			C.calculateOut();
			int temp = C.getOutputBit();
			write(rfds20[1],&temp,sizeof(&temp));
			exit(getpid());
		}
		else{
			write(rfds21[1],stationC,BUFSIZE);
			sleep(2);
			read(rfds20[0],buf,BUFSIZE);
			cout << "ReceiverC's received bit: " <<buf[0] <<endl;
			outputBits[2]=buf[0];
		
		}

		receive_pid[3]=fork(); //stationD
		cout << getpid() << "is forking!" << endl;
		if(receive_pid[3]==0)
		{	
			cout << getpid() << "is forking!" << endl;
			read(rfds31[0],buf,BUFSIZE);
			receiver D = receiver();
			D.setStation(buf);
			D.inputSumming(summing);
			D.calculateOut();
			int temp = D.getOutputBit();
			write(rfds30[1],&temp,sizeof(&temp));
			exit(getpid());
		}
		else{
			write(rfds31[1],stationD,BUFSIZE);
			sleep(2);
			read(rfds30[0],buf,BUFSIZE);
			cout << "ReceiverD's received bit: " <<buf[0] <<endl;
			outputBits[3]=buf[0];
		
		}

		if(receive_pid[0]!=0&&receive_pid[1]!=0&&receive_pid[2]!=0&&receive_pid[3]!=0)
		{
			//if(receive_pid[0]!=0&&receive_pid[1]!=0&&receive_pid[2]!=0&&receive_pid[3]!=0)
			//summing all signal from transmitter;
			sleep(2);
			cout << "you send this bits = (";
			for(int i = 0; i<4 ; i++)
			{
				cout<<outputBits[i]<<", ";
			}
			cout<< ")";
		}


	/*
	if( pid == 0 )

	{

	write(fds1[1], str1, sizeof(str1)); // fds1 is input of parent

	read(fds2[0], buf, BUFSIZE); //output of sons process

	printf("child proc output : %d\n", buf[0]);

	}

	else

	{

	read(fds1[0], buf, BUFSIZE); // fds1[0]

	cout << "this process's ID is pid" << pid ;

	printf("parent proc output: %d\n", buf[0]);

	write(fds2[1], str2, sizeof(str2));

	sleep(3);

	}
	*/
   

	return 0;

}