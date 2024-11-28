#include "cluster.h"
#include <algorithm>

Cluster::Cluster(int nodes, size_t time) : total_nodes(nodes), free_nodes(nodes), current_tact(0), work_time(time),
task_queue(), active_tasks(), generator(std::random_device{}()) 
{
	if (nodes <= 0)
		throw invalid_argument("The number of nodes must be greater than zero.");
	if (time <= 0)
		throw invalid_argument("The work time must be greater than zero.");
}

void Cluster::generate_tasks(double alpha, int max_new_tasks, int max_tacts, int max_nodes)
{
	std::uniform_real_distribution<double> probability_distribution(0.0, 1.0); // для вероятности alpha
	// Генерация новых задач
	std::uniform_int_distribution<int> node_distribution(1, max_nodes);
	std::uniform_int_distribution<int> tact_distribution(1, max_tacts);

	for (int i = 0; i < max_new_tasks; ++i)
	{
		if (probability_distribution(generator) <= alpha)
		{
			Task new_task;
			// используем текущий такт кластера как уникальный ID задачи
			new_task.id = current_tact;
			// генерация случайного количества узлов и оставшихся тактов
			new_task.required_nodes = node_distribution(generator); // число узлов от 1 до free_nodes
			new_task.remaining_tacts = tact_distribution(generator); // оставшиеся такты от 1 до max_tacts
			task_queue.Push(new_task); // добавляем новую задачу в очередь
		}
	}
}

void Cluster::process_tasks()
{
	while (!task_queue.IsEmpty() && free_nodes > 0) // обрабатываем задачи
	{
		Task task = task_queue.Pop();
		if (task.required_nodes <= free_nodes) // выполнение задачи
		{
			active_tasks.push_back(task);
			free_nodes -= task.required_nodes;
		}
		else // Если узлов недостаточно, задача остается в очереди
		{
			task_queue.Push(task);
			break;
		}
	}

	for (size_t i = 0 ; i < active_tasks.size(); ) // обновляем состояния задач
	{
		active_tasks[i].remaining_tacts--;
		if (active_tasks[i].remaining_tacts <= 0)
		{
			free_nodes += active_tasks[i].required_nodes; // освобождаем узлы
			active_tasks.erase(active_tasks.begin() + i); // удаляем завершенную задачу
		}
		else
			++i;
	}

	++current_tact; // увеличиваем текущий такт
}

size_t Cluster::get_current_tact() const noexcept
{
	return current_tact;
}

size_t Cluster::get_work_time() const noexcept
{
	return work_time;
}

size_t Cluster::get_task_queue_size() const noexcept
{
	return task_queue.size();
}

size_t Cluster::get_active_task_count() const noexcept
{
	return active_tasks.size();
}

size_t Cluster::get_free_node_count() const noexcept
{
	return free_nodes;
}

Cluster::Statistics Cluster::get_statistics() const
{
	Statistics stats;
	stats.total_tasks = task_queue.size() + active_tasks.size();
	stats.completed_tasks = active_tasks.size();
	stats.remaining_tasks = task_queue.size();
	stats.avg_load = static_cast<double>(total_nodes - free_nodes) / total_nodes;
	return stats;
}

std::ostream& operator<<(std::ostream& os, const Cluster& cluster)
{
	os << "Total nodes: " << cluster.total_nodes << ", Free nodes: " << cluster.free_nodes
		<< ", Current tact: " << cluster.current_tact << ", Work time: " << cluster.work_time;
	return os;
}
