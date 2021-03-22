FROM ubuntu
COPY p1.cpp p2.cpp ./
RUN apt-get update && apt-get install gcc gcc-multilib g++ -y
RUN g++ p1.cpp -o p1 && g++ p2.cpp -o p2 -lpthread
CMD ./p2 ex n
