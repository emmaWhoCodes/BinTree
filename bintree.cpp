#include "bintree.h"


/*-----------------------------Empty Constructor-------------------------------
 * Pre: None
 *
 * Post: Creates an empty BinTree.
 *---------------------------------------------------------------------------*/
BinTree::BinTree() {
    root = NULL;
}



/* ------------------------------Copy Constructor------------------------------
 * Pre: Takes in a read-only reference to another BinTree, otherTree.
 *
 * Post: Creates a deep copy of otherTree. Meaning that this BinTree is the
 *      exact same as otherTree, but it is its own tree.
 * */
BinTree::BinTree(const BinTree& otherTree) {
    root = NULL;
    copyTree(otherTree.root, root);
}



/*---------------------------------Destructor----------------------------------
 * Pre: None
 *
 * Post: Destroys this BinTree by deleting everything in the tree. The BinTree
 *       will be NULL.
 *---------------------------------------------------------------------------*/
BinTree::~BinTree() {
    makeEmpty();
}



/*---------------------------------CopyTree------------------------------------
 * Pre: Takes in a read-only pointer to a Node in another BinTree, otherPtr
 *      Takes in a reference pointer, currentPtr, which points to a Node in
 *      this BinTree.
 *
 * Post: Copies this BinTree to be an exact copy of the other BinTree
 *---------------------------------------------------------------------------*/
void BinTree::copyTree(const Node* otherPtr, Node*& currentPtr) {
    if (otherPtr != NULL) {
        currentPtr = new Node();
        currentPtr->left = NULL;
        currentPtr->right = NULL;
        currentPtr->data = new NodeData(*otherPtr->data);
        copyTree(otherPtr->left, currentPtr->left);
        copyTree(otherPtr->right, currentPtr->right);
    }
}



/* -----------------------------Output Operator--------------------------------
 * Pre: Takes in a reference to an ostream, outStream, which is used to write
 *      the output. Takes in a read-only reference to another BinTree,
 *      otherTree, which is going to be the tree printed.
 *
 * Post: Prints the BinTree out to the console in an in-order traversal. This
 *      will print it out alphabetically. Returns the ostream after every
 *      BinTree node has been printed.
 *---------------------------------------------------------------------------*/
ostream& operator<<(ostream& outStream, const BinTree& otherTree) {
    const BinTree::Node* currentPtr = otherTree.root;
    otherTree.outputHelper(outStream, currentPtr);
    outStream << endl;
    return outStream;
}



/*------------------------Private: OutputHelper-------------------------------
 * Pre: Takes in a reference to an ostream, outStream, which is used to print
 *      the data to the console. Takes in a read-only pointer to a Node,
 *      currentPtr, which points to a Node within the BinTree that will be
 *      printed.
 *
 * Post: Is a read-only method. Prints the data in an in-order traversal.
 *---------------------------------------------------------------------------*/
void BinTree::outputHelper(ostream& outStream, const Node* currentPtr) const {
    if (currentPtr != NULL) {
        outputHelper(outStream, currentPtr->left);
        cout << *currentPtr->data << " ";
        outputHelper(outStream, currentPtr->right);
    }
}



/*--------------------------------getHeight------------------------------------
 * Pre: Takes in a read-only reference to a NodeData, target, which is used to
 *      find a matching NodeData value in the BinTree.
 *
 * Post: Returns an int that is the height of the Node from the bottom of the
 *      tree. (The Node contains the matching NodeData). If the NodeData is not
 *      in the BinTree, or the tree is empty, then 0 is returned.
 *---------------------------------------------------------------------------*/
int BinTree::getHeight(const NodeData& target) const {
    Node *targetPtr;
    if (findNode(target, root, targetPtr)) {
        int height = heightHelper(targetPtr);
        return height;
    }
    targetPtr = NULL; // No dangling pointer.
    return 0;
}



