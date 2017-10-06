#ifndef __TREE_H__
#define __TREE_H__

struct TreeNode;
typedef struct TreeNode* PtrToNode;
typedef PtrToNode Tree;

#define FT_FILE 1
#define FT_DIR  2

#define MAX_DEPTH 20

/* defined in tree.c */
extern Tree T_MakeEmpty(Tree root);
extern int T_PathMatch(char *path[], Tree r, Tree *matched);
extern int T_FindUnderDir(char *fname, int filetype, Tree parent, Tree *pre, Tree *node);
extern Tree T_Insert(char *fn, int ft, int fz, Tree parent);
extern Tree T_InsertAfterFind(char *fn, int ft, int fz, Tree parent, Tree pre);
extern Tree T_DeleteAfterFind(char *fn, Tree parent, Tree pre, Tree node);
extern int T_IsEmptyDir(Tree node);
extern void T_DumpNode(Tree node);
extern void ListCurDir(Tree root, int need_size);
extern void T_ListDir(Tree root);

/* defined in file_op.c */
extern void PrintPathFname(char *fn, char *path[], char *fname);
extern int T_MakeDir(char *fn, int fsize);
extern int T_MakeFile(char *fn, int fsize);
extern int T_RemoveDir(char *fn);
extern int T_RemoveFile(char *fn);
extern int T_ChangeCwd(char *fn);
extern void T_ShowCwd(void);
extern void T_ShowCwdFiles(void);
extern void T_ShowCwdFilesWithSize(void);
extern void T_DumpTree(void);
extern void T_DumpTreeWithSize(void);
extern void T_DestroyTree(void);

/**
 * 加入函数的声明
 * 消除警告:
 * warning: assignment makes pointer from integer without a cast
 */
char *strdup(const char *s);
char *strtok_r(char *str, const char *delim, char **saveptr);
#endif
