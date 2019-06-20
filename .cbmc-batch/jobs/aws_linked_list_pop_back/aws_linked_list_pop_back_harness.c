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

void aws_linked_list_pop_back_harness() {
    /* data structure */
    struct aws_linked_list list;

    ensure_linked_list_is_allocated(&list, MAX_LINKED_LIST_ITEM_ALLOCATION);

    /* Assume the preconditions. The function requires that list != NULL */
    __CPROVER_assume(!aws_linked_list_empty(&list));
    
    /* Keep the old last node of the linked list */
    struct aws_linked_list_node *old_prev_last = (list.tail.prev)->prev;

    /* perform operation under verification */
    struct aws_linked_list_node *ret = aws_linked_list_pop_back(&list);

    /* assertions */
    assert(aws_linked_list_is_valid(&list));
    assert(ret->next == NULL && ret->prev == NULL);
    assert(list.tail.prev == old_prev_last);
}
