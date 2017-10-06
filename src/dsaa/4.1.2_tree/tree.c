#include "tree.h"
#include "ds.h"

struct TreeNode {
	char *name;
	int type;
	int size;
	PtrToNode firstChild;
	PtrToNode nextSibling;
};

Tree T_MakeEmpty(Tree root)
{
	if (root != NULL) {
		T_MakeEmpty(root->firstChild);
		T_MakeEmpty(root->nextSibling);
		free(root->name);
		free(root);
	}
	return root;
}

/**
 * 匹配文件/目录的路径部分,路径可相对路径也可绝对路径
 * path: [in] path to be match
 * root: [in] root node to start matching
 * mathed: [out] 匹配的路径部分
 * 1: match, 0; not match
 */
int T_PathMatch(char *path[], Tree root, Tree *matched)
{
	int depth = 0;
	Tree p = root;
	*matched = p;

	if (path == NULL) {
		err("path not alloc mem\n");
		return 0;
	}

	if (path[0] == NULL) {
		dbg("path[0] is NULL, matched\n");
		return 1;
	}
#if 0
	PrintPathFname(NULL, path, NULL);
	if (root == NULL)
		dbg("root is null\n");
	else
		dbg("root->name=%s\n", root->name);
#endif
	while (path[depth] != NULL) {
		if (p == NULL) {
			dbg("path not match, depth=%d\n", depth);
			return 0;
		}
		/* dbg("p->name=%s,path=%s,type=%d\n", p->name, path[depth],p->type); */
		while (p != NULL && strcmp(p->name, path[depth]))
			p = p->nextSibling;

		if (p != NULL && p->type != FT_DIR) { /* name match */
			dbg("path name %s conflict with file\n", path[depth]);
			return 0;
		} else if (p == NULL) {
			dbg("path not match, depth=%d\n", depth);
			return 0;
		}

		*matched = p;
		p = p->firstChild; /* 进入下一级目录 */
		depth++;
	}
	return 1;
}

/**
 * 在parent节点下找名为fname, 文件类型是filetype的文件
 * fname: [in] 要找的文件/目录名
 * filetype: [in] 要找的文件类型FT_FILE, or FT_DIR
 * parent: [in] 父节点的指针
 * pre: [out]
 * node: [out]
 *   如果找到，node指向找到的那个节点，pre指向它的前置节点
 *   如果没找到
 *     如果有文件名一样但文件类型不匹配的，node指向该节点,pre指向它的前置节点
 *     否则node指向null, pre为它的前置，即如果后续执行插入操作，则pre是插入节点的前置
 * 返回值:
 * 1: 找到, pre/node有效
 * 0: 找到同名不同类型的文件，pre/node有效
 * -1: 参数错误, *pre=*node=NULL
 * -2: 没找到, pre/node有效
 */
int T_FindUnderDir(char *fname, int filetype, Tree parent, Tree *pre, Tree *node)
{
	Tree p = NULL;
	*pre = parent;
	*node = NULL;

	if (fname == NULL) {
		err("fname can't be null\n");
		return -1;
	}

	if (parent == NULL) {
		dbg("parent is null, it is a empty tree\n");
		return -2;
	}
	p = parent->firstChild;

	while (p != NULL && strcmp(p->name, fname)) {
		*pre = p;
		p = p->nextSibling;
	}

	*node = p;
	if (p != NULL && p->type != filetype) { /* name match */
		dbg("found fname=%s, but filetype not match\n", fname);
		return 0;
	} else if (p == NULL) {
		dbg("fname=%s not found\n", fname);
		return -2;
	}
	/*dbg("found fname=%s, p=%p\n", fname, p);*/
	return 1;
}

/**
 * 在确保parent下无文件名是fn, 文件类型是ft的文件时，插入一个节点
 * fn: [in] file name to insert
 * ft: [in] file type
 * fz: [in] file size
 * parent: [in] new node's parent
 * 插入成功返回新插入的节点，否则返回NULL
 */
Tree T_Insert(char *fn, int ft, int fz, Tree parent)
{
	Tree p = NULL;
	Tree tmp = NULL;

	if (fn == NULL) {
		err("fn can't be null\n");
		return NULL;
	}

	if (parent == NULL && (fn[0] != '/' || fn[1] != '\0')) {
		err("parent is null, fn should be /.\n");
		return NULL;
	}

	if ((p = malloc(sizeof(struct TreeNode))) == NULL) {
		err("no memory, insert fail\n");
		return NULL;
	}

	p->name = strdup(fn);
	p->type = ft;
	p->size = fz;
	p->firstChild = p->nextSibling = NULL;

	if (parent == NULL) {
		/*dbg("it is root node\n");*/
	} else if (parent->firstChild == NULL) {
		parent->firstChild = p;
	} else {
		tmp = parent->firstChild;
		while (tmp->nextSibling != NULL)
			tmp = tmp->nextSibling;
		tmp->nextSibling = p;
	}
	return p;
}

