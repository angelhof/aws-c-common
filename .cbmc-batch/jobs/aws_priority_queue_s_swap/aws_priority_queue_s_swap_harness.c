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

#include <aws/common/priority_queue.h>
#include <proof_helpers/make_common_data_structures.h>

/**
 * Runtime: 180s
 */
void aws_priority_queue_s_swap_harness() {
    /* data structure */
    struct aws_priority_queue queue;

    /* assumptions */

    /* Question: Is bounding by item size and initial item allocation necessary? */
    /* I think that if I increase this it takes much more time. I am not sure though */
    __CPROVER_assume(aws_priority_queue_is_bounded(&queue, MAX_INITIAL_ITEM_ALLOCATION, MAX_ITEM_SIZE));
    
    ensure_priority_queue_has_allocated_members(&queue);

    /* Assuming the function preconditions */
    __CPROVER_assume(aws_priority_queue_is_valid(&queue));

    /* perform operation under verification */

    /* I probably have to constrain them to be less than the size of the queue */
    size_t a;
    size_t b;

    __CPROVER_assume(a < queue.container.length);
    __CPROVER_assume(b < queue.container.length);
    
    /* This assumes that the two backpointers a, b are valid, either
     * by being NULL or by allocating their objects with their correct
     * values. */
    ensure_backpointer_cell_points_to_allocated(&(queue.backpointers), a);
    ensure_backpointer_cell_points_to_allocated(&(queue.backpointers), b);

    s_swap(&queue, a, b);

    /* assertions */
    /* This is asserted as a postcondition */
    /* assert(aws_priority_queue_is_valid(&queue)); */
    /* assert_array_list_equivalence(&queue.container, &old_container, &old_byte_container); */
    /* assert_array_list_equivalence(&queue.backpointers, &old_backpointers, &old_byte_backpointers); */
}
