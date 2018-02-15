#include "nodedata.h"

// buildTree and initArray REMAIN IN MAIN METHOD BECAUSE THEY ARE GLOBAL.

/* This class, BinTree, is a Binary tree that follows the Binary Search
 * algorithm. The lesser value Nodes go to the left, while the greater
 * value Nodes go to the right.
 *
 * This class can compare if two BinTrees are equal or unequal, it can
 * assign a BinTree values from another BinTree, and can move the BinTree
 * into an array and then back into a BinTree. Also, it can print the BinTree
 * out in an in-order fashion. It can also determine whether a Node is in the
 * BinTree and can retrieve the desired Node data. Additionally, BinTree can
 * return the position of a Node relative to the bottom of the BinTree.
 *
 * */
class BinTree {

friend ostream& operator<<(ostream& outStream, const BinTree& otherTree);


private:
    struct Node {
        NodeData* data;						// pointer to data object
        Node* left;							// left subtree pointer
        Node* right;						// right subtree pointer
    };
    Node* root;                             // root of the tree


    //----------------------------outputHelper---------------------------------
    // Helper for output overloaded operator. Prints the BinTree's data in
    // an in-order fashion
    void outputHelper(ostream& outStream, const Node* currentPtr ) const;


    //--------------------------sideways----------------------------------------
    // Helper for displaySideways(). Displays BinTree's structure sideways.
    void sideways(Node*, int) const;


    // ----------------------------insertHelper--------------------------------
    // Helper for insert() method.  Inserts the data into the BinTree.
    // Returns True is successful. Returns False if not successful
    bool insertHelper(NodeData* s, Node*& current);


    //---------------------------destroyTree-----------------------------------
    // Helper for Destructor and makeEmpty() methods. Deletes all Nodes and
    // NodeData in BinTree. BinTree will be empty after.
    void destroyTree(Node* currentPtr);


    //---------------------------copyTree--------------------------------------
    // Helper for copy constructor and assignment operator. Creates a deep copy
    // of the other BinTree.
    void copyTree(const Node* otherPtr, Node*& currentPtr);


    //---------------------------checkEqual------------------------------------
    // Helper for equal and unequal operator. Checks to see if every Node in
    // both BinTrees are the same. Returns true if they are equal. Fale is not
    bool checkEqual(const Node* otherPtr, const Node* thisPtr) const;


    //----------------------------heightHelper---------------------------------
    // Helper for getHeight() method. Returns the height of the Node from the
    // bottom of the BinTree.
    int heightHelper(const Node* currentPtr) const;


    //---------------------------findNode--------------------------------------
    // Helper for retrieve() and getHeight() methods. Finds the Node in the
    // BinTree that has a specific NodeData value. Returns true if the BinTree
    // contains that NodeDat. Returns false if it does not contain it.
    bool findNode(const NodeData &target, Node* currentPtr, Node*& targetPtr) const;


    //--------------------------toArrayHelper----------------------------------
    // Helper for bstreeToArray() method. Moves all of the data from the array
    // into the BinTree so that it is balanced on both sides.
    void toArrayHelper(NodeData* arrayPtr[], Node* currentPtr, int& index);


    //---------------------------toBSTreeHelper--------------------------------
    // Helper for arrayToBSTree() method. Moves the data from this BinTree into
    // the array in pre-order fashion.
    void toBSTreeHelper(NodeData* array[], int min, int max, Node*& currentPtr);



public:

    //---------------------------Empty Constructor-----------------------------
    // Creates an empty BinTree.
    BinTree();


    // -------------------------Copy Constructor------------------------------
    // Creates a deep copy of another BinTree.
    BinTree(const BinTree&);


    // ---------------------------Destructor----------------------------------
    // Destroys tree and frees memory.  Calls private method destroyTree().
    ~BinTree();


    // ---------------------------isEmpty---------------------------------------
    // Returns true if empty. Returns false if not. Leaves BinTree unchanged.
    bool isEmpty() const;


    //---------------------------makeEmpty-------------------------------------
    // Makes BinTree empty. Calls private method destroyTree().
    void makeEmpty();


    //------------------------------insert-------------------------------------
    // Inserts a Node into the BinTree that contains the NodeData. Calls
    // private method insertHelper().
    bool insert(NodeData* s);


    // --------------------------displaySideways-------------------------------
    // Displays the BinTree sideways. Calls private method sideways()
    void displaySideways() const;

    // -------------------------retrieve--------------------------------------
    // Returns true if NodeData is in BinTree. Returns false otherwise. Calls
    // private method findNode(). Leaves BinTree unchanged.
    bool retrieve(const NodeData &, NodeData *&) const;

    // --------------------------getHeight-----------------------------------
    // Returns the height of the Node from the bottom of the BinTree. Calls
    // private method findNode() and heightHelper(). Leaves BinTree unchanged
    int getHeight(const NodeData &) const;


    //-----------------------------bsTreeToArray-------------------------------
    // Moves all of the data from the BinTree into the array. Calls private
    // method toArrayHelper() and makeEmpty()
    void bstreeToArray(NodeData* []);


    //----------------------------arrayToBSTree--------------------------------
    // Moves the data from the array into the BinTree. Calls the private method
    // to BSTreeHelper. Array is empty afterwards
    void arrayToBSTree(NodeData* []);

    // --------------------------Equal Operator-------------------------------
    // Checks if the two BinTrees are equal. Calls private method checkEqual()
    // to check every Node. Returns true if equal. Returns false if not
    bool operator==(const BinTree &) const;

    // -------------------------Unequal Operator----------------------------
    // Checks if the two BinTrees are equal. Negates the equal operator.
    // Returns true if unequal. Returns false if equal.
    bool operator!=(const BinTree &) const;

    // -----------------------Assignment Operator--------------------------
    // Assigns this BinTree the same values as the other BinTree. Calls
    // private method destroyTree before assigning data so no memory leaks.
    // returns a reference to this BinTree afterwards.
    BinTree& operator=(const BinTree &);



};





