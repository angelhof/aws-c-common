/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may not use
 * this file except in compliance with the License. A copy of the License is
 * located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * FUNCTION: s_swap
 *
 * This overrides s_swap from priority_queue with a no_op. It is used
 * in s_sift_down and s_sift_up as in their proofs memcpy is stubbed
 * with a no_op, and thus there is no real data movement inside the
 * priority queue. 
 */

#include <aws/common/priority_queue.h>

void __CPROVER_file_local_priority_queue_c_s_swap(struct aws_priority_queue *queue, size_t a, size_t b) {
    assert(aws_priority_queue_is_valid(queue));
    assert(a < queue->container.length);
    assert(b < queue->container.length);
    assert(aws_backpointer_index_valid(queue, a));
    assert(aws_backpointer_index_valid(queue, b));

    /* Invariant: If the backpointer array is initialized, we have enough room for all elements */
    if (queue->backpointers.data) {
        assert(queue->backpointers.length > a);
        assert(queue->backpointers.length > b);
    }
}
