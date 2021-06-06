#include <iostream>
#include <queue>

using namespace std;

namespace ariel
{

    template <typename T>
    class BinaryTree
    {

        class Node
        {
        public:
            T data;
            Node *right;
            Node *left;
            Node *parent;
            Node(const T &d) : data(d), left(nullptr), right(nullptr), parent(nullptr) {}

            //copy constructor
            Node(Node &other) : data(other.data)
            {
                if (other.left != nullptr)
                {
                    left = new Node(*other.left);
                }
                else
                {
                    left = nullptr;
                }

                if (other.right != nullptr)
                {
                    right = new Node(*other.right);
                }
                else
                {
                    right = nullptr;
                }
                if (other.parent != nullptr)
                {
                    parent = new Node(*other.parent);
                }
                else
                {
                    parent = nullptr;
                }
            }

            Node(Node &&other) noexcept
            {
                data = other.data;
                left = other.left;
                right = other.right;
                parent = other.parent;
                other.value = nullptr;
                other.left = nullptr;
                other.right = nullptr;
                other.parent = nullptr;
            }

            Node &operator=(Node other)
            {
                if (this == other)
                {
                    return *this;
                }
                delete right;
                delete left;
                delete parent;

                if (left != nullptr)
                {
                    left = new Node(*other.left);
                }
                else
                {
                    left = nullptr;
                }

                if (right != nullptr)
                {
                    right = new Node(*other.right);
                }
                else
                {
                    right = nullptr;
                }
                if (parent != nullptr)
                {
                    parent = new Node(*other.parent);
                }
                else
                {
                    parent = nullptr;
                }
                return *this;
            }
            Node &operator=(Node &&other) noexcept
            {
                if (this == other)
                {
                    return *this;
                }

                if (left != nullptr)
                {
                    delete left;
                }
                if (right != nullptr)
                {
                    delete right;
                }
                if (parent != nullptr)
                {
                    delete parent;
                }

                left = other.left;
                right = other.right;
                data = other.data;
                parent = other.parent;

                other.left = nullptr;
                other.right = nullptr;
                other.parent = nullptr;

                return *this;
            }
            ~Node()
            {
                delete left;
                delete right;
                delete parent;
            }
        }; //end node class

        //---------------------------------------start of Iterator class------------------------------------------------------------

        enum order_type
        {
            PREORDER,
            INORDER,
            POSTORDER
        };

        class Iterator
        {
        private:
            Node *current;
            order_type type;
            queue<Node *> MyQueue;

            void Run_Preorder(Node *root)
            {
                if (root != nullptr)
                {
                    MyQueue.push(root);
                    Run_Preorder(root->left);
                    Run_Preorder(root->right);
                }
            }

            void Run_Inorder(Node *root)
            {
                if (root != nullptr)
                {
                    Run_Inorder(root->left);
                    MyQueue.push(root);
                    Run_Inorder(root->right);
                }
            }

            void Run_Postorder(Node *root)
            {
                if (root != nullptr)
                {
                    Run_Postorder(root->left);
                    Run_Postorder(root->right);
                    MyQueue.push(root);
                }
            }

        public:
            Iterator() ////default constructor
            {
                current = nullptr;
            }

            Iterator(Node *curr, order_type type) // constructor to link the order type
            {
                this->current = curr;
                this->type = type;
                if (type == PREORDER)
                {
                    Run_Preorder(current);
                    MyQueue.push(nullptr);

                    current = MyQueue.front();
                    MyQueue.pop();
                }

                if (type == INORDER)
                {
                    Run_Inorder(current);
                    MyQueue.push(nullptr);
                    current = MyQueue.front();
                    MyQueue.pop();
                }

                if (type == POSTORDER)
                {
                    Run_Postorder(current);
                    MyQueue.push(nullptr);
                    current = MyQueue.front();
                    MyQueue.pop();
                }
            }
            // Iterator(ORDDER_TYPE type)
            // {
            //     current = nullptr;
            //     this->type = type;
            // }
            // Iterator(Node *curr, ORDDER_TYPE type) // check null
            // {
            //     if (type == PREORDER)
            //         this->current = curr;
            //     else
            //     {
            //         Node * tmp = curr;
            //         while(tmp->left != NULL)
            //         {
            //             tmp = tmp->left;
            //         }
            //         this->current = tmp;

            //     }
            //     this->type = type;
            // }

            bool operator==(const Iterator &rhs) const
            {
                return (this->current == rhs.current);
            }

