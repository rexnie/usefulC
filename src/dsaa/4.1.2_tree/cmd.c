#include "ds.h"
#include "cmd.h"
#include "tree.h"

/*#define DEBUG_PARSER*/

static cmd_tbl_t fs_cmd[] = {
	{ "mkdir", 3, do_mkdir, "mkdir path [fsize]\t\tcreate dir, default 1 if w/o fsize" },
	{ "touch", 3, do_touch, "touch path/fname [fsize]\t\tcreate file, \
				default 1 if w/o fsize" },
	{ "rmdir", 2, do_rmdir, "rmdir path\t\tsame as linux rmdir utility" },
	{ "rm", 2, do_rm, "rm file\t\tsame as linux rm utility" },
	{ "cd", 2, do_cd, "cd path\t\tchange current work directory" },
	{ "pwd", 1, do_pwd, "pwd\t\tshow current work directory" },
	{ "ls", 1, do_ls, "ls\t\tlist files under $PWD" },
	{ "ll", 1, do_ll, "ll\t\tlist file w/ fsize under $PWD" },
	{ "tree", 1, do_tree, "tree\t\tsame as linux tree utility" },
	{ "du", 1, do_du, "du\t\tsame as linux du utility" },
	{ "destroy", 1, do_destroy, "destroy\t\tdestroy tree, and free all nodes memory" },
	{ "quit", 1, do_quit, "quit\t\tquit the program" },
	{ "exit", 1, do_quit, "exit\t\tquit the program" },
	{ "help", 1, do_help, "help\t\tlist this help usage" },

};
#define SZ_CMD_TBL (sizeof(fs_cmd)/sizeof(fs_cmd[0]))

int do_mkdir(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	int fz = 1;
	char *endptr;

	if (argc == 3) {
		fz = (int) strtol(argv[2], &endptr, 10);
	}
	return T_MakeDir(argv[1], fz);
}

int do_touch(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	int fz = 1;
	char *endptr;

	if (argc == 3) {
		fz = (int) strtol(argv[2], &endptr, 10);
	}
	return T_MakeFile(argv[1], fz);
}

int do_rmdir(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	return T_RemoveDir(argv[1]);
}

int do_rm(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	return T_RemoveFile(argv[1]);
}

int do_cd(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	return T_ChangeCwd(argv[1]);
}

int do_pwd(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	T_ShowCwd();
	return 0;
}

int do_ls(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	T_ShowCwdFiles();
	return 0;
}

int do_ll(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	T_ShowCwdFilesWithSize();
	return 0;
}

int do_tree(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	T_DumpTree();
	return 0;
}

int do_du(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	T_DumpTreeWithSize();
	return 0;
}

int do_destroy(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	T_DestroyTree();
	return 0;
}
int do_quit(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	exit(0);
}

int do_help(struct cmd_tbl_s *tbl, int argc, char *argv[])
{
	cmd_tbl_t *cmdtp;
	int i;

	dbg("list all support commands:\n");
	for (i = 0, cmdtp=&fs_cmd[0]; i < SZ_CMD_TBL; i++, cmdtp++) {
		printf("%s\n", cmdtp->usage);
	}
	return 0;
}

static char console_buffer[CFG_CBSIZE];		/* console I/O buffer	*/
static char * delete_char (char *buffer, char *p, int *colp, int *np, int plen);
static char erase_seq[] = "\b \b";		/* erase sequence	*/
static char   tab_seq[] = "        ";		/* used to expand TABs	*/

cmd_tbl_t *find_cmd (const char *cmd)
{
	cmd_tbl_t *cmdtp;
	int i;

	for (i = 0, cmdtp=&fs_cmd[0]; i < SZ_CMD_TBL; i++, cmdtp++) {
		if (strcmp (cmd, cmdtp->name) == 0) {
			return cmdtp;	/* full match */
		}
	}

	return NULL;	/* not found or ambiguous command */
}

