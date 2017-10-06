#include "ds.h"
#include "tree.h"

static Tree g_root = NULL;
static Tree g_cur = NULL;
static char *g_cwd[MAX_DEPTH] = { NULL, };

static Tree T_GetRootNode(void)
{
	return g_root;
}

static char **T_GetCwd(void)
{
	return g_cwd;
}

static Tree T_GetCwdNode(void)
{
	return g_cur;
}

static int IsAbsolutePath(const char *fn)
{
	if (fn == NULL) {
		err("fn is null\n");
		return -1;
	}
	if (fn[0] == '/')
		return 1;
	else
		return 0;
}

static Tree T_GetStartNode(const char *fn)
{
	Tree root = NULL;

	if (IsAbsolutePath(fn) == 1) { /* 绝对路径 */
		root = T_GetRootNode();
	} else { /* 相对路径 */
		root = T_GetCwdNode() != NULL ? T_GetCwdNode() : T_GetRootNode();
	}
	return root;
}

static void T_ClearAfterDeleteRoot(void)
{
	char **t;
	g_root = g_cur = NULL;
	t = g_cwd;
	while (*t != NULL) {
		free(*t);
		*t = NULL;
		t++;
	}
}


/**
 * 分离fn为path/fname两部分
 * fn: [in] 是被split的文件或目录的字符串，支持绝对/相对路径
 * path: [out] 目录的path部分
 * fname: [out] 文件名的部分
 * all_path: [in] =1时,split为全路径，*fname==NULL,
 *                =0时,split为path/fname两部分
 * 返回:
 *   内部heap alloc的memory, 保存着fn
 *   NULL 表示split失败
 *
 * all_path == 1:
 * fn="/home/rex" ==>path={ "/", "home", "rex" }, *fname=NULL
 * fn="home/rex/" ==> path={ "home", "rex" }, *fname=NULL
 *
 * all_path == 0:
 * fn="/home/rex" ==>path={ "/", "home" }, *fname="rex"
 * fn="home/rex/" ==> path={ "home" }, *fname="rex"
 * fn="/home/rex/a.c" ==>path={ "/", "home","rex"}, fname="a.c"
 */
static char *path_split(char *fn, char *path[], char **fname, int all_path)
{
	int i = 0;
	char *q = NULL;
	char *savep;
	char *delim = "/";

	if (path == NULL) {
		err("should alloc mem for path\n");
		return NULL;
	}

	if (fn == NULL) {
		err("fn must be not null\n");
		return NULL;
	}

	if ((q = (char *) malloc(sizeof(char) * (strlen(fn) + 1))) == NULL) {
		err("no mem\n");
		return NULL;
	}

	strcpy(q, fn);
	if (fn[0] == '/')
		path[i++] = strdup(delim);
	path[i] = strtok_r(q, delim, &savep);
	while (path[i] != NULL) {
		i++;
		path[i] = strtok_r(NULL, delim, &savep);
	}
	if (!all_path) {
		i--;
		if (i == 0 && fn[i] == '/') { /* fn == "/" */
			*fname = q;
			free(path[0]);
			path[0] = NULL;
		} else {
			*fname = path[i];
			path[i] = NULL;
		}
	} else
		*fname = NULL;
	return q;
}

void PrintPathFname(char *fn, char *path[], char *fname)
{
	int i = 0;
	dbg("after path split, origin fn=%s\n", fn);
	if (path == NULL) {
		err("should alloc mem for path\n");
		return;
	}
	while(path[i] != NULL) {
		dbg("path %d: %s\n", i, path[i]);
		i++;
	}
	if (i == 0)
		dbg("path[0] is null\n");
	if (fname != NULL)
		dbg("fname=%s\n", fname);
	else
		dbg("fname is null\n");
}

