#include <iostream>
#include <vector>

using namespace std;

int NODE_MAX = 5000;

struct Node {
	int data;
	Node* next;

	Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
	Node* head;
	Node* tail;
	vector<Node*> NodeArr;
	int NodeCnt;

public:
	LinkedList() : head(nullptr), tail(nullptr), NodeCnt(0) {
		NodeArr.resize(NODE_MAX, nullptr);
	}

	Node* GetNewNode(int data) {
		return NodeArr[NodeCnt++] = new Node(data);
	}

	void InsertNums(int index, vector<int>& nums) {
		int start = 0;
		
		// 맨 처음 부분에 넣기
		if (index == 0) {
			// 이미 헤드가 있음
			// 첫 숫자 넣은 후, 걔를 헤드로 바꿔주기
			if (head != nullptr) {
				Node* newnode = GetNewNode(nums[0]);
				newnode->next = head;
				head = newnode;
			}
			// 헤드가 없음 (아무것도 없음)
			else {
				head = GetNewNode(nums[0]);
			}
			index++;
			start++;
		}

		// index 위치까지 이동 (여기부터 넣어야 하니까)
		// cur은 넣을 곳 바로 전 노드 가리킴
		Node* cur = head;
		for (int i = 1; i < index; i++)
			cur = cur->next;

		// 하나씩 꼽 껴주기
		for (int i = start; i < nums.size(); i++) {
			// 꼽 낄 노드 생성
			Node* newnode = GetNewNode(nums[i]);
			
			// 순서 조심해서 꼽 껴주고
			newnode->next = cur->next;
			cur->next = newnode;

			// cur을 꼭 옮겨줘야 함!
			cur = newnode;
		}

		// 내가 꼴찌면 tail
		if (cur->next == nullptr)
			tail = cur;
	}

	// index부터 cnt개 지워야 함
	void RemoveNode(int index, int cnt) {
		Node* cur = head;
		
		// 헤드를 지우래 -> 헤드 대피
		if (index == 0) {
			for (int i = 0; i < cnt; i++) {
				cur = cur->next;
			}
			head = cur;
			return;
		}

		// 지워야 하는 곳까지 옮겨
		// cur은 지울 거 바로 전 노드 가리킴
		for (int i = 1; i < index; i++) {
			cur = cur->next;
		}

		// 잠시 저장해두고
		Node* temp = cur;

		// 삭제되는 마지막 노드까지 가기
		for (int i = 0; i < cnt; i++)
			cur = cur->next;

		// 사이 무시하고 바로 이어주기
		temp->next = cur->next;

		if (temp->next == nullptr)
			tail = temp;
	}

	// 맨 마지막에 노드 하나 넣기
	void AddTail(int data) {
		Node* cur = tail;
		Node* newnode = GetNewNode(data);
		cur->next = newnode;
		tail = newnode;
	}

	// cnt개 출력
	void PrintList(int cnt) {
		Node* cur = head;
		for (int i = 0; i < cnt; i++) {
			cout << cur->data << " ";
			cur = cur->next;
		}
	}
};