/**
 * 删除buffer中的一个字符
 * buffer: [in] char buffer
 * p: [in] current position in buffer
 * *colp: [out] collumn index
 * *np: [out] buffer index
 * plen: [in] len of prompt
 *
 */
static char *delete_char (char *buffer, char *p, int *colp, int *np, int plen)
{
	char *s;

	if (*np == 0) {
		return (p);
	}

	if (*(--p) == '\t') {			/* will retype the whole line	*/
		while (*colp > plen) {
			puts (erase_seq);
			(*colp)--;
		}
		for (s=buffer; s<p; ++s) {
			if (*s == '\t') {
				puts (tab_seq+((*colp) & 07));
				*colp += 8 - ((*colp) & 07);
			} else {
				++(*colp);
				putchar (*s);
			}
		}
	} else {
		puts (erase_seq);
		(*colp)--;
	}
	(*np)--;
	return (p);
}

int parse_line (char *line, char *argv[])
{
	int nargs = 0;

#ifdef DEBUG_PARSER
	dbg ("parse_line: \"%s\"\n", line);
#endif
	while (nargs < CFG_MAXARGS) {

		/* skip any white space */
		while ((*line == ' ') || (*line == '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
			dbg ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		argv[nargs++] = line;	/* begin of argument string	*/

		/* find end of string */
		while (*line && (*line != ' ') && (*line != '\t')) {
			++line;
		}

		if (*line == '\0') {	/* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
			dbg ("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		*line++ = '\0';		/* terminate current arg	 */
	}

	err ("** Too many args (max. %d) **\n", CFG_MAXARGS);

#ifdef DEBUG_PARSER
	err ("parse_line: nargs=%d\n", nargs);
#endif
	return (nargs);
}

/*
 * Prompt for input and read a line.
 * Return:	number of read characters
 *		-1 if break
 */
int readline (const char *const prompt)
{
	char   *p = console_buffer;
	int	n = 0;				/* buffer index		*/
	int	plen = 0;			/* prompt length	*/
	int	col;				/* output column cnt	*/
	char	c;

	/* print prompt */
	if (prompt) {
		plen = strlen (prompt);
		/*puts (prompt);*/
		printf("%s", prompt);
	}
	col = plen;

	for (;;) {
		c = getchar();

		/*
		 * Special character handling
		 */
		switch (c) {
		case '\r':				/* Enter		*/
		case '\n':
			*p = '\0';
			/*puts ("\r\n");*/
			return (p - console_buffer);

		case '\0':				/* nul			*/
			continue;

		case 0x03:				/* ^C - break		*/
			console_buffer[0] = '\0';	/* discard input */
			return (-1);

		case 0x15:				/* ^U - erase line	*/
			while (col > plen) {
				puts (erase_seq);
				--col;
			}
			p = console_buffer;
			n = 0;
			continue;

		case 0x17:				/* ^W - erase word 	*/
			p=delete_char(console_buffer, p, &col, &n, plen);
			while ((n > 0) && (*p != ' ')) {
				p=delete_char(console_buffer, p, &col, &n, plen);
			}
			continue;

		case 0x08:				/* ^H  - backspace	*/
		case 0x7F:				/* DEL - backspace	*/
			p=delete_char(console_buffer, p, &col, &n, plen);
			continue;

		default:
			/*
			 * Must be a normal character then
			 */
			if (n < CFG_CBSIZE-2) {
				if (c == '\t') {	/* expand TABs		*/
					puts (tab_seq+(col&07)); /* 跳到下一个第8个字符 */
					col += 8 - (col&07);
				} else {
					++col;		/* echo input		*/
					/*putchar (c);*/
				}
				*p++ = c;
				++n;
			} else {			/* Buffer full		*/
				putchar ('\a');
			}
		}
	}
}

/****************************************************************************
 * returns:
 *	1  - command executed
 *	0  - command executed but not repeatable, interrupted commands are
 *	     always considered not repeatable
 *	-1 - not executed (unrecognized, bootd recursion or too many args)
 *           (If cmd is NULL or "" or longer than CFG_CBSIZE-1 it is
 *           considered unrecognized)
 */
int run_command (const char *cmd)
{
	cmd_tbl_t *cmdtp;
	char cmdbuf[CFG_CBSIZE];	/* working copy of cmd		*/
	char *token;			/* start of token in cmdbuf	*/
	char *sep;			/* end of token (separator) in cmdbuf */
	char *str = cmdbuf;
	char *argv[CFG_MAXARGS + 1];	/* NULL terminated	*/
	int argc, inquotes;
	int rc = 0;

#ifdef DEBUG_PARSER
	dbg ("[RUN_COMMAND] cmd[%p]=\"", cmd);
	puts (cmd ? cmd : "NULL");	/* use puts - string may be loooong */
	puts ("\"\n");
#endif

	if (!cmd || !*cmd) {
		return -1;	/* empty command */
	}

	if (strlen(cmd) >= CFG_CBSIZE) {
		err("## Command too long!\n");
		return -1;
	}

	strcpy (cmdbuf, cmd);

#ifdef DEBUG_PARSER
	dbg ("[PROCESS_SEPARATORS] %s\n", cmd);
#endif
	while (*str) {

		/*
		 * Find separator, or string end
		 * Allow simple escape of ';' by writing "\;"
		 */
		for (inquotes = 0, sep = str; *sep; sep++) {
			if ((*sep=='\'') &&
			    (*(sep-1) != '\\'))
				inquotes=!inquotes; /* 找到了一个引号' */

			if (!inquotes &&
			    (*sep == ';') &&	/* separator		*/
			    ( sep != str) &&	/* past string start	*/
			    (*(sep-1) != '\\'))	/* and NOT escaped	*/
				break;
		}

		/*
		 * Limit the token to data between separators
		 */
		token = str;
		if (*sep) {
			str = sep + 1;	/* start of command for next pass */
			*sep = '\0';
		}
		else
			str = sep;	/* no more commands for next pass */
#ifdef DEBUG_PARSER
		dbg ("token: \"%s\"\n", token);
#endif

		/* Extract arguments */
		if ((argc = parse_line (token, argv)) == 0) {
			rc = -1;	/* no command at all */
			continue;
		}

		/* Look up command in command table */
		if ((cmdtp = find_cmd(argv[0])) == NULL) {
			dbg ("Unknown command '%s' - try 'help'\n", argv[0]);
			rc = -1;	/* give up after bad command */
			continue;
		}

		/* found - check max args */
		if (argc > cmdtp->maxargs) {
			dbg ("Usage:\n%s\n", cmdtp->usage);
			rc = -1;
			continue;
		}

		/* OK - call function to do the command */
		if ((cmdtp->cmd) (cmdtp, argc, argv) != 0) {
			rc = -1;
		}
	}

	return rc < 0 ? -1 : 0;
}

void InitTreeFromFile(void)
{
	FILE *fp = NULL;
	char *p;
	if ((fp = fopen("init.txt", "r")) == NULL) {
		perror("open init.txt fail");
		return;
	}

	while (fgets(console_buffer, CFG_CBSIZE, fp) != NULL) {
		p = console_buffer;
		/* remove '\n' in the end-of-line */
		while (*p != '\0') {
			if (*p == '\n' && *(p+1) == '\0')
				*p = '\0';
			p++;
		}
		if (!strlen(console_buffer))
			continue;
		if (run_command (console_buffer) < 0) {
			err("run cmd \"%s\" err\n", console_buffer);
			break;
		}
	}
	fclose(fp);
}

int main(void)
{
	int len;
	int rc = 0;

	InitTreeFromFile();
	for (;;) {
		len = readline (CFG_PROMPT);

		if (len == -1) {
			puts ("<INTERRUPT>\n");
			break;
		} else if (len > 1)
			rc = run_command (console_buffer);

		if (rc < 0)
			dbg("run_command ret -1\n");
		console_buffer[0] = 0; /* clear buf */
	}
	return 0;
}
