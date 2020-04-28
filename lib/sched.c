#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.14 ***/
void sched_yield(void)
{
    //return;
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    //printf("in yield!");return;
    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`, 
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     * 
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
    struct Env *e = curenv;
    if (count != 0 && e->env_status != ENV_RUNNABLE) {
        count = 0;
    }
    while (count == 0) {
        if (LIST_EMPTY(&env_sched_list[point])) {
            point = 1 - point;
        }
        if (LIST_EMPTY(&env_sched_list[point])) {
            //continue;//return;
            panic("haha! You have no runnable env!");
        }
        //while (!LIST_EMPTY(&env_sched_list[point])) {
            e = LIST_FIRST(&env_sched_list[point]);
            if (e->env_status == ENV_RUNNABLE) {
                count = e->env_pri;
                LIST_REMOVE(e, env_sched_link);
                LIST_INSERT_HEAD(&env_sched_list[1 - point], e, env_sched_link);
                break;
            } else if (e->env_status == ENV_FREE) {
                LIST_REMOVE(e, env_sched_link);
            } else {
                LIST_REMOVE(e, env_sched_link);
                LIST_INSERT_HEAD(&env_sched_list[1 - point], e, env_sched_link);
            }
        //}
        //printf("yield: inside! now count: %d\n",count);
    }
    //printf("yield: outside!\n");
    //printf("yield: id:%d pid:%d status:%d pgdir:0x%x\n",e->env_id, e->env_parent_id, e->env_status, e->env_pgdir);
    count--;
    assert(e!=NULL);
    env_run(e);
    /*
    static int cur_lasttime = 1;
	static int cur_head_index = 0;
	struct Env *next_env;
	int now_have = 0;
	cur_lasttime--;
    
	if (cur_lasttime <= 0 || curenv == NULL || curenv->env_status != ENV_RUNNABLE)
	{
		now_have = 0;
		while(1)
		{
			if (LIST_EMPTY(&env_sched_list[cur_head_index]))
			{
				cur_head_index = !cur_head_index;
				break;
			}
			next_env = LIST_FIRST(&env_sched_list[cur_head_index]);
			if (next_env->env_status == ENV_RUNNABLE)
			{
				now_have = 1;
				break;
			}
			LIST_REMOVE(next_env, env_sched_link);
			LIST_INSERT_HEAD(&env_sched_list[!cur_head_index], next_env, env_sched_link);
		}
		if (!now_have)
		{
			while (1)
			{
				if (LIST_EMPTY(&env_sched_list[cur_head_index]))
				{
					panic("^^^^^^No env is RUNNABLE!^^^^^^");
				}
				next_env = LIST_FIRST(&env_sched_list[cur_head_index]);
				if (next_env->env_status == ENV_RUNNABLE)
				{
					now_have = 1;
					break;
				}
				LIST_REMOVE(next_env, env_sched_link);
				LIST_INSERT_HEAD(&env_sched_list[!cur_head_index], next_env, env_sched_link);
			}
		}
		LIST_REMOVE(next_env, env_sched_link);
		LIST_INSERT_HEAD(&env_sched_list[!cur_head_index], next_env, env_sched_link);
		cur_lasttime = next_env->env_pri;
        printf("inside! pc:0x%x, epc:0x%x\n",next_env->env_tf.pc, next_env->env_tf.cp0_epc);
		env_run(next_env);
		panic("^^^^^^sched yield jump faild^^^^^^");
	}
    printf("pc:0x%x, epc:0x%x\n",next_env->env_tf.pc, next_env->env_tf.cp0_epc);
	env_run(curenv);
	panic("^^^^^^sched yield reached end^^^^^^");*/
}

