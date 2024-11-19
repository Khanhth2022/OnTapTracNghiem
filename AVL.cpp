#include <iostream>
#include <string>

using namespace std;
struct Node{
	int sbd;
	string hoTen;
	Node *left;
	Node *right;
	int height;
	Node(int s, string h, Node *l,Node *r,int c){
		sbd = s;
		hoTen = h;
		left = l;
		right = r;
		height = c;
	}
};

typedef struct Node* node;
class BSTree{
	public:
		BSTree(){
			root = NULL;
		}
		~BSTree(){
			while(!isEmpty()){
				makeEmpty(root);
			}
		}
		bool isEmpty(){
			return root == NULL;
		}
		void makeEmpty(){
			while(!isEmpty()){
				makeEmpty(root);
			}
		}
		void insert(int sbd, string hoTen){
			insert(sbd,hoTen,root);
		}
		node search(int sbd){
			search(sbd,root);
		}
		void duyetTrc(){
			duyetTrc(root);
		}
		void duyetGiua(){
			duyetGiua(root);
		}
		void duyetSau(){
			duyetSau(root);
		}
		node goc(){
			return root;
		}
		void inra(){
			inra(root);
		}
		void inla(){
			inla(root);
		}
		

	private:
		node root;
		void makeEmpty(node &t){
			if(t == NULL) return;
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
			t = NULL;
		}
		void insert(int sbd, string hoTen, node &t){
			if(t == NULL)
				t = new Node(sbd,hoTen,NULL,NULL,0);
			
			else if(sbd < t->sbd)
				insert(sbd, hoTen, t->left);
			
			else if(sbd > t->sbd)
				insert(sbd, hoTen, t->right);
			balance(t);
		}
		node search (int sbd, node t){
			if (t == NULL) return NULL;
			else if(sbd < t->sbd)
				search(sbd, t->left);
			
			else if(sbd > t->sbd)
				search(sbd, t->right);
			else
				return t;
		}
		void duyetTrc(node t){
			if(t == NULL) return;
			cout << t->sbd << " " << t->hoTen <<" ";
			
			duyetTrc(t->left);
			duyetTrc(t->right);
			
		}
		void duyetGiua(node t){
			if(t == NULL) return;
			
			duyetGiua(t->left);
			cout << t->sbd << " " << t->hoTen <<" ";
			duyetGiua(t->right);	
		}
		void duyetSau(node t){
					
			if(t == NULL) return;
			
			
			duyetSau(t->left);
			duyetSau(t->right);
			cout << t->sbd << " " << t->hoTen <<" ";
		}
		void th1(node &k2){
			node k1 = k2->left;
			k2->left = k1->right;
			k1->right = k2;
			k2->height = max(height(k2->left), height(k2->right))+1;
			k1->height = max(height(k1->left), k2->height) + 1;
			k2 = k1; 
		}
		void th4(node &k1){
			node k2 = k1->right;
			k1->right = k2->left;
			k2->left = k1;
			k1->height = max(height(k1->left), height(k1->right))+1;
			k1->height = max(height(k2->right), k1->height) + 1;
			k1 = k2; 
		}
		void th2(node &k3){
			th4(k3->left);
			th1(k3);
		}
		void th3(node &k1){
			th1(k1->right);
			th4(k1);
		}
		int height(node t){
			return t == NULL ? -1 : t->height;
		}
		int max(int lhs, int rhs){
			return lhs>rhs ? lhs : rhs;
		}
		void balance(node &t) {

			if (t == NULL)	return;			
			if (height(t->left) - height(t->right) > 1)
				if (height(t->left->left) >= height(t->left->right))
					th1(t);//TH1
			else
				th2(t);//TH2
			else if (height(t->right) - height(t->left) > 1)
				if (height(t->right->right) >= height(t->right->left))
					th4(t);//TH4
				else
					th3(t);//TH3
			
			t->height = max(height(t->left), height(t->right)) + 1;			
		}
		void inra(node t){
			cout << t->left->sbd << " " << t->right->sbd;
		}
		void inla(node t){
			if(t==NULL) return;
			if(t->right == NULL && t->left == NULL)
				cout << t->sbd << " ";
			inla(t->left);
			inla(t->right);
		}

};
int main()
{
	BSTree bst;
	// Chen mot so sinh vien moi vao cay.
	bst.insert(5, "Tuan");
	bst.insert(6, "Lan");
	bst.insert(3, "Cong");
	bst.insert(8, "Huong");
	bst.insert(7, "Binh");
	bst.insert(4, "Hai");
	bst.insert(2, "Son");
	// Tim hai sinh vien co so bao danh 4 va 9.
	Node * n1 = bst.search(4);
	Node * n2 = bst.search(9);
	// In ket qua tim kiem
	if (n1 != NULL)
	cout << "Sinh vien voi SBD=4 la " << n1->hoTen << endl;
	if (n2 == NULL)
	cout << "Khong tim thay sinh vien voi SBD=9" << endl;
	cout << "Duyet trc: "; bst.duyetTrc(); cout << endl;
	cout << "Duyet giua: "; bst.duyetGiua(); cout << endl;
	cout << "Duyet sau: "; bst.duyetSau(); cout << endl;
	Node *n3 = bst.goc();
	cout << "SBD nut goc: " << n3->sbd << endl;
	cout << "Cay co do sau 1: "; bst.inra(); cout << endl;
	cout << "La: "; bst.inla(); cout << endl;
	// Lam rong cay.
	bst.makeEmpty();
	if (bst.isEmpty())
	cout << "Cay da bi xoa rong" << endl;
	
	
	return 0;
}
