#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <queue>
#include <set>
#include <typeinfo>

namespace ariel {
  const int diff_flag = 4;
const int inorder_flag = 1; //le ihpat li mi heetekim
const int preorder_flag =2;
const int postorder_flag = 3;
    template<typename T> class BinaryTree {
    private:
        struct Node { //ze kvar pablic nitan lageshet le netunim
            T value;
            Node *left;
            Node *right;

            Node(T& v):value(v),left(nullptr),right(nullptr) {}
            T operator*()  { return value; }
        };

        Node *head;


    public:
          //i can be seen from evry class
        //inline static stack<Node *> stk;
        // unordered_set<fun> p;
        BinaryTree() : head(nullptr) {} //, size(0)
        ~BinaryTree(){ //postorder traversal

            RemoveSubtree(head);
        }
        void delet_tree(Node* root){
            if(!root){return;}
            delet_tree(root->left);
            delet_tree(root->right);
            delete root;
            root = nullptr;
        }
        BinaryTree(const BinaryTree & other){
            head = new Node(other.head->value);
            deep_copy(*head,*other.head);
        }
        void deep_copy(Node& root, Node& other_root){
            if(other_root.left) {
                root.left = new Node(other_root.left->value);
                deep_copy(*root.left,*other_root.left);
            }
            if(other_root.right) {
                root.right = new Node(other_root.right->value);
                deep_copy(*root.right,*other_root.right);
            }
        }

        BinaryTree& operator=(const BinaryTree& other) {
            if (this == &other) {return *this;}
            //delet_tree(head);
            delete head;
            head = new Node(other.head->value);
            deep_copy(*head, *other.head);
            return *this;
        }

        BinaryTree& operator = (BinaryTree&& other)noexcept{
            head = other->head;
            other->head = nullptr;
            return *this;
        }

        BinaryTree(BinaryTree&& other)noexcept{
            head = other.head;
            other.head = nullptr;
        }
        void RemoveSubtree(Node* root){ //postorder style delet
            if(root!= nullptr){
                if(root->left!= nullptr){
                    RemoveSubtree(root->left);
                }
                if(root->right!= nullptr){
                    RemoveSubtree(root->right);
                }
                delete root;

            }
        }
        BinaryTree &add_root(T root);

        BinaryTree &add_left(T exsist, T add);

        BinaryTree &add_right(T exsist, T add);

        Node* find_node(Node* root,T val){
            if(!root) {return nullptr;}
            if(root->value == val){return root;}

            Node* result = find_node(root->left,val);

            if(result){return result;}

            return find_node(root->right,val);
        }

        friend std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &b) {
            return out;
        }

        class iterator {
        protected:
            Node *pointer_to_current_node; //if & allways need to be initialized
            std::queue<Node*> tree_queue; //for each iterator we store diff it //maby without *
            unsigned int i = 0;

        public:
            iterator(const int flag =diff_flag,Node *ptr= nullptr ) : pointer_to_current_node(ptr) {

                // tree_in_vector.resize(_size);
                if(pointer_to_current_node){
                    if(flag == inorder_flag){
                        Inorder(pointer_to_current_node);
                        //cout<<"printing multiset inorder"<<endl;
                       //print_multiset();
                    }
                    else if(flag == preorder_flag){
                        Preoder(pointer_to_current_node);
                        //cout<<"printing multiset preorder"<<endl;
                      //  print_multiset();
                    }
                    else
                    {
                        Postorder(pointer_to_current_node);
                        //cout<<"printing multiset postorder"<<endl;
                        //print_multiset();
                    }
                }
                tree_queue.push(nullptr); //else just initiate

            }
//            void print_multiset(){
//                for(const auto &e :tree_queue){ //esh po arahi, befnim
//                    cout <<**e;
//                }
//                cout<<endl;
//            }

            T &operator*() const { return pointer_to_current_node->value; }

            T *operator->() const { return &(pointer_to_current_node->value); }

