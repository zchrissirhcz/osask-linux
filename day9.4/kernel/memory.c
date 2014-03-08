/*
 * ==================================================
 *
 *       Filename:  memory.c
 *
 *    Description:  
 *
 *        Version:  0.01
 *        Created:  2014年03月07日 星期五 21时02分32秒
 *         Author:  ChrisZZ, zchrissirhcz@163.com
 *        Company:  ZJUT
 *
 * ==================================================
 */
#include <header.h>

unsigned int memtest(unsigned int start, unsigned int end){
	char flg486 = 0;
	unsigned int eflg, cr0, i;
	eflg = io_load_eflags();
	eflg |= EFLAGS_AC_BIT;
	io_store_eflags(eflg);
	eflg = io_load_eflags();
	if((eflg & EFLAGS_AC_BIT)!=0){
		flg486=1;
	}
	eflg &= ~EFLAGS_AC_BIT;
	io_store_eflags(eflg);

	if(flg486!=0){
		cr0 = load_cr0();
		cr0 |= CR0_CACHE_DISABLE;
		store_cr0(cr0);
	}

	i=memtest_sub(start, end);

	if(flg486!=0){
		cr0 = load_cr0();
		cr0 &= ~CR0_CACHE_DISABLE;
		store_cr0(cr0);
	}
	return i;
}

unsigned int memtest_sub(unsigned int start, unsigned int end){
	unsigned int i, old, pat0=0xaa55aa55, pat1=0x55aa55aa;
	volatile unsigned int *p;
	for(i=start; i<=end; i+=0x1000){
		p = (unsigned int *)(i+0xffc);
		old = *p;
		*p = pat0;
		*p ^= 0xffffffff;
		if(*p!=pat1){
not_memory:
			*p = old;
			break;
		}
		*p ^= 0xffffffff;
		if(*p!=pat0){
			goto not_memory;
		}
		*p = old;
	}
	return i;
}

void memman_init(struct MEMMAN *man){
	man->frees = 0;
	man->maxfrees = 0;
	man->lostsize = 0;
	man->losts = 0;
	return;
}

unsigned int memman_total(struct MEMMAN *man){
	unsigned int i, t=0;
	for(i=0; i<man->frees; i++){
		t += man->free[i].size;
	}
	return t;
}

unsigned int memman_alloc(struct MEMMAN *man, unsigned int size){
	unsigned int i, a;
	for(i=0; i<man->frees; i++){
		if(man->free[i].size >= size){
			a = man->free[i].addr;
			man->free[i].addr += size;
			man->free[i].size -= size;
			if(man->free[i].size ==0){
				man->frees--;
				for(; i<man->frees; i++){
					man->free[i] = man->free[i+1];
				}
			}
			return a;
		}
	}
	return 0;
}

int memman_free(struct MEMMAN *man, unsigned int addr, unsigned int size){
	int i, j;
	for(i=0; i<man->frees; i++){
		if(man->free[i].addr > addr){
			break;
		}
	}
	if(i>0){
		if(man->free[i-1].addr + man->free[i-1].size == addr){
			man->free[i-1].size += size;
			if(i<man->frees){
				if(addr+size == man->free[i].addr){
					man->free[i-1].size += man->free[i].size;
					man->frees--;
					for(; i<man->frees; i++){
						man->free[i] = man->free[i+1];
					}
				}
			}
		}
		return 0;
	}
	if(i<man->frees){
		if(addr+size == man->free[i].addr){
			man->free[i].addr = addr;
			man->free[i].size += size;
			return 0;
		}
	}
	if(man->frees < MEMMAN_FREES){
		for(j=man->frees; j>i; j--){
			man->free[j] = man->free[j-1];
		}
		man->frees++;
		if(man->maxfrees < man->frees){
			man->maxfrees = man->frees;
		}
		man->free[i].addr = addr;
		man->free[i].size = size;
	}
	man->losts++;
	man->lostsize += size;
	return -1;
}