/*------------------------------Private: findNode------------------------------
 * Pre: Takes in a read-only reference to a NodeData, target, which is the
 *      NodeData that is going to be searched for. Takes in a pointer to a
 *      Node, currentPtr, which points to the current node in the BinTree.
 *      Takes in a reference pointer to a Node, targetPtr, which will point to
 *      the Node that contains target if found.
 *
 * Post: Searches the tree to see if it contains target. If it contains target,
 *       then targetPtr will point to the Node that contains it and returns true.
 *       If target is not found, then targetPtr does not point to anything and
 *       false is returned.
 *---------------------------------------------------------------------------*/
bool BinTree::findNode(const NodeData &target, Node* currentPtr
        , Node*& targetPtr) const {        // to keep it under 80.
    if (currentPtr == NULL) {
        return false;
    } else if (*currentPtr->data == target) {
        targetPtr = currentPtr;
        return true;
    } else {
        bool left = findNode(target, currentPtr->left, targetPtr);
        bool right = findNode(target, currentPtr->right, targetPtr);
        return left || right;
    }
}



/*----------------------------Private: heightHelper----------------------------
 * Pre: Takes in a read-only pointer to a Node, currentPtr. Assumes that the
 *      method "findNode" has been ran before and currentPtr points to a valid
 *      Node, or currentPtr is NULL.
 *
 * Post: Counts the height of the node from its location in the tree to the
 *       bottom. Returns the height.
 *----------------------------------------------------------------------------*/
int BinTree::heightHelper(const Node* currentPtr) const {
    if (currentPtr == NULL) {
        return 0;
    } else {
        int left = heightHelper(currentPtr->left) + 1;
        int right = heightHelper(currentPtr->right) + 1;
        if (left > right) {
            return left;
        }
        return right;
    }
}



/*-------------------------------retrieve-------------------------------------
 * Pre: Takes in a read-only reference to a NodeData, target, which is the
 *      value to look for. Takes in a pointer references to a NodeData,
 *      nodeDataPtr.
 *
 * Post: Retrieves target's value from the tree. Makes nodeDataPtr point to
 *       the Node that contains target's value in the BinTree. If target is
 *       not in the tree, then the nodeDataPtr is set to NULL. If the target
 *       if found, then returns true. If target is not in the BinTree, returns
 *       false. **SETS nodeDataPtr TO NULL IF NOT FOUND.
 *---------------------------------------------------------------------------*/
bool BinTree::retrieve(const NodeData &target, NodeData *& nodeDataPtr) const {
    Node* nodePtr;
    if (findNode(target, root, nodePtr)) {
        nodeDataPtr = nodePtr->data;
        nodePtr = NULL;
        return true;
    }
    nodeDataPtr = NULL;  // NULL if not found in tree
    nodePtr = NULL; //no dangling ptr
    return false;
}



/*-----------------------------Equal Operator----------------------------------
 * Pre: Takes in a read-only reference to another BinTree, otherTree.
 *
 * Post: Tests whether this BinTree is equal to otherTree, meaning that
 *       are identical. (If they have the same Node structure with the same
 *       values in them) Returns true if they identical. Returns false if they
 *       are not.
 *---------------------------------------------------------------------------*/
bool BinTree::operator==(const BinTree& otherTree) const {
    Node* otherPtr = otherTree.root;
    Node* thisPtr = root;
    return checkEqual(otherPtr, thisPtr);
}



/*----------------------------Unequal Operator---------------------------------
 * Pre: Takes in a read-only reference to another BinTree, otherTree.
 *
 * Post: Tests whether this BinTree is unequal to otherTree, meaning that
 *       they do not contain the same values and/or structure
 *---------------------------------------------------------------------------*/
bool BinTree::operator!=(const BinTree& otherTree) const {
    return !operator==(otherTree);
}

BinTree& BinTree::operator=(const BinTree& otherTree) {
    if (*this != otherTree) {
        destroyTree(root);
        copyTree(otherTree.root, root);
    }
    return *this;
}



