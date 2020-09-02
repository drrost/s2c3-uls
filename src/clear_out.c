#include "uls.h"

void mx_clear_out(t_out *out) {
  if (out->gid != NULL) {
    mx_strdel(&out->gid);
    out->gid = NULL;
  }
  if (out->size != NULL) {
    mx_strdel(&out->size);
    out->size = NULL; 
  }
  if (out->nlink != NULL) {
    mx_strdel(&out->nlink);
    out->nlink = NULL;
  }
  if (out->sblocks != NULL) {
    mx_strdel(&out->sblocks);
    out->sblocks = NULL;
  }
  if (out->name != NULL) {
    mx_strdel(&out->name);
    out->name = NULL;
  }
}
