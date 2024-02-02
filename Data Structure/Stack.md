
# 스택

제한적으로 접근할 수 있는 나열 구조. 컴퓨터 과학 역사에서 나타나게 된 것은 1946년, 엘런 튜링에 의해서다. "bury", "unbury"라는 용어를 통해 two-level stack을 Subroutine에서 되돌아오는 개념으로 컴퓨터에서 최초로 사용했다고 한다. 
![](https://upload.wikimedia.org/wikipedia/commons/thumb/2/29/Data_stack.svg/300px-Data_stack.svg.png)


목록의 끝에서만 접근이 일어나고, Pushdown List라고 함. (여기서 pushdown automata 개념이 생김.)
LIFO(Last In First Out, 후입선출)의 특징을 갖고 있음.

###### Pushdown Automata
![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FYEmAl%2FbtqNwvZ7UO7%2FBB8yKigNKlUgMX6mmueHmK%2Fimg.png)

input을 $까지 읽을 때까지 Control Unit에 있는 Automata가 Stack 공간을 활용하여 State를 변환하는 과정.

아키텍처에서의 스택도 비슷한 형태로 이루어져 있음.
![](https://upload.wikimedia.org/wikipedia/commons/thumb/a/ac/ProgramCallStack2_en.svg/350px-ProgramCallStack2_en.svg.png)
함수가 호출되면, Stack에 메모리가 할당된다. 리턴이 있다면 리턴받을 메모리를 먼저 push한 다음 인자가 있다면 인자를 전달한 다음 함수 내부에 사용될 메모리 공간을 순서대로 할당한다. 가변 공간은 Heap을 사용한다.

# 언제 사용할까?

1. 수식 계산 및 구문 분석
	* 수식을 계산할 때 [역폴란드 표기법, 후위 표기법](https://ko.wikipedia.org/wiki/%EC%97%AD%ED%8F%B4%EB%9E%80%EB%93%9C_%ED%91%9C%EA%B8%B0%EB%B2%95) 으로 바꿀 때, 계산할 때 모두 스택을 사용.
	* 구문 분석을 할 때 스택을 활용하는 LR 파서 기반 컴파일러들은 스택을 활용하여 구문을 분석.
2. 백트래킹 (DFS)
	* 상태 트리 기법을 사용하는 백트래킹은 트리 순회 방법에서 DFS를 보통 사용한다. DFS는 함수 호출의 연속이기 때문에 stack을 사용한다고 봐도 된다.
3. 그라함 스캔 등 기타 여러 효율적인 알고리즘
	* 컨벡스 헐 문제를 풀 때 보통 사용하는 그라함 스캔 알고리즘에는 스택이 사용된다.
4. 보안 공격
	* 스택이 컴퓨터의 첫 단계라면, 버퍼 오버플로우 공격은 해킹의 첫 단계라고 볼 수 있다.
	* 스택의 취약점을 활용한 공격.

# 구현 방법

배열이나 리스트를 활용하여 구현할 수 있다.
특별한 경우가 아니라면 배열을 활용하여 구현한다.

# 필수 연산

## push(원소)

스택에 원소를 넣는 것을 의미한다.

## pop()

스택에서 값을 빼는 것을 의미한다.

# 기타 연산

## top(), peak()

스택의 가장 위 값을 의미한다. 해당 원소를 리턴하거나 에러를 도출할 수도 있다.

## empty(), size()

스택에 있는 원소의 개수와 연관이 있다. 에러를 도출하지 않는다.



# 대표 문제 : 괄호
https://www.acmicpc.net/problem/9012

```c++
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        stack<int> st;
        string str;
        bool fail=false;
        cin >> str;
        for(int i=0; i<str.size(); ++i){
            if(str[i] == '(') st.push(1);
            else {
                if(st.empty()) {
                    fail = true;
                    break;
                }
                st.pop();
            }
        }
        if(!st.empty()) fail=true;
        if(fail) cout << "NO" << '\n';
        else cout << "YES" << '\n';
        
    }
}
```


###### Reference
https://ko.wikipedia.org/wiki/%EC%8A%A4%ED%83%9D