            bool operator!=(const Iterator &rhs) const
            {
                return (this->current != rhs.current);
            }
            T &operator*() const
            {

                return this->current->data; // NULL ???
            }

            T *operator->() const
            {
                return &(this->current->data); // NULL ????
            }

            Iterator &operator++()
            {

                if (!MyQueue.empty())
                {
                    this->current = MyQueue.front();
                    MyQueue.pop();
                }
                return *this;
            }
            Iterator operator++(int)
            {
                Iterator ans = *this;
                this->current = MyQueue.front();
                MyQueue.pop();
                return ans;
            }
            // private:

            // Iterator & inorderNext()
            // {
            //      Node * tmp;
            //     if (curr->right != NULL)
            //     {
            //         tmp = curr->right;
            //         while(tmp->left != NULL)
            //         {
            //             tmp = tmp->left;
            //         }
            //         current = tmp;
            //         return current;
            //     }

            //     Node* parent = curr->parent;
            //     tmp = curr;
            //     while(parent && parent->right == tmp)
            //     {
            //         tmp = parent;
            //         parent = parent->parent;
            //     }
            //     curr = parent;
            //     return parent; //how finish ??

            // }

        }; //end iterator class

        //---------------------------------------start of BT class------------------------------------------------------------
    private:
        Node *root;
        Node *Run_on_Tree(Node *root, T data)
        {
            if (root == nullptr || root->data == data)
            {
                return root;
            }
            Node *left = Run_on_Tree(root->left, data);
            Node *right = Run_on_Tree(root->right, data);
            if (right == nullptr)
            {
                return left;
            }
            return right;
        }

    public:
        BinaryTree()
        {
            root = NULL;
        }
        BinaryTree(BinaryTree &other)
        {
            if (root != nullptr && other.root != nullptr)
            {
                root = new Node(*other.root);
            }
        }
        BinaryTree(BinaryTree &&other) noexcept
        {
            root = other.root;
            other.root = nullptr;
        }
        BinaryTree &operator=(BinaryTree &&other) noexcept
        {
            if (root != nullptr)
            {
                delete root;
            }
            root = other.root;
            other.root = nullptr;
            return *this;
        }
        BinaryTree &operator=(const BinaryTree other)
        {
            if (root != nullptr)
            {
                delete root;
            }
            root = new Node(*other.root);
            return *this;
        }

        BinaryTree<T> &add_root(T d)
        {
            if (root != nullptr)
            {
                root->data = d;
                return *this;
            }
            root = new Node{d};
            return *this;
        }

        BinaryTree &add_left(T parent, T son)
        {
            Node *node = Run_on_Tree(root, parent);
            if (node == nullptr)
            {
                throw std::invalid_argument{"The parent dosen't exist in the tree"};
            }
            if (node->left == nullptr)
            {
                node->left = new Node{son};
            }
            else
            {
                node->left->data = son; //updating the data of the left child
            }
            return *this;
        }
        BinaryTree &add_right(T parent, T son)
        {
            Node *node = Run_on_Tree(root, parent);
            if (node == nullptr)
            {
                throw std::invalid_argument{"The parent dosen't exist in the tree"};
            }
            if (node->right == nullptr)
            {
                node->right = new Node{son};
            }
            else
            {
                node->right->data = son; //updating the data of the right child
            }
            return *this;
        }
        Iterator begin_preorder() { return Iterator{root, PREORDER}; }

        Iterator end_preorder() { return Iterator{}; }

        Iterator begin_inorder() { return Iterator{root, INORDER}; }

        Iterator end_inorder() { return Iterator{}; }

        Iterator begin_postorder() { return Iterator{root, POSTORDER}; }

        Iterator end_postorder() { return Iterator{}; }

        Iterator begin() { return Iterator{root, INORDER}; } //should start from left then root and then right

        Iterator end() { return Iterator{}; }

        friend std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &bt)
        {
            //     for (auto node : bt)
            // {
            //     out << node << ",";
            // }
            // out << endl;
            return out;
        }

        ~BinaryTree()
        {
            if (root != nullptr)
            {
                delete root;
            }
        }
    };

    //   int main(){
    //          BinaryTree<int> tree_of_ints;
    //     (tree_of_ints.add_root(1));
    //     (tree_of_ints.add_left(1, 9));
    //     (tree_of_ints.add_left(9, 4));
    //     (tree_of_ints.add_right(9, 5));

    //     cout << tree_of_ints << endl;
    //         return 0;

    //     }
}