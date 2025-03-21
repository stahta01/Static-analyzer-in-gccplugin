int gimplestmt_count;
int dump_points_to_solution2(FILE *file, struct pt_solution *pt)
{
	if (pt->anything)
		fprintf(file, ", points-to anything");
	if (pt->nonlocal)
		fprintf(file, ", points-to non-local");
	if (pt->escaped)
	{
		fprintf(file, ", points-to escaped");
	}
	if (pt->ipa_escaped)
	{
		fprintf(file, ", points-to unit escaped");
	}
	if (pt->null)
	{
		fprintf(file, ", points-to NULL");
	}
	if (pt->vars)
	{
		fprintf(file, ", points-to vars: ");
		// dump_decl_set(file, pt->vars);
		// if (pt->vars_contains_nonlocal || pt->vars_contains_escaped || pt->vars_contains_escaped_heap || pt->vars_contains_restrict)
		// {
		// 	const char *comma = "";
		// 	fprintf(file, " (");
		// 	if (pt->vars_contains_nonlocal)
		// 	{
		// 		fprintf(file, "nonlocal");
		// 		comma = ", ";
		// 	}
		// 	if (pt->vars_contains_escaped)
		// 	{
		// 		fprintf(file, "%sescaped", comma);
		// 		comma = ", ";
		// 	}
		// 	if (pt->vars_contains_escaped_heap)
		// 	{
		// 		fprintf(file, "%sescaped heap", comma);
		// 		comma = ", ";
		// 	}
		// 	if (pt->vars_contains_restrict)
		// 	{
		// 		fprintf(file, "%srestrict", comma);
		// 		comma = ", ";
		// 	}
		// 	if (pt->vars_contains_interposable)
		// 		fprintf(file, "%sinterposable", comma);
		// 	fprintf(file, ")");
		// }
	}
	return 1;
}
void printfBasicblock()
{
	fprintf(stderr, "\n===============Print ALL GIMPLE IR=================\n");

	gimple *u_stmt;
	gimple_array start;
	start.stmt = NULL;
	gimple_array *used_stmt = &start;
	ptb *table_temp = ptable;
	tree t;
	basic_block bb;

	struct cgraph_node *node;
	const char *name;

	FOR_EACH_FUNCTION(node)
	{

		if (!gimple_has_body_p(node->decl))
			continue;
		push_cfun(node->get_fun());

		if (cfun == NULL)
		{
			pop_cfun();
			continue;
		}
		name = get_name(cfun->decl);

		if (name != NULL)
		{

			fprintf(stderr, "=======Mapping node_fun:%s=========\n", name);
		}
		calculate_dominance_info(CDI_DOMINATORS);

		FOR_EACH_BB_FN(bb, cfun)
		{
			fprintf(stderr, "=======is loop:%d=========\n", bb_in_loop_p(bb));
			fprintf(stderr, "\n bb index %d \n", bb->index);
			debug_bb(bb);
			for (gimple_stmt_iterator gsi = gsi_start_bb(bb); !gsi_end_p(gsi); gsi_next(&gsi))
			{
				gimple *gc = gsi_stmt(gsi);
				location_t loc = gimple_location_safe(gc);
				// warning_at(gimple_location_safe(gc), 0, "use location");
				gimplestmt_count += 1;
			}
		}
		pop_cfun();
	}
	fprintf(stderr, "\n===============Print ALL GIMPLE IR=================\n");
}

void print_function_path(vector<return_type> *path)
{
	fprintf(stderr, "[\n");
	for (int i = 0; i < (*path).size(); i++)
	{
		debug((*path)[i].stmt);
		fprintf(stderr, ",\n");
	}
	fprintf(stderr, "]\n");
	// fprintf(stderr, "	function ->%s in loc %d \n", IDENTIFIER_POINTER(DECL_NAME((*path)[i].first.fndecl)), LOCATION_LINE((*path)[i].second));
}

void print_function_return2(tree function_tree)
{
	if (function_return_collect->get(function_tree) == NULL)
		return;
	function_return_array fun_array = *(function_return_collect->get(function_tree));

	vector<return_type> ret_type_array = fun_array.return_type_array;
	// debug_tree(function_tree);
	// vector<pair<fdecl,location_t>> loc;
	fprintf(stderr, "=======print_function_return %d   %d========\n", function_tree, ret_type_array.size());
	fprintf(stderr, "[\n");
	for (int i = 0; i < ret_type_array.size(); i++)
	{

		// for (int i = 0; i < (ret_type_array).size(); i++)
		// {
		debug((ret_type_array)[i].stmt);
		fprintf(stderr, ",\n");
		// }
		// fprintf(stderr, "]\n");
		// print_function_path(&ret_type_array);
	}
	fprintf(stderr, "]\n");
}

void print_function_return(tree function_tree)
{
	if (function_return_collect->get(function_tree) == NULL)
		return;
	function_return_array fun_array = *(function_return_collect->get(function_tree));

	vector<return_type> ret_type_array = fun_array.return_type_array;
	// debug_tree(function_tree);
	// vector<pair<fdecl,location_t>> loc;
	fprintf(stderr, "=======print_function_return %d   %d========\n", function_tree, ret_type_array.size());
	fprintf(stderr, "[\n");
	for (int i = 0; i < ret_type_array.size(); i++)
	{

		// for (int i = 0; i < (ret_type_array).size(); i++)
		// {
		debug((ret_type_array)[i].stmt);
		fprintf(stderr, ",\n");
		// }
		// fprintf(stderr, "]\n");
		// print_function_path(&ret_type_array);
	}
	fprintf(stderr, "]\n");
}