static char *
T_PathSplitAndMatch(char *fn, char *path[], char **fname, int all_path, Tree *matched)
{
	char *buf = NULL;
	char *path2[MAX_DEPTH] = { NULL, };
	char **dst = path2;
	char **src, *pre = NULL;

	if (path == NULL) {
		err("should alloc mem for path\n");
		return NULL;
	}

	if (fn == NULL) {
		err("fn must be not null\n");
		return NULL;
	}

	if ((buf = path_split(fn, path, fname, all_path)) == NULL) {
		err("path split return null\n");
		return NULL;
	}

	if (IsAbsolutePath(fn) == 0) {
		src = T_GetCwd();
		while (*src != NULL) {
			pre = *src;
			src++;
		}
		if (pre != NULL)
			*dst++ = pre;

		src = path;
		while (*src != NULL)
			*dst++ = *src++;
		*dst = NULL;
		/*PrintPathFname(fn, path2, *fname);*/
	}

	if (T_PathMatch(IsAbsolutePath(fn) == 0 ? path2 : path, 
				T_GetStartNode(fn), matched) == 0) {
		err("path not match\n");
		goto quit;
	}

	return buf;
quit:
	if (buf != NULL)
		free(buf);
	return NULL;
}

/**
 * 返回值看T_FindUnderDir()
 */
static int T_PathSplitMatchAndFind(char *fn, char *path[], char **fname, int ftype, char **buf,
		Tree *matched, Tree *pre, Tree *node)
{
	if ((*buf = T_PathSplitAndMatch(fn, path, fname, 0, matched)) == NULL) {
		err("path split or match fail\n");
		return -1;
	}
	return T_FindUnderDir(*fname, ftype, *matched, pre, node);
}

/**
 * 往树中插入一个目录fn, 大小为fsize
 * 一次只处理一个节点，所以只有父目录存在的情况下，插入才成功
 * 返回 0 插入成功, -1 失败
 */
int T_MakeDir(char *fn, int fsize)
{
	int ret = -1;
	char *fname;
	char *buf = NULL;
	Tree pre = NULL, node = NULL, matched = NULL;
	Tree p = NULL;
	char *path[MAX_DEPTH] = { NULL, };

	ret = T_PathSplitMatchAndFind(fn, path, &fname, FT_DIR, &buf, &matched, &pre, &node);
	if (ret == 1) {
		err("dir=%s exist\n", fname);
		ret = -1;
		goto quit;
	} else if (ret == 0) {
		err("dir=%s exist with different file type\n", fname);
		ret = -1;
		goto quit;
	} else if (ret == -1) {
		err("parament err\n");
		ret = -1;
		goto quit;
	}

	/* not find */
	p = T_InsertAfterFind(fname, FT_DIR, fsize, matched, pre);

	if (p != NULL) { /* first node is root */
		if (matched == NULL) {
			dbg("insert as root node\n");
			g_root = p;
			g_cur = p;
			g_cwd[0] = strdup("/");
			g_cwd[1] = NULL;
		}
		ret = 0;
	} else {
		err("insert node fail\n");
		ret = -1;
	}
quit:
	if (buf != NULL)
		free(buf);
	return ret;
}

int T_MakeFile(char *fn, int fsize)
{
	int ret = -1;
	char *fname;
	char *buf = NULL;
	Tree pre = NULL, node = NULL, matched = NULL;
	Tree p = NULL;
	char *path[MAX_DEPTH] = { NULL, };

	ret = T_PathSplitMatchAndFind(fn, path, &fname, FT_FILE, &buf, &matched, &pre, &node);
	if (ret == 1) {
		err("dir=%s exist\n", fname);
		ret = -1;
		goto quit;
	} else if (ret == 0) {
		err("dir=%s exist with different file type\n", fname);
		ret = -1;
		goto quit;
	} else if (ret == -1) {
		err("parament err\n");
		ret = -1;
		goto quit;
	}

	p = T_InsertAfterFind(fname, FT_FILE, fsize, matched, pre);
	if (p == NULL) {
		err("insert node fail\n");
		ret = -1;
	} else
		ret = 0;
quit:
	if (buf != NULL)
		free(buf);
	return ret;
}

