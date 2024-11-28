#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include "queue.h"
#include <vector>
#include <random>
#include <iostream>

class Cluster
{
public:
	struct Task
	{
		int id; // уникальный идентификатор задачи
		int required_nodes; // число узлов, необходимых для выполнения
		int remaining_tacts; // оставшееся время выполнения
	};
	struct Statistics
	{
		size_t total_tasks; // общее количество задач
		size_t completed_tasks; // число выполненных задач
		size_t remaining_tasks; // число задач, оставшихся в очереди
		double avg_load; // средняя загрузка кластера
	};
private:
	int total_nodes; //	общее количество узлов
	int free_nodes; // свободные узлы
	size_t work_time; // время работы кластера (максимальное количество тактов)
	size_t current_tact; // текущий такт времени
	TQueue<Task> task_queue; // очередь задач
	std::vector<Task> active_tasks; // задачи, выполняющиеся на данном такте

	std::default_random_engine generator; // генератор псевдослучайных чисел

public:
	Cluster(int nodes, size_t work_time);
	void generate_tasks(double alpha, int max_new_tasks, int max_tacts, int max_nodes);
	void process_tasks();
	size_t get_current_tact() const noexcept;
	size_t get_work_time() const noexcept;
	size_t get_task_queue_size() const noexcept;
	size_t get_active_task_count() const noexcept;
	size_t get_free_node_count() const noexcept;
	Statistics get_statistics() const;
	friend std::ostream& operator<<(std::ostream& os, const Cluster& cluster);
};

#endif