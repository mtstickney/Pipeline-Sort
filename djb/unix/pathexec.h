#ifndef PATHEXEC_H
#define PATHEXEC_H

extern void pathexec_run(const char *file,char *argv[],char *envp[]);
extern int pathexec_env(const char *,const char *);
extern void pathexec(char *argv[]);

#endif