int T_RemoveDir(char *fn)
{
	int ret = -1;
	char *fname;
	char *buf = NULL;
	Tree pre = NULL, node = NULL, matched = NULL;
	Tree p = NULL;
	char *path[MAX_DEPTH] = { NULL, };

	if (fn == NULL) {
		err("fn is null\n");
		return -1;
	}

	if (fn[0] == '/' && fn[1] == '\0') {
		if (T_GetRootNode() != NULL) {
			node = T_GetRootNode();
			fname = "/";
			goto found;
		} else {
			err("delete root node, but it is not empty\n");
			return -1;
		}
	}

	ret = T_PathSplitMatchAndFind(fn, path, &fname, FT_DIR, &buf, &matched, &pre, &node);
	if (ret == 0) {
		err("dir=%s exist with different file type\n", fname);
		ret = -1;
		goto quit;
	} else if (ret == -1) {
		err("parament err\n");
		ret = -1;
		goto quit;
	} else if (ret == -2) {
		err("dir=%s not found\n", fname);
		ret = -1;
		goto quit;
	}

found:
	/* find it */
	if (T_IsEmptyDir(node) != 1) {
		err("dir=%s is not empty\n", fname);
		ret = -1;
		goto quit;
	}

	if (T_DeleteAfterFind(fname, matched, pre, node) == NULL) {
		dbg("delete the root successfully\n");
		T_ClearAfterDeleteRoot();
	}
	ret = 0;

quit:
	if (buf != NULL)
		free(buf);
	return ret;
}

int T_RemoveFile(char *fn)
{
	int ret = -1;
	char *fname;
	char *buf = NULL;
	Tree pre = NULL, node = NULL, matched = NULL;
	char *path[MAX_DEPTH] = { NULL, };

	ret = T_PathSplitMatchAndFind(fn, path, &fname, FT_FILE, &buf, &matched, &pre, &node);
	if (ret == 0) {
		err("file=%s exist with different file type\n", fname);
		ret = -1;
		goto quit;
	} else if (ret == -1) {
		err("parament err\n");
		ret = -1;
		goto quit;
	} else if (ret == -2) {
		err("fname=%s not found\n", fname);
		ret = -1;
		goto quit;
	}

	/* find it */
	T_DeleteAfterFind(fname, matched, pre, node);
	ret = 0;
quit:
	if (buf != NULL)
		free(buf);
	return ret;
}

int T_ChangeCwd(char *fn)
{
	char *buf = NULL;
	char *fname;
	Tree matched = NULL;
	char *path[MAX_DEPTH] = { NULL, };
	char **dst = NULL, **src = NULL;
	int ret = -1;

	if ((buf = T_PathSplitAndMatch(fn, path, &fname, 1, &matched)) == NULL) {
		err("path not match\n");
	} else {
		/*T_DumpNode(matched);*/
		g_cur = matched;
		src = path;
		dst = g_cwd;
		if (IsAbsolutePath(fn) == 0)
			while (*dst != NULL)
				dst++;
		while (*src != NULL)
			*dst++ = strdup(*src++);
		*dst = NULL;
		ret = 0;
	}

	if (buf != NULL)
		free(buf);
	return ret;
}

void T_ShowCwd(void)
{
	char **p = T_GetCwd();
	if (*p == NULL) {
		dbg("it is a empty tree\n");
		return;
	} else if (**p == '/')
		printf("%s", *p);
	p++;
	while (*p != NULL) {
		printf("%s/", *p);
		p++;
	}
	printf("\n");
}

void T_ShowCwdFiles(void)
{
	ListCurDir(T_GetCwdNode(), 0);
}

void T_ShowCwdFilesWithSize(void)
{
	ListCurDir(T_GetCwdNode(), 1);
}

void T_DumpTree(void)
{
	T_ListDir(T_GetRootNode());
}

void T_DumpTreeWithSize(void)
{
	T_ListDirWithSize(T_GetRootNode());
}

void T_DestroyTree(void)
{
	T_MakeEmpty(T_GetRootNode());
	T_ClearAfterDeleteRoot();
}
