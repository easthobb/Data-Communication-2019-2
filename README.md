# Data-Communication-2019-2
19년도 2학기 동국대학교 컴퓨터공학과 데이터통신 어사인먼트입니다.
19년도에 수행한 코드를 학습 및 후배들의 과제 수행에 도움이 되라고 올립니다.

## Assignment#1 (CDMA)
- ### 문제정의 
>write a program to implement CDMA. assume that the length of a chip sequences is eight process and the number of stations transmitting is four. your program consists of three sets of process, four transmitter process(t0,t1,t2 and t3), one joiner process, and four receiver process (r0,r1,r2 and r3). The main program, which also acts as the joiner process, first reads four chip sequences ( bipolar notation ) from the standard input and a sequence of 4 bits ( 1bit per transmitter process to be transmitted), and forks off four pairs of transmitter and receiver process,. each pair of transmitter/receiver processes (t0,r0; t1,r1; t2,r2; t3,r3) is assigned one chip sequence and each transmitter process is assigned 1 bit (first bit to t0, second bit to t1 and so on). Next each transmitter computes the signal to be transmitted (a sequence of 8bits) and sends it to the joiner process. After receiving signals from all four transmitter processes, the joiner process combines the signals and sends the combined signal to four receiver processes. Each receiver process then computes the bit it has received and prints it to standard output. use pipes for communication between processes.

- ### 어싸인 수행에 필요한 것
    - Code Division Multiple Access에 대한 이해
    - LINUX 시스템에서 지원하는 fork() 에 대한 프로세스-스레드 개념이해
    - 프로세스간 통신에 이용되는 Pipe에 대한 이해
- ### 채점기준 
    - 코드의 정상작동
    - 코드의 논리적 구조와 설계
    - fork, pipe 등의 사용여부
    - 코드의 가독성 및 주석의 상세함을 통한 유지보수성
- ### 실행 결과
![1](https://user-images.githubusercontent.com/57410044/100576266-273a4680-3321-11eb-8177-456ba3b54f1f.PNG)
![2](https://user-images.githubusercontent.com/57410044/100576492-9a43bd00-3321-11eb-9ed2-bff981d80a95.PNG)
![3](https://user-images.githubusercontent.com/57410044/100576502-a0399e00-3321-11eb-8652-af8e75fe4121.PNG)
![4](https://user-images.githubusercontent.com/57410044/100576508-a465bb80-3321-11eb-8146-05f6c0801e56.PNG)
![5](https://user-images.githubusercontent.com/57410044/100576517-a9c30600-3321-11eb-8f94-5d05d10fb345.PNG)

## Assignment#2 (CRC)


- ### 문제정의
>36. the goal of this lab exercise is to implement an error-detection mechanism using the standard CRC algorithm described in the text. Write two programs, generator and verifier. The generator program reads from standard input a line of ASCII text containing an n-bit message consisting of a string of 0s and 1s. The second line is the k-bit polynominal, also in ASCII. It outputs to standard a line of ASCII text with n+k 0s and 1s representing the message to be transmitted. Then, it outputs the polynominal, just as it read it in. the verifier program reads in the outputs a message indicating whether it is correct or not, finally write a program, alter, that inverts 1bit on the first line depending on its argument(the bit number counting the leftmost bit as 1) but copies the rest of the two lines correctly.
By typing
	Generator <file | verifier
You should see that the message is correct, but by typing
	Generator <file| alter arg | verifier
You should get the error message.

- ### 어싸인 수행에 필요한 것
    - CRC 개념에 대한 이해, 체크섬에 대한 이해
    - 리눅스 환경에 대한 이해 명령어 - input - output 파이프라이닝

- ### 채점기준
    - 코드의 예상-결과 값 일치
    - 코드의 논리적 구조와 설계
    - 코드의 가독성 및 주석의 상세함을 통한 유지보수성
- ### 실행결과
>비정상 실행 
![6](https://user-images.githubusercontent.com/57410044/100576538-b3e50480-3321-11eb-8190-c6d625f04689.PNG)

>정상실행
![7](https://user-images.githubusercontent.com/57410044/100576563-bba4a900-3321-11eb-88d7-7db6a101da46.PNG)

>file.png
![file](https://user-images.githubusercontent.com/57410044/100576591-c7906b00-3321-11eb-936c-ebc08ea294cb.PNG)
