========================================================================
BLACK JACK
========================================================================

딜러 1명
플레이어 1명

딜러/플레이어 각각 2장씩 카드를 받음
딜러 카드 1장 공개
HIT : 카드를 한장 더 받는다
STAY : 카드를 더 받지 않는다
BURST : 카드 숫자의 합이 21을 초과. (=패배)
BLACKJACK : A + 10의 조합으로 21 완성. 배팅액의 150% 획득.

플레이어 BURST 의 경우 무조건 플레이어의 패배
딜러는 17이상이 될 때까지 HIT (17 이상이 되면 STAY)
딜러 STAY 시 카드 합을 계산하여 21에 가까운 쪽이 승리
딜러 BURST 시 플레이어 승리

카드 구조체
- 도형/숫자
- 2 ~ 10, A, J, Q, K
- Spade, Dia, Heart, Club
- enum, switch 활용
- char* 혹은 string 사용하여 도형정보 기록
- 전체 덱 셔플
- 셔플된 전체 덱 화면에 출력 ( 모양 + 숫자 )

------------------------필수 ~170912 -----------------------------

시간 여유 있으면 플레이까지

Write Date : 170911

//	VECTOR EXAMPLE
/*
vector<int> vecInt;
vector<int>::iterator iter;

vecInt.push_back(1);
vecInt.push_back(3);
vecInt.push_back(5);
cout << vecInt[0] << endl;

cout << vecInt.size() << endl;
vecInt.pop_back();	//	last value pop out
cout << vecInt.size() << endl;

cout << *(vecInt.begin() + 1) << endl;

for (iter = vecInt.begin(); iter != vecInt.end(); iter++)
{
	cout << *iter << endl;
}
*/