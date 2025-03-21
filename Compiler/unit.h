void analyze_type(tree tree_typed)
{
	// printf("%s ", get_tree_code_name(TREE_CODE(tree_typed)));
	switch (TREE_CODE(tree_typed))
	{
	case FUNCTION_TYPE:
	{
		printf("receives ");
		tree args = TYPE_ARG_TYPES(tree_typed);
		if (args == NULL_TREE)
			printf("nothing ");
		else
			while (args != NULL_TREE && TREE_VALUE(args) != void_type_node)
			{
				analyze_type(TREE_VALUE(args));
				if (TREE_CHAIN(args) != NULL_TREE)
					printf("and ");
				else
					printf("... "); // this node is not void_type_node and the next node is NULL_TREE, thus variadic arguments
				args = TREE_CHAIN(args);
			}
		printf("then returns ");
		analyze_type(TREE_TYPE(tree_typed));
		break;
	}
	case RECORD_TYPE:
	{
		printf("named ");
		tree type_name = TYPE_NAME(tree_typed);
		if (TREE_CODE(type_name) == IDENTIFIER_NODE)
		{
			printf("%s ", IDENTIFIER_POINTER(type_name));
		}
		else if (TREE_CODE(type_name) == TYPE_DECL)
		{
			printf("%s ", IDENTIFIER_POINTER(DECL_NAME(type_name)));
		}
		else
		{
			printf("**** UNRECOGNIZED TYPE NODE ****");
		}
		break;
	}
		switch (TREE_CODE(tree_typed))
		case POINTER_TYPE:
		{
			printf("points to ");
			analyze_type(TREE_TYPE(tree_typed));
			break;
		}
		case INTEGER_TYPE:
		{
			unsigned int precision = TYPE_PRECISION(tree_typed);
			printf("%s integer of %d bits ", TYPE_UNSIGNED(tree_typed) ? "unsigned" : "signed", precision);
			break;
		}
		case ARRAY_TYPE:
		{
			printf("of ");
			analyze_type(TREE_TYPE(tree_typed));
			break;
		}
		case VAR_DECL:
		{
			printf("oSDAAAAAf ");
			analyze_type(TREE_TYPE(tree_typed));
			break;
		}
		default:
			break;
	}
}
bool bb_in_loop_p(basic_block bb)
{
	return bb->loop_father->header->index != 0;
}

bool bb_in_branch_p(gimple *stmt)
{
	// function* fn = DECL_STRUCT_FUNCTION(gimple_get_lhs(stmt));
	//  debug_gimple_stmt(stmt);
	//  debug_bb(stmt->bb);
	//  debug_bb(cfun->cfg->x_exit_block_ptr->prev_bb);
	//  debug_bb(cfun->cfg->x_entry_block_ptr->next_bb);
	//  debug_bb(stmt->bb);
	//  fprintf(stderr," %d\n",dominated_by_p(CDI_DOMINATORS,stmt->bb,cfun->cfg->x_exit_block_ptr->prev_bb));

	return !dominated_by_p(CDI_DOMINATORS, stmt->bb, cfun->cfg->x_exit_block_ptr->prev_bb);
}

void init_table()
{
	// fprintf(stderr,"init_table.... \n");
	start1.target = NULL_TREE;
	start1.next = NULL;
	start1.state = POINTER_NOT_EXIST;
	ptable = &start1;

	start2.target = NULL_TREE;
	start2.next = NULL;
	start2.state = POINTER_NOT_EXIST;
	ftable = &start2;
}

