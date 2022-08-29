struct treenode {
   int label;		/* terminal symbol, or production rule # */
   int nkids;		/* 0 for tokens (tree leaves)i*/
   struct treenode *kids[7]; /* sized for muth.y */
   //struct token lexinfo;
};

typedef struct treenode *TreePtr;
