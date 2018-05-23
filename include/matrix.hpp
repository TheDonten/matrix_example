#include<iostream>
#include<cassert>
template <typename T>
class RBT {
private:
    struct node_t {
        node_t* parent;
        node_t* left;
        node_t* right;
        T value;
        bool color;  // черный это false, true - красный.
    };

private:
    node_t* root_;

public:
    RBT() { root_ = nullptr; }
    node_t* root() const { return root_; }
    node_t* grandparent(node_t* node) {
        if ((node != nullptr) && (node->parent != nullptr))
            return node->parent->parent;
        else
            return nullptr;
    }
    node_t* uncle(node_t* node) {
        node_t* g = grandparent(node);
        if (g == nullptr) return nullptr;
        if (node->parent == g->left)
            return g->right;
        else
            return g->left;
    }
    void insert(T value) {
        node_t* node = new node_t;
        node->value = value;
        node->right = nullptr;
        node->left = nullptr;
        if (root_ == nullptr) {
            root_ = node;
            root_->parent = nullptr;
            root_->color = false;
            return;
        }
        node_t* vetka = root_;
        while (vetka != nullptr) {
            if (vetka->value <= value) {
                if (vetka->right != nullptr) {
                    vetka = vetka->right;
                } else {
                    vetka->right = node;
                    vetka->right->parent = vetka;
                    vetka->right->color = true;
                    insert_case1(vetka->right);
                    return;
                }
            } else if (vetka->value >= value) {
                if (vetka->left != nullptr) {
                    vetka = vetka->left;
                } else {
                    vetka->left = node;
                    vetka->left->parent = vetka;
                    vetka->left->color = true;
                    insert_case1(vetka->left);
                    return;
                }
            } else
                return;
        }
    }
    void insert_case1(node_t* node) {
        if (node->parent == nullptr) {
            node->color = false;
        } else
            insert_case2(node);
    }
    void insert_case2(node_t* node) {
        if (node->parent->color == false)
            return;
        else
            insert_case3(node);
    }
    void insert_case3(node_t* node) {
        node_t* u = uncle(node);
        node_t* g;
        if ((u != nullptr) && (u->color == true)) {
            node->parent->color = false;
            u->color = false;
            g = grandparent(node);
            g->color = true;
            insert_case1(g);
        } else {
            insert_case4(node);
        }
    }
    void insert_case4(node_t* node) {
        node_t* g = grandparent(node);
        if ((node == node->parent->right) && (node->parent == g->left)) {
            rotate_left(node->parent);
            node = node->left;
        } else if ((node == node->parent->left) && (node->parent == g->right)) {
            rotate_right(node->parent);
            node = node->right;
        }
        insert_case5(node);
    }
    void insert_case5(node_t* node) {
        node_t* g = grandparent(node);
        node->parent->color = false;
        g->color = true;
        if ((node == node->parent->left) && (node->parent == g->left)) {
            rotate_right(g);
        } else if ((node == node->parent->right) && (node->parent == g->right)) {
            rotate_left(g);
        }
    }
    void rotate_left(node_t* node) {
        node_t* vetka = node->right;
        if(root_ == node){
            root_ = node->right;
        }
        vetka->parent = node->parent;
        if (node->parent != nullptr) {
            if (node->parent->left == node)
                node->parent->left = vetka;
            else
                node->parent->right = vetka;
        }
        node->right = vetka->left;
        if (vetka->left != nullptr) vetka->left->parent = node;
        node->parent = vetka;
        vetka->left = node;
    }
    void rotate_right(node_t* node) {
        node_t* vetka = node->left;
        if(root_ == node){
            root_ = node->left;
        }
        vetka->parent = node->parent;
        if (node->parent != nullptr) {
            if (node->parent->left == node)
                node->parent->left = vetka;
            else
                node->parent->right = vetka;
        }
        node->left = vetka->right;
        if (vetka->right != nullptr) vetka->right->parent = node;

        node->parent = vetka;
        vetka->right = node;
    }
    node_t * sibling(node_t* node){
        if (node == node->parent->left)
            return node->parent->right;
        else return
                    node->parent->left;
    }
    void replace_node(node_t* node, node_t* child){
        node_t* g = grandparent(child);
        child->parent = g;
        if(g) {
            if(g->left == node) g->left = child;
            else g->right = child;
        }
        else root_ = child;
        if(node->right == child) {child->right = node;
        node->right = nullptr;
        }
        else {child->left = node;
         node->left = nullptr;
        }
        node->parent = child;


    }
    void free(node_t*  & node){
        if(node == root_){
            root_ = nullptr;
            delete root_;
            return;
        }
        node_t* p = node->parent;
        node->parent = nullptr;
        if( p->left == node) {
            if(node->left) p->left = node->left;
            else p->left= nullptr;}
        else { if(node->right) p->right = node->right;
            else p->right = nullptr;}
        delete node;
    }
    void delete_case1(node_t* node){
        if(node->parent != nullptr)
            delete_case2(node);
    }
    void delete_case2(node_t* node){
        node_t* s = sibling(node);
        if(s == nullptr) return;
        if(s->color == true){
            node->parent->color = true;
            s->color = false;
            if(node == node->parent->left)
                rotate_left(node->parent);
            else
                rotate_right(node->parent);
        }
        delete_case3(node);
    }
    void delete_case3(node_t* node){
        node_t* s = sibling(node);
        if(s == nullptr) return;
        if (s->left == nullptr || s->right == nullptr) return;
              if ((node->parent->color == false) && (s->color == false) && (s->left->color == false) &&
                  (s->right->color == false)) {
                  s->color = true;
                  delete_case1(node->parent);
              } else delete_case4(node);

    }
    void delete_case4(node_t* node){
        node_t* s = sibling(node);
        if((node->parent->color == true) && (s->color == false) && (s->left->color == false) && (s->right->color == false)){
            s->color = true;
            node->parent->color = false;
        }
        else delete_case5(node);
    }
    void delete_case5(node_t* node){
        node_t* s = sibling(node);
        if(s->color == false){
            if((node == node->parent->left) &&(s->right->color == false) && (s->left->color == true)){
                s->color = true;
                s->left->color = false;
                rotate_right(s);
            } else if ((node == node->parent->right) && (s->left->color == false) && (s->right->color == true)){
                s->color = true;
                s->right->color = false;
                rotate_left(s);
            }
        }
        delete_case6(node);
    }
    void delete_case6(node_t * node){
        node_t* s = sibling(node);

        s->color = node->parent->color;
        node->parent->color = false;
        if (node == node->parent->left){
            if(s->right) s->right->color = false;
            rotate_left(node->parent);
        }
        else { if(s->left) s->left->color = false;
        rotate_right(node->parent);}
    }
    void delete_one_child(node_t* node,node_t* child){
        if(child) {
            replace_node(node, child);
            if (node->color == false) {
                if (child->color == true)
                    child->color = false;
                else delete_case1(child);
            }
        }
        free(node);
    }
    bool remove(int key){

        if(!(root_)){
            throw std::invalid_argument("root_ = nullptr");
        }
        node_t * vetka = root_;
        while(vetka){
            if(vetka->value == key) break;
            else {
                if(key < vetka->value) vetka = vetka->left;
                else vetka = vetka->right;
            }
            if(!(vetka)) return false;
        }
        if(vetka) {
            if (vetka->left == nullptr && vetka->right != nullptr) {
                delete_one_child(vetka, vetka->right);
            } else if (vetka->right == nullptr && vetka->left != nullptr) {
                delete_one_child(vetka, vetka->left);
            }
            else if(vetka->left == nullptr && vetka->right == nullptr){
                delete_case1(vetka);
                free(vetka);
            }
            else if(vetka->right && vetka->left) {
                node_t *child = choose_left_child(vetka);
                swap_child_parent(vetka,child);
                if(vetka->right != nullptr && vetka->left == nullptr) delete_one_child(vetka,vetka->right);
                else if(vetka->left != nullptr && vetka->right == nullptr) delete_one_child(vetka,vetka->left);
                else if(vetka->left == nullptr && vetka->right == nullptr){
                    delete_case1(vetka);
                    if(vetka->color == true){
                        if(child->right == vetka ) child->left->color = true;
                    }

                     free(vetka);

                }
                if(child == root_ && child->color == true) child->color = false;
            }

        }
        else return false;
    }
    node_t* choose_left_child(node_t* node){
        if(node->right) {node_t* vetka = node->right;

        while(vetka->left){
            vetka=vetka->left;
        }
        return vetka;}
        else return nullptr;
    }
    void swap_child_parent(node_t* node,node_t* child){

        node_t* node_parent = node->parent;
        node_t* parent_child = child->parent;
        node_t* right_child = node->right;
        child->parent = node_parent;
        if(node_parent){
            if(node_parent->right == node){
                node_parent->right = child;
            }
            else{
                node_parent->left = child;
            }
        }
        else root_ = child;
        node->right = child->right;
        if(child->right) child->right->parent = node;
        if(node->left) {
            node->left->parent = child;
            child->left = node->left;
            node->left = nullptr;}


        if(node != parent_child){
             if(parent_child->left == child) parent_child->left = node;
             else parent_child->right = node;
            node->parent = parent_child;
            child->right = right_child;
            right_child->parent = child;}
        else {
            child->right = node;
            node->parent = child;
        }

    }
    void print(std::ostream& stream, int level, node_t* node) const {
        if (node == nullptr) return;

        print(stream, level + 1, node->right);

        for (unsigned int i = 0; i < level; i++) {
            stream << "---";
        }
        if(node->color == false)
            stream << node->value <<"B"<< std::endl;
        if(node->color == true)
            stream << node->value <<"R"<< std::endl;
        print(stream, level + 1, node->left);
    }
    void destroy(node_t* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
    ~RBT() { destroy(root_); }

};

/*int main() {
    int value;

    RBT<int> sp1;
    sp1.insert(10);
    sp1.insert(12);
    sp1.remove(10);
   /* sp1.insert(85);
    sp1.insert(15);
    sp1.insert(70);
    sp1.insert(20);
    sp1.insert(60);
    sp1.insert(30);
    sp1.insert(50);
    sp1.insert(65);
    sp1.insert(80);
    sp1.insert(90);
    sp1.insert(40);
    sp1.insert(5);
    sp1.insert(55);*/
    /*sp1.insert(1);
    sp1.insert(2);
    sp1.insert(3);
    sp1.insert(4);
    sp1.insert(5);
    sp1.insert(6);
    sp1.insert(7);
    sp1.insert(8);
    sp1.insert(9);
    sp1.insert(10);

    sp1.insert(11);
    sp1.insert(0);
     sp1.remove(3);
     sp1.remove(2);*/
   /* for (unsigned int i = 0; i < 11; i++) {
        std::cin>>value;
        sp1.insert(value);

        std:: cout<<std::endl;
        std::   cout<<std::endl;

    }*/
     //sp1.print(std::cout, 0, sp1.root());
    //sp1.remove(17);
    /*sp1.insert(1);
    sp1.insert(2);
    sp1.insert(6);
    sp1.insert(8);
    sp1.insert(9);
    sp1.insert(7);
    sp1.insert(4);
    sp1.insert(4);
    sp1.insert(2);
    sp1.insert(4);
    sp1.insert(4);

    sp1.remove(4);
    sp1.remove(4);
    sp1.remove(4);
    sp1.remove(4);
    sp1.remove(8);
    sp1.remove(9);*/
   /*sp1.insert(1);
    sp1.insert(2);
    sp1.insert(3);
    sp1.insert(4);
    sp1.insert(5);
    sp1.insert(6);
    sp1.insert(7);
    sp1.insert(8);
    sp1.insert(9);
    sp1.insert(10);
    sp1.insert(11);
    sp1.insert(0);
   sp1.remove(3);
    sp1.insert(5);
    sp1.insert(5);
    sp1.insert(5);
    sp1.insert(5);
    sp1.insert(5);
    sp1.remove(2);*/
    /*sp1.insert(2);
    sp1.insert(1);
    sp1.insert(3);
    sp1.insert(4);
    sp1.insert(5);
    sp1.insert(2);
    sp1.remove(2);
    sp1.print(std::cout, 0, sp1.root());
}*/
