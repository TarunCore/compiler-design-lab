#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"closure_goto.h"
#include"parsingtable.h"
#include"first_follow.h"
#include"parse.h"

int main() {
	start();

	initialize_first_follow();
	compute_first();
	compute_follow();

	create_parsing_table();

	parse();	

	return 0;
}