bool Location_b(gimple *a, gimple *b, basic_block bb)
{
	gimple *gc;
	// debug_gimple_stmt(a);
	// debug_gimple_stmt(b);
	for (gimple_stmt_iterator gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
	{
		gc = gsi_stmt(gsi);
		// debug_gimple_stmt(gc);
		if (gc == a)
		{
			return true;
		}
		else if (gc == b)
		{
			return false;
		}
	}
	return false;
}

bool Location_b2(gimple *a, gimple *b, tree function_tree)
{
	struct cgraph_node *node;
	basic_block bb;
	FOR_EACH_DEFINED_FUNCTION(node)
	{
		if (!gimple_has_body_p(node->decl))
			continue;

		push_cfun(DECL_STRUCT_FUNCTION(node->decl));

		// fprintf(stderr, "=====www==node_fun:%s=========\n", get_name(cfun->decl));

		if (cfun == NULL)
		{
			pop_cfun();
			continue;
		}
		// mutlple entry point
		if (cfun->decl == function_tree)
		{

			calculate_dominance_info(CDI_DOMINATORS);

			FOR_EACH_BB_FN(bb, cfun)
			{

				for (gimple_stmt_iterator gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
				{
					gimple *gc = gsi_stmt(gsi);
					if (gc == a)
					{
						pop_cfun();
						return true;
					}
					else if (gc == b)
					{
						pop_cfun();
						return false;
					}
				}
			}
		}
		pop_cfun();
	}
	return false;
}

bool Location_b3(gimple *a, gimple *b, tree function_tree)
{
	struct cgraph_node *node;
	basic_block bb;
	FOR_EACH_DEFINED_FUNCTION(node)
	{
		if (!gimple_has_body_p(node->decl))
			continue;

		push_cfun(DECL_STRUCT_FUNCTION(node->decl));

		// fprintf(stderr, "=====www==node_fun:%s=========\n", get_name(cfun->decl));

		if (cfun == NULL)
		{
			pop_cfun();
			continue;
		}
		// mutlple entry point
		if (cfun->decl == function_tree)
		{

			calculate_dominance_info(CDI_DOMINATORS);

			FOR_EACH_BB_FN(bb, cfun)
			{

				for (gimple_stmt_iterator gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
				{
					gimple *gc = gsi_stmt(gsi);
					if (dominated_by_p(CDI_DOMINATORS, a->bb, b->bb))
					{
						pop_cfun();
						return true;
					}
					else
					{
						pop_cfun();
						return false;
					}
				}
			}
		}
		pop_cfun();
	}
	return false;
}
unsigned int SDBMHash(char *str)
{
	unsigned int hash = rand() % 10;

	while (*str)
	{
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}

	return (hash & 0x7FFFFFFF);
}
void output_basic_block_stage()
{
	if (symbolicexecution)
	{
		fprintf2(stderr, "\n=============================output_basic_block_stage==================================\n");
		fprintf(stderr, "alloc index %d\n", alloc_index);
		for (int i = 0; i < bestfreepaths.size(); i++)
		{
			// // if(bestfreepaths[i].mttindex == alloc_index)
			// fprintf(stderr, "bb index %d: mmt :%d, has stmt :%d has free:%d has exit:%d\n", (bestfreepaths[i].bb)->index, bestfreepaths[i].mttindex,
			// 		bestfreepaths[i].has_stmt, bestfreepaths[i].has_free, bestfreepaths[i].has_exit);
			// z3 mod
			fprintf(stderr, "[%d,%d,%d,%d],\n", (bestfreepaths[i].bb)->index,
					bestfreepaths[i].has_stmt, bestfreepaths[i].has_free, bestfreepaths[i].has_exit);
		}
	}
}
int update_basic_block(basic_block bb, int setmttindex, int sethas_stmt, int sethas_free, int sethas_exit)
{
	if (symbolicexecution)
	{
		int find = 0;
		for (int i = bestfreepaths.size() - 1; i >= 0; i--)
		{
			if (bestfreepaths[i].bb == bb)
			{
				find = 1;
				if (setmttindex >= 1)
					bestfreepaths[i].mttindex = setmttindex;
				if (sethas_stmt >= 1)
					bestfreepaths[i].has_stmt = sethas_stmt;
				if (sethas_free >= 1)
					bestfreepaths[i].has_free = sethas_free;
				if (sethas_exit >= 1)
					bestfreepaths[i].has_exit = sethas_exit;
				// fprintf(stderr, "\n ================== find free stmt %d====%d============== \n",bestfreepaths[i].bb->index,bestfreepaths[i].has_exit );
			}
		}
		if (!find)
		{
			basic_block_attributes add;
			add.bb = bb;
			add.mttindex = setmttindex;
			add.has_stmt = sethas_stmt;
			add.has_free = sethas_free;
			add.has_exit = sethas_exit;
			bestfreepaths.push_back(add);
		}
	}
}
int fprintf2(FILE *stream, const char *format, ...)
{
	if (!debugoutput)
		return 0;
	va_list ap;
	va_start(ap, format);
	// vprintf(format,ap);
	vfprintf(stream, format, ap);

	va_end(ap);
	fflush(fp);
}

DEBUG_FUNCTION void
debug_gimple_stmt2(gimple *gs)
{
	if (!debugoutput)
		return;
	debug_gimple_stmt(gs);
}

DEBUG_FUNCTION void
debug_tree2(tree node)
{
	if (!debugoutput)
		return;
	debug_tree(node);
}

// DEBUG_FUNCTION void
// debug2 (const tree_node &ref)
// {
//   dump_tree_via_hooks (&ref, TDF_NONE);
// }

DEBUG_FUNCTION void
debug2(const tree_node *ptr)
{
	if (!debugoutput)
		return;
	if (ptr)
		debug(*ptr);
	else
		fprintf(stderr, "<nil>\n");
}
DEBUG_FUNCTION void
debug2(gimple *ptr)
{
	if (!debugoutput)
		return;
	if (ptr)
		debug(*ptr);
	else
		fprintf(stderr, "<nil>\n");
}

/* A warning at LOCATION.  Use this for code which is correct according to the
   relevant language specification but is likely to be buggy anyway.
   Returns true if the warning was printed, false if it was inhibited.  */

bool warning_at2(location_t location, int opt, const char *gmsgid, ...)
{
	if (!debugoutput)
		return 0;
	expanded_location xloc = expand_location(location);

	return 1;
	inform_n(location, 0, /* msgid */ "", /* default_msg */ "");
	// return warning_at(location, opt, gmsgid);
}

/* Same as "warning at" above, but using RICHLOC.  */

bool warning_at2(rich_location *richloc, int opt, const char *gmsgid, ...)
{
	if (!debugoutput)
		return 0;
	// 		 inform_n(location, 0, /* msgid */ "note", /* default_msg */
	//  "This is an informational message");
	//  return 1;
	return warning_at(richloc, opt, gmsgid);
}

// void insert_always_inline()
// {
// 	cgraph_node *node;
// 	const char *name;
// 	bool always_inline;
// 	// fprintf(stderr,"=======inline=========\n");

// 	FOR_EACH_DEFINED_FUNCTION(node)
// 	{
// 		basic_block bb;
// 		cgraph_edge *e;

// 		if (!gimple_has_body_p(node->decl))
// 			continue;
// 		// fprintf(stderr, "=======node_fun:%s=========\n", get_name(cfun->decl));

// 		tree attr;
// 		enum availability avail;
// 		for (e = node->callees; e; e = e->next_callee)
// 		{

// 			cgraph_node *caller = e->caller->inlined_to ? e->caller->inlined_to : e->caller;
// 			cgraph_node *callee = e->callee->ultimate_alias_target(&avail, caller);
// 			tree callee_tree = callee ? DECL_FUNCTION_SPECIFIC_OPTIMIZATION(callee->decl) : NULL;
// 			// DECL_DISREGARD_INLINE_LIMITS (callee->decl)=1;
// 			if (DECL_ATTRIBUTES(callee->decl) != NULL)
// 			{
// 				attr = get_attribute_name(DECL_ATTRIBUTES(callee->decl));
// 				// debug_tree(attr);
// 			}
// 			else
// 			{
// 				// if(callee->decl)
// 				// DECL_ATTRIBUTES (callee->decl) = tree_cons (get_identifier ("always_inline"),
// 				// NULL, DECL_ATTRIBUTES (callee->decl));
// 			}

// 			if (lookup_attribute("noinline", DECL_ATTRIBUTES(callee->decl)) == NULL)
// 			{

// 				fprintf(stderr, "=======node_fun:%s=========\n", get_name(callee->decl));
// 				DECL_ATTRIBUTES(callee->decl) = tree_cons(get_identifier("noinline"), NULL, DECL_ATTRIBUTES(callee->decl));
// 				DECL_DISREGARD_INLINE_LIMITS(callee->decl) = 1;
// 				debug_tree(DECL_ATTRIBUTES(callee->decl));
// 			}
// 			else
// 			{
// 				fprintf(stderr, "=======node_fun:%s=========\n", get_name(callee->decl));

// 				debug_tree(DECL_ATTRIBUTES(callee->decl));
// 			}
// 			// if (!lookup_attribute("noinline", DECL_ATTRIBUTES(callee->decl)))
// 			// {
// 			// 	fprintf(stderr, "=======node_fun:%s=========\n", get_name(callee->decl));
// 			// 	DECL_ATTRIBUTES(callee->decl) = tree_cons(get_identifier("noinline"), NULL, DECL_ATTRIBUTES(callee->decl));
// 			// 	DECL_DISREGARD_INLINE_LIMITS(callee->decl) = 1;
// 			// 	debug_tree(DECL_ATTRIBUTES(callee->decl));
// 			// }
// 			// 	always_inline = (DECL_DISREGARD_INLINE_LIMITS(callee->decl) && lookup_attribute("noinline", DECL_ATTRIBUTES(callee->decl)));
// 			// debug_tree(DECL_ATTRIBUTES(callee->decl));
// 		}
// 		push_cfun(DECL_STRUCT_FUNCTION(node->decl));
// 		// if (cfun == NULL)
// 		// {
// 		// }

// 		// if (!MAIN_NAME_P(DECL_NAME(node->decl)))
// 		// {
// 		// debug_tree(DECL_ATTRIBUTES(cfun->decl));
// 		// if( !lookup_attribute("noinline", DECL_ATTRIBUTES(node->decl))){
// 		// DECL_ATTRIBUTES(cfun->decl) = tree_cons(get_identifier("noinline"), NULL, DECL_ATTRIBUTES(cfun->decl));
// 		// DECL_DISREGARD_INLINE_LIMITS(cfun->decl) = 1;}

// 		// debug_tree(DECL_ATTRIBUTES(cfun->decl));
// 		// }
// 		// FOR_EACH_BB_FN(bb, cfun)
// 		// {

// 		// 	for (gimple_stmt_iterator gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
// 		// 	{
// 		// 		gimple *gc = gsi_stmt(gsi);

// 		// 		if (is_gimple_call(gc))
// 		// 		{

// 		// 			if (gimple_call_fn(gc) == NULL)
// 		// 				continue;
// 		// 			name = get_name(gimple_call_fn(gc));
// 		// 			if (name == NULL)
// 		// 				continue;

// 		// 			if (!strcmp(name, "free") ||
// 		// 				!strcmp(name, "xfree") ||
// 		// 				!strcmp(name, "malloc") ||
// 		// 				!strcmp(name, "realloc") ||
// 		// 				!strcmp(name, "xmalloc") ||
// 		// 				!strcmp(name, "calloc") ||
// 		// 				!strcmp(name, "xcalloc") ||
// 		// 				!strcmp(name, "strdup"))
// 		// 			{

// 		// 				//always_inline = (DECL_DISREGARD_INLINE_LIMITS(node->decl) && lookup_attribute("no_inline", DECL_ATTRIBUTES(node->decl)));
// 		// 				if ( !MAIN_NAME_P(DECL_NAME(node->decl)))
// 		// 				{
// 		// 					DECL_ATTRIBUTES(node->decl) = tree_cons(get_identifier("no_inline"), NULL, DECL_ATTRIBUTES(node->decl));
// 		// 					DECL_DISREGARD_INLINE_LIMITS(node->decl) = 1;
// 		// 				}
// 		// 			}
// 		// 		}
// 		// 	}
// 		// }
// 		pop_cfun();
// 	}
// };