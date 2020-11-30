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
    - ![screensh](./Assignment#1/1.png)

