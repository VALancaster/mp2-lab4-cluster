#include "queue.h"
#include <gtest.h>

TEST(TQueue, can_create_queue)
{
    ASSERT_NO_THROW(TQueue<int> q);
}

TEST(TQueue, can_enqueue)
{
    TQueue<int> q;

    ASSERT_NO_THROW(q.Push(5));
}

TEST(TQueue, can_dequeue)
{
    TQueue<int> q;
    q.Push(10);

    ASSERT_NO_THROW(q.Pop());
}

TEST(TQueue, dequeue_returns_correct_value)
{
    TQueue<int> q;
    q.Push(42);

    EXPECT_EQ(42, q.Pop());
}

TEST(TQueue, can_check_if_queue_is_empty)
{
    TQueue<int> q;

    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueue, queue_is_not_empty_after_enqueue)
{
    TQueue<int> q;
    q.Push(1);

    EXPECT_FALSE(q.IsEmpty());
}

TEST(TQueue, can_get_queue_size)
{
    TQueue<int> q;
    q.Push(1);
    q.Push(2);

    EXPECT_EQ(2, q.size());
}

TEST(TQueue, pop_reduces_size)
{
    TQueue<int> q;
    q.Push(1);
    q.Push(2);
    q.Pop();

    EXPECT_EQ(1, q.size());
}
