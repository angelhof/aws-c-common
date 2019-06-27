/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws/common/linked_list.h>
#include <proof_helpers/make_common_data_structures.h>

void aws_linked_list_begin_harness() {
    /* data structure */
    struct aws_linked_list list;

    ensure_linked_list_is_allocated(&list, MAX_LINKED_LIST_ITEM_ALLOCATION);

    /* Assume the preconditions */
    __CPROVER_assume(aws_linked_list_is_valid(&list));

    /* Save the nodes of the old linked_list */
    struct aws_linked_list_node **old_list_nodes;
    size_t old_length;
    /* copy_linked_list_nodes(&list, &old_list_nodes, &old_length); */

    size_t temp_length = 0;
    struct aws_linked_list_node *temp = &list.head.next;
    while(temp != &list.tail) {
        temp_length++;
        temp = temp->next;
    }
    old_length = temp_length;
    
    /* Allocate an array with pointers to all nodes and fill it */
    struct aws_linked_list_node ** temp_nodes = malloc(temp_length * sizeof(struct aws_linked_list_node*));
    temp_length = 0;
    temp = &list.head.next;
    while(temp != &list.tail) {
        temp_nodes[temp_length++] = temp;
        temp = temp->next;
    }
    /* old_list_nodes = temp_nodes; */
    
    /* perform operation under verification */
    struct aws_linked_list_node *rval = aws_linked_list_begin(&list);

    /* assertions */
    assert(rval == list.head.next);
    assert(aws_linked_list_is_valid(&list));
    assert_linked_list_equivalence(&list, old_list_nodes, old_length);
}