/*-------------------------Private: checkEqual---------------------------------
 * Pre: Takes in a read-only pointer to a Node in another BinTree, otherPtr.
 *      Takes in a read-only pointer to a Node in this BinTree, thisPtr.
 *
 * Post: Check the whole tree to see if they have the same structure AND they
 *       contain the same values in each Node. Returns true if the two trees
 *       are identical. Returns false if they are unequal.
 *-----------------------------------------------------------------------------*/
bool BinTree::checkEqual(const Node* otherPtr, const Node* thisPtr) const {
    if (otherPtr == NULL && thisPtr == NULL) {
        return true;
    } else if (otherPtr != NULL && thisPtr != NULL) {
        bool value = *otherPtr->data == *thisPtr->data;
        bool left = checkEqual(otherPtr->left, thisPtr->left);
        bool right = checkEqual(otherPtr->right, thisPtr->right);
        return value && left && right;
    } else {
        return false;
    }
}



/*----------------------------------insert-------------------------------------
 * Pre: Takes in a pointer to a NodeData, insertPtr, which is the value that
 *      will be inserted into the BinTree.
 *
 * Post: Inserts insertPtr into the BinTree. Can only insert if the BinTree
 *      does not contain insertPtr's value. Returns true if it was successfully
 *      inserted. Returns false if it cannot be inserted.
 *---------------------------------------------------------------------------*/
bool BinTree::insert(NodeData* insertPtr) {
    bool insert = insertHelper(insertPtr, root);
    return insert;
}



/*-----------------------------Private: insertHelper---------------------------
 * Pre: Takes in a pointer to a NodeData, insertPtr. Takes in a pointer to a
 *      reference Node, currentPtr, which is a node that is currently in the
 *      tree.
 *
 * Post: Creates a new Node and assigns it insertPtr's value, then adds it
 *       into the tree. The lesser-value Nodes are inserted to the left,
 *       while greater-value Nodes are inserted to the right. Returns true
 *       if successfully inserted into tree. Returns false if no insertion
 *       was made.
 *---------------------------------------------------------------------------*/
bool BinTree::insertHelper(NodeData* insertPtr, Node*& currentPtr) {
    if (currentPtr == NULL) {
        Node* newNodePtr = new Node;
        newNodePtr->data = insertPtr;
        newNodePtr->left = NULL;
        newNodePtr->right = NULL;
        currentPtr = newNodePtr;
        return true;
    } else if (*insertPtr == *currentPtr->data) {
        return false;
    } else if (*insertPtr < (*currentPtr->data)) {
        return insertHelper(insertPtr, currentPtr->left);
    } else {
        return insertHelper(insertPtr, currentPtr->right);
    }
}



/*---------------------------------isEmpty-------------------------------------
 * Pre: None.
 *
 * Post: Checks if the BinTree is empty. Returns true if the BinTree is empty.
 *       returns false if it is not empty.
 *---------------------------------------------------------------------------*/
bool BinTree::isEmpty() const {
    return root == NULL;
}



/* ----------------------------bstreeToArray-----------------------------------
 * Pre: Takes in an array that contains the NodeData pointer data type, array.
 *
 * Post: Moves all of the data stored in this BinTree into the array. The
 *       BinTree becomes empty.
 *---------------------------------------------------------------------------*/
void BinTree::bstreeToArray(NodeData* array[]) {
    int startIndex = 0;
    toArrayHelper(array, root, startIndex);
    makeEmpty();
}



/*---------------------------Private: toArrayHelper----------------------------
 * Pre: Takes in an array that is of NodeData pointer type. Takes in a pointer
 *      to a Node, currentPtr, which points to a Node in this BinTree. Takes
 *      in a reference to an int, index, which is the current index in the array.
 *
 * Post: Moves all of the data in the BinTree to the tree by using an in-order
 *      traversal. The BinTree's structure remains but no data is in it.
 *---------------------------------------------------------------------------*/
void BinTree::toArrayHelper(NodeData* arrayPtr[], Node* currentPtr
        , int& index) {
    if (currentPtr != NULL) {
        toArrayHelper(arrayPtr, currentPtr->left, index);
        arrayPtr[index] = currentPtr->data;
        currentPtr->data = NULL;
        index++;
        toArrayHelper(arrayPtr, currentPtr->right, index);
    }
}


