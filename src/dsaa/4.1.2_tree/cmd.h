#ifndef _CMD_H
#define _CMD_H 1

#define	CFG_PROMPT		"=>"		/* Monitor Command Prompt	*/
#define	CFG_CBSIZE		256		/* Console I/O Buffer Size	*/
#define	CFG_MAXARGS		16		/* max number of command args	*/

struct cmd_tbl_s {
	char		*name;		/* Command Name			*/
	int		maxargs;	/* maximum number of arguments	*/
					/* Implementation function	*/
	int		(*cmd)(struct cmd_tbl_s *, int, char *[]);
	char		*usage;		/* Usage message	(short)	*/
};

typedef struct cmd_tbl_s cmd_tbl_t;

cmd_tbl_t *find_cmd(const char *cmd);

extern int do_mkdir(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_touch(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_rmdir(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_rm(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_cd(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_pwd(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_ls(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_ll(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_tree(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_preorder_non_recursion(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_postorder_non_recursion(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_du(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_du2(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_destroy(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_quit(struct cmd_tbl_s *tbl, int argc, char *argv[]);
extern int do_help(struct cmd_tbl_s *tbl, int argc, char *argv[]);;
#endif
