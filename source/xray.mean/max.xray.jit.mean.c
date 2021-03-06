/*
	xray.jit.mean
	Wesley Smith
	wesley.hoke@gmail.com

	last modified: 12-7-2006
*/

#include "jit.common.h"
#include "max.jit.mop.h"

typedef struct _max_xray_jit_mean
{
	t_object			ob;
	void				*obex;
	void 				*minout;
	void 				*meanout;
	void 				*maxout;
	t_atom				*av;
} t_max_xray_jit_mean;

t_jit_err xray_jit_mean_init(void);

void *max_xray_jit_mean_new(t_symbol *s, long argc, t_atom *argv);
void max_xray_jit_mean_free(t_max_xray_jit_mean *x);
void max_xray_jit_mean_assist(t_max_xray_jit_mean *x, void *b, long m, long a, char *s);
void max_xray_jit_mean_bang(t_max_xray_jit_mean *x);
void max_xray_jit_mean_mproc(t_max_xray_jit_mean *x, void *mop);
void *max_xray_jit_mean_class;

void C74_EXPORT main(void)
{
	void *p,*q;

	xray_jit_mean_init();
	setup((t_messlist **)&max_xray_jit_mean_class, max_xray_jit_mean_new, (method)max_xray_jit_mean_free, (short)sizeof(t_max_xray_jit_mean),
		0L, A_GIMME, 0);

	p = max_jit_classex_setup(calcoffset(t_max_xray_jit_mean,obex));
	q = jit_class_findbyname(gensym("xray_jit_mean"));
    max_jit_classex_mop_wrap(p,q,0);
    max_jit_classex_standard_wrap(p,q,0);
 	addmess((method)max_jit_mop_assist, "assist", A_CANT,0);
}



void max_xray_jit_mean_free(t_max_xray_jit_mean *x)
{
	max_jit_mop_free(x);
	jit_object_free(max_jit_obex_jitob_get(x));
	max_jit_obex_free(x);
}

void *max_xray_jit_mean_new(t_symbol *s, long argc, t_atom *argv)
{
	t_max_xray_jit_mean *x;
	void *o;

	if (x=(t_max_xray_jit_mean *)max_jit_obex_new(max_xray_jit_mean_class,gensym("xray_jit_mean"))) {
		if (o=jit_object_new(gensym("xray_jit_mean"))) {
			max_jit_mop_setup_simple(x,o,argc,argv);
			max_jit_attr_args(x,argc,argv);
		} else {
			error("xray.jit.mean: could not allocate object");
			freeobject((t_object *)x);
		}
	}
	return (x);
}