/*------------------------------arrayToBSTree----------------------------------
 * Pre: Takes in an array of NodeData pointer data, array, that is filled with
 *      the data that will go into the BinTree. **BINTREE MUST BE EMPTY SO NO
 *      MEMORY LEAKS
 *
 * Post: Moves all of the data from array into this BinTree. The data is
 *       entered so the BinTree is balanced on both sides.
 *---------------------------------------------------------------------------*/
void BinTree::arrayToBSTree(NodeData* array[]) {
    this->makeEmpty();
    int size = 0;
    while (array[size] != NULL) {
        size++;
    }
    int max = size - 1;
    int min = 0;
    for (int i = max; i > 0; i = i / 2) {
        toBSTreeHelper(array, min, max, root);
    }
}

/*-----------------------------Private: toBSTreeHelper-------------------------
 * Pre: Takes in an array of pointers to NodeData that contains all of the data
 *      that will be entered into this BinTree. Takes in an int, min, that is
 *      the minimum index, and another int, max, that is the maximum index.
 *      Takes in a pointer reference to a Node, currentPtr, which is the Node
 *      currently being pointed to in this BinTree. **Assumes that this BinTree
 *      is already empty. **IF BINTREE IS NOT EMPTY THEN MEMORY LEAK.
 *
 * Post: Moves all of the data from array into this BinTree. The BinTree's data
 *      is added to where the data is balanced on the BinTree.
 *---------------------------------------------------------------------------*/
void BinTree::toBSTreeHelper(NodeData* array[], int min, int max
        , Node*& currentPtr) {
    if (currentPtr == NULL) {
        if (array[(min + max) / 2] != NULL) {
            currentPtr = new Node();
            currentPtr->data = array[(max + min) / 2];
            array[(max + min) / 2] = NULL;
            currentPtr->left = NULL;
            currentPtr->right = NULL;
        }
    } else {
        int rightMin = ((max + min) / 2) + 1;
        int leftMax = ((max + min) / 2) - 1;
        toBSTreeHelper(array, min, leftMax, currentPtr->left);
        toBSTreeHelper(array, rightMin, max, currentPtr->right);
    }
}



/*------------------------- displaySideways -----------------------------------
 * Pre: None.
 *
 * Post: Displays a binary tree as though you are viewing it from the side;
 *      hard coded displaying to standard output.BinTree remains unchanged.
 *----------------------------------------------------------------------------*/
 void BinTree::displaySideways() const {
    sideways(root, 0);
}

/*----------------------------Private: Sideways -------------------------------
 * Pre: Takes in a pointer to a Node, current, which is the current Node that
 *      is being pointed to. Takes in an int, level, which indicates what level
 *      the Node is at in the tree.
 *
 * Post: Prints out the BinTree sideways. The BinTree remains unchanged.
 * --------------------------------------------------------------------------*/
void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}


/* -------------------------------makeEmpty------------------------------------
 * Pre: None.
 *
 * Post: Deletes every Node in the tree along with its data. The BinTree
 *       becomes empty.
 *---------------------------------------------------------------------------*/
void BinTree::makeEmpty() {
    destroyTree(root);
    root = NULL;
}


/* --------------------------Private: destroyTree------------------------------
 * Pre: Takes in a pointer to a Node, currentPtr, which points to a Node in the
 *      BinTree.
 *
 * Post: Deletes every Node and its data in the BinTree. Leaves the tree empty
 *      afterwards.
 *---------------------------------------------------------------------------*/
void BinTree::destroyTree(Node* currentPtr) {
    if (currentPtr != NULL) {
        destroyTree(currentPtr->right);
        destroyTree(currentPtr->left);
        delete currentPtr->data;
        currentPtr->data = NULL;
        currentPtr->left = NULL;
        currentPtr->right = NULL;
        delete currentPtr;
    }
}