/**
 * 在T_FindUnderDir()返回-2时，插入新节点
 * fn: [in] file name to insert
 * ft: [in] file type
 * fz: [in] file size
 * parent: [in] new node's parent 
 * pre: [in] 新节点的前置
 * 插入成功返回新插入的节点，否则返回NULL
 */
Tree T_InsertAfterFind(char *fn, int ft, int fz, Tree parent, Tree pre)
{
	Tree p = NULL;
	if (fn == NULL) {
		err("fn can't be null\n");
		return NULL;
	}

	if (parent == NULL && (fn[0] != '/' || fn[1] != '\0')) {
		err("parent is null, fn should be /.\n");
		return NULL;
	}

	if ((p = malloc(sizeof(struct TreeNode))) == NULL) {
		err("no memory, insert fail\n");
		return NULL;
	}

	p->name = strdup(fn);
	p->type = ft;
	p->size = fz;
	p->firstChild = p->nextSibling = NULL;
	if (parent == NULL) { /* null tree */
		/*dbg("it is root node\n"); */
	} else if (parent->firstChild == NULL) {
		parent->firstChild = p;
	} else {
		pre->nextSibling = p;
	}
	return p;
}

/**
 * 在T_FindUnderDir返回1的情况下，删除节点
 * 返回被删除节点的父节点
 */
Tree T_DeleteAfterFind(char *fn, Tree parent, Tree pre, Tree node)
{
	Tree p = NULL;
	if (strcmp(node->name, fn)) {
		err("parameter err\n");
		return parent;
	}

	if (parent == NULL && (fn[0] != '/' || fn[1] != '\0')) {
		err("parent is null, fn should be /.\n");
		return parent;
	}
	if (parent == NULL) {
		dbg("delete root node\n");
	} else if (parent->firstChild == node) {
		parent->firstChild = node->nextSibling;
	} else {
		pre->nextSibling = node->nextSibling;
	}
	free(node->name);
	free(node);
	return parent;
}

int T_IsEmptyDir(Tree node)
{
	if (node == NULL) {
		err("node is null\n");
		return -1;
	}
	if (node->firstChild == NULL && node->type == FT_DIR)
		return 1;
	else
		return 0;
}

void T_DumpNode(Tree node)
{
	if (node != NULL)
		dbg("name=%s,type=%d,size=%d\n", node->name, node->type, node->size);
	else
		dbg("node is null\n");
}

static void PrintName(Tree p, int depth)
{
	int i;
	for (i = 0; i < depth; i++)
		printf("\t");
	if (p->type == FT_DIR)
		printf("%s*\n", p->name);
	else
		printf("%s\n", p->name);
}

void ListCurDir(Tree root, int need_size)
{
	if (root != NULL) {
		root = root->firstChild;
		while (root != NULL) {
			if (root->type == FT_DIR)
				if (need_size)
					printf("%-20s*%20d\n", root->name, root->size);
				else
					printf("%s*\n", root->name);
			else
				if (need_size)
					printf("%-20s %20d\n", root->name, root->size);
				else
					printf("%s \n", root->name);
			root = root->nextSibling;
		}
	}
}

/**
 * 打印目录树
 * TODO: 是否可以非递归实现
 */
static void ListDir(Tree root, int depth)
{
	if (root != NULL) {
		PrintName(root, depth);
		if (root->type == FT_DIR) {
			Tree p = root->firstChild;
			while (p != NULL) {
				ListDir(p, depth + 1);
				p = p->nextSibling;
			}
		}
	}
}

void T_ListDir(Tree root)
{
	dbg("List tree nodes:\n");
	ListDir(root, 0);
}

static void PrintNameSize(Tree p, int depth, int sz)
{
	int i;
	for (i = 0; i < depth; i++)
		printf("\t");
	if (p->type == FT_DIR)
		printf("%s*  %d\n", p->name, sz);
	else
		printf("%s   %d\n", p->name, sz);
}

int T_FileSize(Tree root)
{
	int size = 0;

	if (root != NULL) {
		size = root->size;
		if (root->type == FT_DIR) {
			Tree p = root->firstChild;
			while (p != NULL) {
				size += T_FileSize(p);
				p = p->nextSibling;
			}
		}

	}
	return size;
}

static void ListDirWithSize(Tree root, int depth)
{
	if (root != NULL) {
		PrintNameSize(root, depth, T_FileSize(root));
		if (root->type == FT_DIR) {
			Tree p = root->firstChild;
			while (p != NULL) {
				ListDirWithSize(p, depth + 1);
				p = p->nextSibling;
			}
		}
	}
}

int T_ListDirWithSize(Tree root)
{
	dbg("List tree nodes with size:\n");
	ListDirWithSize(root, 0);
}