void printfunctionCollect2(ptb *ptable, gimple_array *user_tmp)
{
	// set_gimple_array(used_stmt, use_stmt, fundecl, fundecl);
	gimple *u_stmt;
	gimple_array start;
	start.stmt = NULL;
	gimple_array *used_stmt = &start;
	ptb *table_temp = ptable;
	tree t;
	basic_block bb;
	//
	struct cgraph_node *node;
	FOR_EACH_DEFINED_FUNCTION(node)
	{

		push_cfun(node->get_fun());
		// if (strcmp(get_name(cfun->decl), "main") == 0)
		// fprintf(stderr, "=======node_fun:%s=========\n", get_name(cfun->decl));
		// debug_tree(cfun->decl);
		if (cfun == NULL)
			continue;
		// calculate_dominance_info(CDI_DOMINATORS);
		print_function_return2(node->get_fun()->decl);
		pop_cfun();
	}
}
void printfunctionCollect(ptb *ptable, gimple_array *user_tmp)
{
	// set_gimple_array(used_stmt, use_stmt, fundecl, fundecl);
	gimple *u_stmt;
	gimple_array start;
	start.stmt = NULL;
	gimple_array *used_stmt = &start;
	ptb *table_temp = ptable;
	tree t;
	basic_block bb;
	//
	struct cgraph_node *node;
	const char *name;
	FOR_EACH_DEFINED_FUNCTION(node)
	{
		push_cfun(node->get_fun());
		// if (strcmp(get_name(cfun->decl), "main") == 0)
		// fprintf(stderr, "=======node_fun:%s=========\n", get_name(cfun->decl));
		// debug_tree(cfun->decl);
		if (cfun == NULL)
		{
			pop_cfun();
			continue;
		}
		name = get_name(cfun->decl);
		if (name != NULL)
		{
			fprintf(stderr, "=======Mapping node_fun:%s=========\n", get_name(cfun->decl));
			// debug_tree(cfun->decl);
			// debug_tree(cfun->decl);
		}
		// calculate_dominance_info(CDI_DOMINATORS);
		print_function_return(node->get_fun()->decl);
		pop_cfun();
	}
}

void printfPointerConstraint(ptb *ptable, gimple_array *user_tmp)
{
	gimple *u_stmt;
	gimple_array start;
	start.stmt = NULL;
	gimple_array *used_stmt = &start;
	ptb *table_temp = ptable;
	tree t;
	//

	FOR_EACH_TABLE(table_temp, t)
	{
		fprintf(stderr, "------------------- stmt -----------------------\n");
		// debug_tree(table_temp->target);
		if (table_temp->target != NULL)
		{
			// debug(table_temp->last_stmt);

			location_t loc = gimple_location_safe(table_temp->last_stmt);
			fprintf(stderr, "------------------------------------------\n");
			warning_at(loc, 0, "loc");

			debug_tree(table_temp->target);
			fprintf(stderr, "------------------------------------------\n");
			user_tmp = treeGimpleArray->get(table_temp->target);
			start.stmt = NULL;
			used_stmt = &start;
			if (user_tmp != NULL)
			{
				fprintf(stderr, " \n Pointer to set  is size %d :[ \n", user_tmp->size);
				if (user_tmp->size > 0)
					FOR_EACH_USE_TABLE(user_tmp, u_stmt)
					{

						if (user_tmp->ret_stmt != NULL)
						{
							location_t loc = gimple_location_safe(user_tmp->ret_stmt);
							warning_at(loc, 0, "loc");
						}
						else
						{
							location_t loc = gimple_location_safe(u_stmt);
							warning_at(loc, 0, "loc");
						}
					}
			}
			else
			{
				fprintf(stderr, " \n Pointer to set  is size 0 :[ \n");
			}
			fprintf(stderr, "] \n");
		}
	}
}

void printfPointerConstraint2(ptb *ftable, gimple_array *user_tmp)
{
	gimple *u_stmt;
	gimple_array start;
	start.stmt = NULL;
	gimple_array *used_stmt = &start;
	ptb *table_temp = ptable;
	tree t;

	FOR_EACH_TABLE(table_temp, t)
	{
		fprintf(stderr, "\n ------------------------------------------\n");

		if (table_temp->target != NULL)
		{
			debug_tree(table_temp->target);
			user_tmp = treeGimpleArray->get(table_temp->target);
			start.stmt = NULL;
			used_stmt = &start;
			if (user_tmp != NULL)
			{
				fprintf(stderr, " \n Pointer to set  is size %d :[ \n", user_tmp->size);
				if (user_tmp->size > 0)
					FOR_EACH_USE_TABLE(user_tmp, u_stmt)
					{
						if (user_tmp->ret_stmt != NULL)
							debug(user_tmp->ret_stmt);

						else
							debug(u_stmt);
					}
				fprintf(stderr, "] \n");
			}
			else
			{
				fprintf(stderr, " \n Pointer to set  is size 0 :[ \n");
				fprintf(stderr, "] \n");
			}
		}
	}
}
