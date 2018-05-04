#include<iostream>
class RBT {
private:
    struct node_t {
        node_t* parent;
        node_t* left;
        node_t* right;
        int value;
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
    void insert(int value) {
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
            if (vetka->value < value) {
                if (vetka->right != nullptr) {
                    vetka = vetka->right;
                } else {
                    vetka->right = node;
                    vetka->right->parent = vetka;
                    vetka->right->color = true;
                    insert_case1(vetka->right);
                    return;
                }
            } else if (vetka->value > value) {
                if (vetka->left != nullptr) {
                    vetka = vetka->left;
                } else {
                    vetka->left = node;
                    vetka->left->parent = vetka;
                    vetka->right->color = true;
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
