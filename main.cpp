#include <iostream>
#include <stack>
#include <time.h>
using namespace::std;

class Node{
	public:
		int data;
		Node* leftChild;
		Node* rightChild;

	Node(int data){
		this->data = data;
		leftChild = NULL;
		rightChild = NULL;
		
	}
	void diplay(){
		cout<<data<<"  ";
	}
}; 

class BST{
	public:
		Node* root;
		int leafNodeCounter = 0;
		int oneNodeCounter = 0;
		int twoNodeCounter = 0;
		int noneCounter = 0;
		
	public:

		BST(){
			root = NULL;
		}
		void deleteRandom(int N){
			for(int i = 0; i < N; i++){
				int data = rand()%1000;
				deleteNode(data);
			}
			
			cout<<"Random nodes tried for deletion\t\t = "<<N<<endl;
			cout<<"No of Leaf nodes deleted\t\t = "<<leafNodeCounter<<endl;
			cout<<"No of 1 child Nodes deleted\t\t = "<<oneNodeCounter<<endl;
			cout<<"No of 2 child Nodes deleted\t\t = "<<twoNodeCounter<<endl;
			cout<<"No of nodes that was not present\t = "<<noneCounter<<endl;
		}
		
		Node* getSuccessor(Node* delNode){
			Node* successorParent = delNode;
			Node* successor = delNode;
			Node* current = delNode->rightChild;
			while(current != NULL){
				successorParent = successor;
				successor = current;
				current = current->leftChild;
			}
			if(successor != delNode->rightChild){
				successorParent->leftChild = successor->rightChild;
				successor->rightChild = delNode->rightChild;
			}
			
			return successor;
		}
		
		//populateTree function
		void pupolateTree(int N){
			srand(time(NULL));	//to get rid of the same generation of values
			for(int i = 0; i < N; i++){
				int number = rand()%1000;
				bool check = insert(new Node(number));
				if(check){
					cout<<number<<" successfully inserted"<<endl;	//if check is true the value will be successfully inserted
				}
				else{
					cout<<number<<" not inserted because it is already present."<<endl;
					N++;					//becuase value is not inserted due to similarity that's why we increment N		
				}
			}
		}
		
		bool insert(Node* node){
			if(root == NULL){
				root = node;
			}
			else{
					Node* current = root;
					Node* parent;
				while(1){
					parent = current;
					if(current->data == node->data){ 	//if value is already present, return false 
						return false;
					}
					if(current->data > node->data){
						current = current->leftChild;
						if(current == NULL){
							parent->leftChild = node;
							return true;
						}
					}
					else{
						current = current->rightChild;
						if(current == NULL){
							parent->rightChild = node;
							return true;
						}
					}
				}
			}
		}
		
		
		void inOrderTraverse(Node* localRoot){
			if(localRoot != NULL){
				inOrderTraverse(localRoot->leftChild);
				localRoot->diplay();
				inOrderTraverse(localRoot->rightChild);
				
			} 
			
		}
			
		void preOrderTraverse(Node* localRoot){
			if(localRoot != NULL){
				localRoot->diplay();
				inOrderTraverse(localRoot->leftChild);
				inOrderTraverse(localRoot->rightChild);
				
			}
		}
		
		void postOrderTraverse(Node* localRoot){
			if(localRoot != NULL){
				inOrderTraverse(localRoot->leftChild);
				inOrderTraverse(localRoot->rightChild);
				localRoot->diplay();
				
			} 
		}
		
		void traverse(){
			cout<<"Inorder: ";
			inOrderTraverse(root);
			cout<<endl;
			cout<<"Preorder: ";
			preOrderTraverse(root);
			cout<<endl;
			cout<<"Postorder: ";
			postOrderTraverse(root);
		}
		
		void recSearchItem(int n, Node* localRoot){
			
			
			if(localRoot == NULL){
				cout<<"Not found"<<endl;
				return;
			}
			else{
				if(localRoot->data == n){
					localRoot->diplay();
					return;
				}
				
				else if(n > localRoot->data){
					recSearchItem(n, localRoot->rightChild);
					
				}
				else{
					recSearchItem(n, localRoot->leftChild);
				}
			}
			
		}
		
	void inOrderIterativeTraversal(){

		stack<Node*> stack;		// Created an empty stack from stack Library.
		Node *current = root;

		while (!stack.empty() or current != NULL){	
    		if (current != NULL){
				stack.push(current);	// Pushed the current node to the stack
				current = current->leftChild;
			}
			else{ 
				current = stack.top(); 
				stack.pop();	//set the current to top and popped the stack
				current->diplay();
				current = current->rightChild; 
			}
		}
	}
	
