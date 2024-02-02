#include <iostream>
#include <queue>
using namespace std;

int main(){

    //큐 선언
    queue<int> q;
    
    //큐에 1~5삽입
     for(int i = 1; i<=5; i++){
        q.push(i);
    }

    //큐 사이즈 리턴
    cout << q.size() << endl;

    //맨 앞 뒤 원소 확인
    int front = q.front();
    int rear = q.back();
    cout << front << " " << rear << endl;

    //맨 앞 원소 삭제(1)
	q.pop();
	
	//큐의 전체원소 출력하기
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}

    return 0;
}