            //prefix
            //b_p == begin preorder
            //enum class fun{b_p,end_preorder,c_begin,c_end,beg_inorder,end_inorder,begin_postorder,end_postorder};
            //enum class num{one ,two,tree,four};
            iterator &operator++() {
//               //shgia logit
                //i!SET.empty()) {
                //auto r = tree_queue.begin(); //set sheli mehil pointers
                tree_queue.pop();

                    //print_multiset();
                    pointer_to_current_node = tree_queue.front(); //mezizim
                    //cout<<"iam at operator ++curr set start = "<< *p;
                    //SET.erase(p);
                    //auto k = SET.begin();


              return *this;
            }//i want does functions be individual for every function
            //postfix
            iterator operator++(int x) { //a++ le operator ze spizifi le naase
                iterator tmp = *this; //nikat oto kodem
                auto s= tree_queue.front();
                tree_queue.pop(); //nozi et hatop shel qeue
                pointer_to_current_node = tree_queue.front();//ve nazbia le rishon hahadash
                return tmp;

            }

            //friend void inorder(Node* n);
            bool operator==(const iterator &rhs) const {
                return pointer_to_current_node == rhs.pointer_to_current_node;
            }

            bool operator!=(const iterator &rhs) const {
                return pointer_to_current_node != rhs.pointer_to_current_node;
            }
            void Preoder(Node* n){ //ani mekabel pointer *n behemsheh mozi et haobekt


                if(n== nullptr){
                   // cout<<"iam at nullptr"<<endl;
                    return;
                }
                //cout<<"iam at preoder "<<n->value<<endl;
                //zarih laasot po new?
                tree_queue.push(n); //mishtamesh be banai maatik be hol zot sholeah heetek im ze le refernce
                Preoder(n->left);
                Preoder(n->right);
            }


            void Postorder(Node* n){
                if (n == nullptr){
                    return;
                }
                std::stack<Node*> s1 ;
                std::stack<Node*> s2;
                s1.push(n);
                Node* node = nullptr;

                while (!s1.empty()) {
                    node = s1.top();
                    s1.pop();
                    s2.push(node);
                    if (node->left){
                        s1.push(node->left);
                    }
                    if (node->right){
                        s1.push(node->right);
                    }
                }
                while (!s2.empty()) {
                    node = s2.top();
                    s2.pop();
                    tree_queue.push(node);
                }
                pointer_to_current_node = tree_queue.front();
            }



            void Inorder(Node* root) {
                std::stack<Node *> s;
                Node *curr = root;
                while (curr != nullptr || !s.empty()) {
                    while (curr != nullptr) {
                        s.push(curr);
                        curr = curr->left;
                    }
                    curr = s.top();
                    s.pop();
                    tree_queue.push(curr);
                    curr = curr->right;
                }
                pointer_to_current_node = tree_queue.front();
            }
        };



        // friend void Inorder(Node* node);


        iterator begin_preorder() { //lekol ehad leshanot et hagisha
            //po ani zarih leadlik boolean ve lehabot aharkah
           // p.insert(fun::b_p);
              //Preoder(head);
            return iterator{preorder_flag,head};

        }

        iterator end_preorder() {
            //SET.clear();
            //p.erase(fun::b_p);
            return iterator(diff_flag,nullptr);
        }

        iterator begin_inorder() {
            //inorder(head);
            //p.insert(fun::beg_inorder);
            return iterator(inorder_flag,head);
        }

        iterator end_inorder() {
            //SET.clear();
            //p.erase(fun::beg_inorder);
            return iterator(diff_flag,nullptr);
        }
        iterator begin(){ //same as inorder

            return begin_inorder(); //ze izor li et haobiekt ikra le default constructor
        }
        iterator end(){

            return end_inorder();

        };

        iterator begin_postorder() {
            //Postorder(head);
            //p.erase(fun::begin_postorder);
            return iterator(postorder_flag,head);
        }

        iterator end_postorder() {
            //SET.clear();
           // p.erase(fun::begin_postorder);
            return iterator(diff_flag,nullptr);
        }


    };


    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_root(T root){
        if(!head){
            head = new Node(root);
            return *this;
        }
        head->value = root;
        return *this;
    }

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_left(T exsist, T add){
        if(!head){throw std::invalid_argument{"Tree is empty"};}
        Node* node = find_node(head,exsist);
        if(!node){throw std::invalid_argument{"That node don't exsist"};}
        if(!node->left){
            node->left= new Node(add);
            return *this;
        }
        node->left->value = add;
        return *this;
    }

    template<typename T>
    BinaryTree<T>& BinaryTree<T>::add_right(T exsist, T add){
        if(!head){throw std::invalid_argument{"Tree is empty"};}
        Node* node = find_node(head,exsist);
        if(!node){throw std::invalid_argument{"That node don't exsist"};}
        if(!node->right){
            node->right = new Node(add);
            return *this;
        }
        node->right->value = add;
        return *this;
    }
}


