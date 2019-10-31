#include "rdp.h"

t_flags	check_param(char **av)
{
	t_flags f;
	f.debug_all = 0;
	f.ast_draw = 0;
	while (*av)
	{
		if (strcmp(*av, "-debug=all") == 0)
			f.debug_all = 1;
		else if (strcmp(*av, "-ast=draw") == 0)
			f.ast_draw = 1;
		av++;
	}
	return (f);
}

void	draw_ast(t_node *n)
{
	while (n)
	{
		if (n->left)
		{
			printf("\t\t\t\t%s\n\t\t\t/\t\t\\\n\t\t       %s\t\t %s\n", n->data, n->left->data, n->right->data);
			if (n->left->tok == TOK_MUL || n->left->tok == TOK_DIVIDE)
			{
				n = n->left;
				printf("\t\t     /\t\\\n\t\t   %s\t %s\n", n->left->data, n->right->data);
			}
		}
		n = n->left;
	}
}

void bst_print_dot_null(char *data, int key, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    \"%s_%d\" -> null%d;\n", data, key, nullcount);
}

void bst_print_dot_aux(t_node* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left)
    {
        fprintf(stream, "    \"%s_%d\" -> \"%s_%d\";\n", node->data, node->key, node->left->data, node->left->key);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->data, node->key, nullcount++, stream);

    if (node->right)
    {
        fprintf(stream, "    \"%s_%d\" -> \"%s_%d\";\n", node->data, node->key, node->right->data, node->right->key);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->data, node->key, nullcount++, stream);
}

void bst_print_dot(t_node* tree, FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    \"%s_%d\";\n", tree->data, tree->key);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}
