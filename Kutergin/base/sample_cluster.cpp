#include <iostream>
#include <string>
#include "cluster.h"

using namespace std;

int main()
{
	// параметры кластера
	int nodes = 16;
	size_t work_time = 2;
	Cluster cluster(nodes, work_time);

	// параметры генерации задач
	double alpha = 0.5; // вероятность генерации задачи
	int max_new_tasks = 10; // максимальное количество новых задач за такт
	int max_tacts = 50; // максимальное время выполнения задачи
	int max_nodes = 2; // максимальное число узлов, запрашиваемое задачей

	// Выводим настройки
	cout << "Cluster simulation:\n"
		<< "  Total nodes: " << nodes << "\n"
		<< "  Work time of cluster (tacts): " << work_time << "\n"
		<< "  Alpha: " << alpha << "\n"
		<< "  Max new tasks per tact: " << max_new_tasks << "\n"
		<< "  Max task duration: " << max_tacts << "\n"
		<< "  Max nodes neede: " << max_nodes << "\n\n";

	while (cluster.get_current_tact() < cluster.get_work_time()) // cимуляция работы кластера
	{
		cout << "n--- Tact " << cluster.get_current_tact() << " ---" << endl;

		// генерация новых задач
		cluster.generate_tasks(alpha, max_new_tasks, max_tacts, max_nodes);
		cout << "Generated tasks this tact: " << cluster.get_statistics().total_tasks << "\n";

		// обработка задач
		cluster.process_tasks();

		// печать текущего состояния кластера
		Cluster::Statistics stats = cluster.get_statistics();
		cout << "Statistics:" << endl;
		cout << "	Total tasks: " << stats.total_tasks << endl;
		cout << "	Completed tasks: " << stats.completed_tasks << endl;
		cout << "	Remaining tasks: " << stats.remaining_tasks << endl;
		cout << "	Average load: " << stats.avg_load * 100.0 << "%" << endl;

		cout << cluster << endl;
	}

	cout << "\nSimulation complete." << endl;

	return 0;
}
