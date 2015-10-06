#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/rbtree.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Max Tang");

static int goodNum = 0;

module_param(goodNum, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(goodNum, "A good number");

struct my_tree_item {
    struct rb_node tree_node;
    int value;
};

static void free_rb_node(struct rb_node* node)
{
    if (node == NULL)
        return;

    free_rb_node(node->rb_left);
    free_rb_node(node->rb_right);

    kfree(node);
}

static void print_rb_node(struct rb_node* rb_node, int depth)
{
    int i;
    struct my_tree_item* itemp;
    char msg[32];

    if (rb_node == NULL)
        return;

    for (i = 0; i < depth; ++i)
        msg[i] = ' ';
    msg[i+1] = 0;
    
    itemp = rb_entry(rb_node, struct my_tree_item, tree_node);
    printk(KERN_ALERT "%s%d\n", msg, itemp->value);

    if (rb_node->rb_left != NULL)
        print_rb_node(rb_node->rb_left, depth + 1);
    if (rb_node->rb_right != NULL)
        print_rb_node(rb_node->rb_right, depth + 1);
}

static void insert_rb_tree(struct rb_node* node, struct rb_root* rb_root)
{
    struct rb_node** p = &rb_root->rb_node;
    struct rb_node* parent = NULL;
    struct my_tree_item* itemp = rb_entry(node, struct my_tree_item, tree_node);
    int value = itemp->value;

    while (*p)
    {
        parent = *p;
        itemp = rb_entry(*p, struct my_tree_item, tree_node);
        if (itemp->value > value)
            p = &(*p)->rb_left;
        else
            p = &(*p)->rb_right;
    }
    
    rb_link_node(node, parent, p);
}

static void test_rb_tree(void)
{
    struct rb_root root = RB_ROOT;
    int i = 0;
    struct my_tree_item* itemp = NULL;

    for (i = 0; i < 10; ++i)
    {
        itemp = kmalloc(sizeof(struct my_tree_item), GFP_KERNEL);
        if (!itemp)
            goto free_all;
        
        printk(KERN_ALERT "Inserting %d\n", i);
        itemp->value = i;
        insert_rb_tree(&itemp->tree_node, &root);

        rb_insert_color(&itemp->tree_node, &root);

        print_rb_node(root.rb_node, 0);
    }
        
free_all:
    free_rb_node(root.rb_node);
}



struct my_list_item {
    struct list_head list;
    int value;
};

static void test_list(void)
{
    struct my_list_item* itemp;
    LIST_HEAD(my_list);
    int i;

    for (i = 0; i < 10; ++i)
    {
        itemp = kmalloc(sizeof(struct my_list_item), GFP_KERNEL);
        if (!itemp)
            goto free_items;
        itemp->value = i*i;
        list_add(&itemp->list, &my_list);
    }
    
    list_for_each_entry(itemp, &my_list, list)
    {
        printk(KERN_ALERT "item in foreach %d\n", itemp->value);
    }
    
free_items:
    while (!list_empty(&my_list))
    {
        itemp = list_entry(my_list.next, struct my_list_item, list);
        printk(KERN_ALERT "item %d\n", itemp->value);
        list_del(&itemp->list);

        kfree(itemp);
    }
}

static int __init init_module1(void)
{
    printk(KERN_ERR "An error message!\n");
    printk(KERN_CRIT "Good number is %d\n", goodNum);
    printk(KERN_ALERT "Hello, world!\n");
    test_list();
    test_rb_tree();

    return 0;
}

static void __exit cleanup_module1(void)
{
    printk(KERN_ALERT "Goodbye, kernel!\n");
}

module_init(init_module1);
module_exit(cleanup_module1);
