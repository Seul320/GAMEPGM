## CARD.cpp
52장의 카드 덱을 생성하고 출력하는 C++ 언어 프로그램입니다.

# 주요 함수
- make_card: 카드 덱을 초기화하는 함수입니다.
- display_card: 생성된 카드를 출력하는 함수입니다.

# 실행 방법
1. 코드를 컴파일한 후 실행합니다.
2. 52장의 카드가 모양(♠, ◆, ♥, ♣)과 숫자(A, 2-10, J, Q, K)로 출력됩니다.

## card2.cpp

- CARD.cpp + 셔플기능 추가

void shuffle_card (trump m_card [])
{
	int i, rnd;
	trump temp;
	srand(time (NULL)) ; //난수의 초기화
	for(i=0;i<52;i++)
	{
		rnd=rand () %52;
		temp=m_card [rnd];
		m_card [rnd]=m_card [i] ;
		m_card [i]=temp;
	}
}