	void deleteNode(int data){
		Node* current = root;
		Node* parent;
		bool isLeftChild = true;
		
		if(root == NULL){
			cout<<"Root is empty"<<endl;
		}
		else{
			while(data != current->data){
				parent = current;
				if(data > current->data){
					current = current->rightChild;
					isLeftChild = false;
				}
				else{
					current = current->leftChild;
					isLeftChild = true;
				}
				if(current == NULL){
					noneCounter++;	//The node isnot present so we increment nonoCounter.
					return;
				}
				
			}
			
		}
		
		if(current->leftChild == NULL and current->rightChild == NULL){
			if(root == current){
				root = NULL;
				delete current;
			}
			else if(isLeftChild){
				parent->leftChild = NULL;
				delete current;
			}
			else{
				parent->rightChild = NULL;
				delete current;
			}
			leafNodeCounter++;	//for leaf node we increament leafNodeCounter.
		}
		
		else if(current->rightChild == NULL){
			if(current == root){
				root = current->leftChild;
				delete current;
			}
			else if(isLeftChild){
				parent->leftChild = current->leftChild;
				delete current;				
			}
			else{
				parent->rightChild = current->leftChild;
				delete current;
			}
			oneNodeCounter++;	//for the node with one child we increament oneNodeCounter
		}
		
		else if(current->leftChild == NULL){
			if(current == root){
				root = current->rightChild;
				delete current;
			}
			else if(isLeftChild == true){
				parent->leftChild = current->rightChild;
				delete current;
			}
			else{
				parent->rightChild = current->rightChild;
				delete current;
			}
			oneNodeCounter++;	//for the node with one child we increament oneNodeCounter
		}
		
		else{
			Node* successor = getSuccessor(current);
			if(current == root){
				root = successor;
			}
			else if(isLeftChild){
				parent->leftChild = successor;
			}
			else{
				parent->rightChild = successor;
			}
			
			successor->leftChild = current->leftChild;
			delete current;
			
			twoNodeCounter++;		//for the node with two child we increament twoNodeCounter
		}	
	}
	
		void deletenode(int data){
		Node* current = root;
		Node* parent;
		bool isLeftChild = true;
		
		if(root == NULL){
			cout<<"Root is empty"<<endl;
		}
		else{
			while(data != current->data){
				parent = current;
				if(data > current->data){
					current = current->rightChild;
					isLeftChild = false;
				}
				else{
					current = current->leftChild;
					isLeftChild = true;
				}
				if(current == NULL){
					cout<<"Not found"<<endl;
					return;
				}
				
			}
			
		}
		
		if(current->leftChild == NULL and current->rightChild == NULL){
			if(root == current){
				root = NULL;
				delete current;
			}
			else if(isLeftChild){
				parent->leftChild = NULL;
				delete current;
			}
			else{
				parent->rightChild = NULL;
				delete current;
			}
		}
		
		else if(current->rightChild == NULL){
			if(current == root){
				root = current->leftChild;
				delete current;
			}
			else if(isLeftChild){
				parent->leftChild = current->leftChild;
				delete current;				
			}
			else{
				parent->rightChild = current->leftChild;
				delete current;
			}
		}
		
		else if(current->leftChild == NULL){
			if(current == root){
				root = current->rightChild;
				delete current;
			}
			else if(isLeftChild == true){
				parent->leftChild = current->rightChild;
				delete current;
			}
			else{
				parent->rightChild = current->rightChild;
				delete current;
			}
		}
		
		else{
			Node* successor = getSuccessor(current);
			if(current == root){
				root = successor;
			}
			else if(isLeftChild){
				parent->leftChild = successor;
			}
			else{
				parent->rightChild = successor;
			}
			
			successor->leftChild = current->leftChild;
			delete current;
			
		}	
	}				
}; 

int main(int argc, char** argv) {
	//check
	BST *tree = new BST();
	cout<<"How to Node you wanna Insert: ";
	int n;
	cin>>n;
	tree->pupolateTree(n);
	
	cout<<"\nInorder: "<<endl;
	tree->inOrderTraverse(tree->root);
	
	cout<<"\nHow many nodes you want to delete: ";
	cin>>n;
	tree->deleteRandom(n);
	
	cout<<"\nAfter deletion: "<<endl;
	tree->inOrderTraverse(tree->root);
	return 0;
}
	

	

	




	
	
	

