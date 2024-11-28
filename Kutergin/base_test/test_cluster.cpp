#include "cluster.h"
#include "cluster.cpp"
#include <gtest.h>

TEST(TCluster, can_create_cluster_with_valid_parameters)
{
	ASSERT_NO_THROW(Cluster cluster(10, 50));
}

TEST(TCluster, throws_when_creating_cluster_with_zero_nodes)
{
	ASSERT_ANY_THROW(Cluster cluster(0, 50));
}

TEST(TCluster, throws_when_creating_cluster_with_negative_nodes)
{
	ASSERT_ANY_THROW(Cluster cluster(-10, 5));
}

TEST(TCluster, throws_when_creating_cluster_with_zero_work_time)
{
	ASSERT_ANY_THROW(Cluster cluster(10, 0));
}

TEST(TCluster, can_process_tacts_with_no_tasks)
{
	Cluster cluster(10, 50);

	ASSERT_NO_THROW(cluster.process_tasks()); // generate_tasks не был вызван
}

TEST(TCluster, can_generate_tasks)
{
	Cluster cluster(4, 10);

	cluster.generate_tasks(1.0, 2, 5, 1);

	EXPECT_EQ(2, cluster.get_task_queue_size());
}


TEST(TCluster, tasks_are_completed_correctly)
{
	Cluster cluster(2, 5);

	cluster.generate_tasks(1.0, 1, 1, 1); 
	cluster.process_tasks();

	EXPECT_EQ(0, cluster.get_active_task_count());
	EXPECT_EQ(2, cluster.get_free_node_count());
}

TEST(TCluster, processes_multiple_tacts_correctly)
{
	Cluster cluster(2, 5);

	cluster.generate_tasks(1.0, 1, 1, 1); // Задача на 3 такта
	cluster.process_tasks();
	cluster.process_tasks();
	cluster.process_tasks();

	EXPECT_EQ(cluster.get_active_task_count(), 0);
	EXPECT_EQ(cluster.get_free_node_count(), 2);
}

/*
TEST(TCluster, handles_insufficient_nodes_gracefully)
{
	Cluster cluster(2, 5);

	cluster.generate_tasks(1.0, 3, 1, 1); // задач больше, чем узлов
	cluster.process_tasks();

	EXPECT_EQ(3, cluster.get_task_queue_size());
	EXPECT_EQ(0, cluster.get_active_task_count());
}

TEST(TCluster, calculates_average_load_correctly)
{
	Cluster cluster(4, 10);

	cluster.generate_tasks(1.0, 1, 1, 1); // Одна задача на 5 тактов, использует 4 узла
	cluster.process_tasks();
	double load = cluster.get_statistics().avg_load;
	EXPECT_EQ(0.25, load);
}
*/