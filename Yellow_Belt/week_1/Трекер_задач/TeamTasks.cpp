#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks{
public:
	//Получить статистику по статусам задач конкретного разработчика
	TasksInfo& GetPersonTasksInfo(const string& person){
		return database[person];
	}
	
	//Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person){
		(database[person])[TaskStatus::NEW]++;
	}
	
	//Обновить статусы по данному количеству задач конкретного разработчика,
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count){
		
		TasksInfo updated;
		TasksInfo untouched = GetPersonTasksInfo(person);
		TasksInfo current = GetPersonTasksInfo(person);
		
		while(untouched[TaskStatus::NEW] != 0 && task_count != 0){
			MakeTask(untouched, TaskStatus::NEW);
			task_count--;
		}
		if(untouched[TaskStatus::NEW] == 0 && task_count != 0){
			while(untouched[TaskStatus::IN_PROGRESS] != 0 && task_count != 0){
				MakeTask(untouched, TaskStatus::IN_PROGRESS);
				task_count--;
			}
			if(untouched[TaskStatus::IN_PROGRESS] == 0 && task_count != 0){
				while(untouched[TaskStatus::TESTING] != 0 && task_count != 0){
					MakeTask(untouched, TaskStatus::TESTING);
					task_count--;
				}
				if(untouched[TaskStatus::TESTING] == 0 && task_count != 0){
					task_count = 0;
				}
			}
		}	
		
		//Остались нетронутые задачи в untouched; Получим из них и полного вектора обновленные задачи
		for(int i = 0; i < 3; i++){
			updated[TaskStatus(i+1)] = current[TaskStatus(i)] - untouched[TaskStatus(i)];
		}
		
		//Обновляем информацию о задчах разработчика в database
		for(int i = 0; i < 4; i++){
			database[person][TaskStatus(i)] = updated[TaskStatus(i)] + untouched[TaskStatus(i)];
			
			if(database[person][TaskStatus(i)] == 0)
			{
				database[person].erase(TaskStatus(i));
			}			
		}
		
		//Очистим поля TasksInfo от лиших полей - пустых полей
		for(int i = 0; i < 4; i++){
			if(updated.at(TaskStatus(i)) == 0){
				updated.erase(TaskStatus(i));
			}
			
			if(untouched.at(TaskStatus(i)) == 0){
				untouched.erase(TaskStatus(i));
			}
		}
		
		//По исловию вернуть надо необновленные исключая выполненные
		untouched.erase(TaskStatus(3));
	
		return tie(updated, untouched);
	}
	
	void MakeTask(map<TaskStatus, int>& untouched, TaskStatus status){
		untouched[status]--;
	}


private:
	map<string, TasksInfo> database;
};

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;;
  
  for (int i = 0; i < 5; ++i){
    tasks.AddNewTask("Alice");
  }
  
  TasksInfo updated_tasks, untouched_tasks, current_tasks;
    
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
  
  cout << "Updated Alice tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
  
  cout << "Updated Alice tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
  
  cout << "Updated Alice tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  
  for (int i = 0; i < 5; ++i){
    tasks.AddNewTask("Alice");
  }
  
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
  current_tasks = tasks.GetPersonTasksInfo("Alice"); 
  
  cout << "current Alice tasks: ";
  PrintTasksInfo(current_tasks);
  cout << "Updated Alice tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
  current_tasks = tasks.GetPersonTasksInfo("Alice"); 
  
  cout << "current Alice tasks: ";
  PrintTasksInfo(current_tasks);
   cout << "Updated Alice tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  
  

  return 0;
}

/*
	AddNewTasks Alice 5
	PerformPersonTasks Alice 2
	GetPersonTasksInfo Alice
	PerformPersonTasks Alice 4
GetPersonTasksInfo Alice
 */




