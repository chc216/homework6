/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {	//노드의 자료구조를 정의합니다. 필드엔 데이터값과 다음 노드를 가리킬 포인터가 있습니다.
	int key;
	struct Node* link;
} listNode;

typedef struct Head {	//노드를 가리킬 헤드 포인터를 구조체로써 정의합니다.
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{			//기능을 실행할 커맨드를 입력받고 커맨드에 따라 함수를 달리 호출합니다.
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {	
		case 'z': case 'Z':		//커맨드 z는 연결리스트를 초기화하는 커맨드로써 리스트를 가리키는 headnode를 인수로 initialize함수를 호출하여 headnode에 해당 주소값을 대입합니다.
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':	//커맨드 p는 연결리스트를 출력하는 커맨드로써 리스트를 가리키는 headnode를 인수로 printlist함수를 호출합니다.
			printList(headnode);
			break;
		case 'i': case 'I':	//커맨드 i는 순서에 따라 알맞은 위치에 노드를 삽입합니다. key값을 사용자로부터 입력을 받은 후 insertnode에 인수로 전달합니다.
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':	//커맨드 
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {	
	//매개변수를 사전에 미리 정의한 구조체 headnode *자료형으로 선언하여 main함수의 headnode가 갖고 있는 주소값을 인수로 넘깁니다.
	//참고로 자료형을 headNode *로 선언한 이유는 포인터의 값을 변경하기 위해서이다.

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)	
		freeList(h);	

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;	//headnode가 가리키는 리스트의 주소 값을 포인터 p에 대입

	listNode* prev = NULL;	//포인터 p가 가리키는 노드의 직전 노드를 가리킬 포인터 prev 선언
	while(p != NULL) {		//포인터 P가 가리키는 노드가 NULL값이 아닐 동안 즉, 리스트의 마지막까지 포인터 p의 값을 prev에 대입하고, 포인터 p가 가리키는 노드의 link 값을 p에 대입한다. 그리고 Prev가 가리키는 노드의 동적 할당을 free함수를 이용하여 해제한다.
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);	//리스트를 가리킨 헤드포인터도 동적할당을 받았으므로 동적할당 해제 해준다.
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	
	node->key = key;
	node->link = NULL;	//새로운 node를 동적할당 받고 해당 node의 필드에 key,link값을 각각 대입한다.

	if (h->first == NULL)	//리스트가 없다면 해드포인터의 first가 가리키는 값을 node의 주소로 대입한다.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;	
	listNode* trail = h->first;	//리스트의 노드를 가리킬 포인터 n, trail을 각각 선언한다.

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {	//기본적으로 포인터 n이 가리키는 노드가 null이 아닐때까지 반복 즉, 특별히 if문에 걸리는게 아니라면 list의 마지막 node까지 검사하게 된다.
		if(n->key >= key) {	//n이 가리키는 노드의 Key값이 매개변수 key의 값보다 크다면 아래의 문장을 실행한다.
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {	//해당 위치에 적합한 Key값이지만 그 위치가 리스트의 첫번째라면 첫번째 노드 앞에 삽입하기 위한 로직을 실행한다.
				h->first = node;	
				node->link = n;
			} else { //해당 위치가 중간이거나 마지막인 경우, 그 경우에 맞는 로직을 실행한다.
				node->link = n;	//node의 link값에 n이 가리키고 있는 node의 주소값으로 대입한다. 즉, node의 뒤에 n이 가리키고 있는 노드가 연결된다.
				trail->link = node;	//포인터 n의 뒤를 따라가는 trail포인터의 link값을 node의 값으로 대입한다. 즉, 이전의 노드와 삽입할 노드가 연결된다.
			}
			return 0;
		}

		trail = n;	//포인터 trail을 n이 가리키고 있는 노드 값으로 변경. 즉, trail포인터를 한칸 이동
		n = n->link;	//포인터 n을 다음 노드값으로 변경.
	}

	//마지막 노드까지 찾지 못한 경우엔 마지막에 삽입한다.
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;	//삽입할 노드를 동적할당하고, 해당 필드에 key,link값을 대입한다.

	if (h->first == NULL)	//리스트가 없다면 h->first의 값에 node를 연결한다.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;	//헤드 포인터가 가리키는 리스트가 존재한다면 노드를 가리킬 포인터 n을 선언한다.
	while(n->link != NULL) {	//포인터 n을 리스트의 마지막 노드를 가리키도록 한다.
		n = n->link;
	}
	n->link = node;	//n이 가리키는 노드에 node값을 대입한다.
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {	//인수를 넘겨받은 후, key값을 가진 Node를 헤드포인터가 가리키는 리스트의 첫번째 부분에 삽입한다.

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	//아래는 리스트의 첫번째 위치에 노드를 삽입하는 로직이다.
	node->link = h->first;	
	h->first = node;

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)	//헤드포인터가 가리키는 리스트가 존재하지 않는다면 아래의 구문을 출력한다.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	//리스트의 노드를 가리킬 포인터 n을 선언한다.
	listNode* trail = NULL;	//포인터 n이 가리키는 노드의 바로 직전 노드를 가리킬 trail포인터를 선언한다.

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {	
		if(n->key == key) {	//삭제할 key값과 n이 가리키는 노드의 key값이 일치할 경우 아래의 구문을 실행한다.
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;	//삭제할 노드가 첫번째 노드라면 해당 명령문을 실행한다. 해당 노드가 리스트에서 빠진다.
			} else { // 중간인 경우거나 마지막인 경우 해당 명령문을 실행한다. 해당 노드가 리스트에서 빠진다.
				trail->link = n->link;	
			}
			free(n);	//삭제한 노드의 동적할당을 해제한다.
			return 0;
		}

		trail = n;	//노드를 가리키는 포인터들을 한 칸씩 옮긴다.
		n = n->link;
	}


	printf("cannot find the node for key = %d\n", key);	//리스트의 끝까지 검사했는데도 찾지 못한 경우 해당 구문을 출력한다.
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //리스트가 존재하지 않을 경우 아래 내용 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	//노드를 가리킬 포인터들을 선언한다.
	listNode* trail = NULL;

	// 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리
	if(n->link == NULL) {	//n->link값이 NULL인 경우 즉, 노드가 하나만 존재하는 경우
		h->first = NULL;	//헤드 포인터가 가리키는 노드를 제외한다.
		free(n);	//n이 가리키는 노드를 동적할당 해제한다.
		return 0;
	}

	
	while(n->link != NULL) {	//노드 포인터 n을 마지막 노드로 이동시킨다.
		trail = n;	
		n = n->link;
	}

	
	trail->link = NULL;	//마지막 노드의 직전 노드의 link값을 null값으로 변경함으로써 마지막 노드를 리스트에서 제외한다.
	free(n);	//해당 노드를 동적 할당 해제한다.

	return 0;
}



int deleteFirst(headNode* h) {	//헤드 포인터를 넘겨받아 포인터가 가리키는 첫번째 노드를 삭제한다.

	if (h->first == NULL)	//리스트가 존재하지 않는다면 아래 내용 출력.
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;	//첫번째 노드를 가리킬 포인터 선언.

	h->first = n->link;	//첫번째 노드를 리스트에서 제외한다.
	free(n);	//해당 노드를 동적할당 해제한다.

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) {	//리스트가 존재하지 않을 경우 아래 내용 출력.
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;	//첫번째 노드를 가리키는 포인터 선언.
	listNode *trail = NULL;	//
	listNode *middle = NULL;

	while(n != NULL){	//해당 리스트의 노드들의 링크가 역순으로 가리키도록 변환한다.
		trail = middle;
		middle = n;
		n = n->link;	//각각의 포인터를 한칸씩 옆의 노드로 이동
		middle->link = trail;	//노드 사이의 링크가 역순으로 가리키도록 한다.
	}

	h->first = middle;	//마지막 노드가 첫번째 순서가 되도록 한다.

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;	//노드를 가리킬 포인터 선언

	printf("\n---PRINT\n");

	if(h == NULL) {	//리스트가 존재하지 않는다면 아래 내용 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;	//해당 포인터가 첫번째 노드를 가리키도록 한다.

	while(p != NULL) {	//리스트의 마지막 노드를 가리킬때까지 반복한다.
		printf("[ [%d]=%d ] ", i, p->key);	//p포인터가 가리키는 노드의 key값을 출력하고 count된 i를 매번 출력한다.
		p = p->link;	//포인터가 옆 노드를 가리키도록한다.
		i++;	//i값을 카운트한다.
	}

	printf("  items = %d\n", i);	//최종 노드개수를 출력한다.
}

