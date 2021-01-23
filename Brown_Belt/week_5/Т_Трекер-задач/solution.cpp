#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

class TeamTasks {
public:
  //Получить статистику по статусам задач конкретного разработчика
  TasksInfo &GetPersonTasksInfo(const string &person) {
    return database[person];
  }

  //Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string &person) {
    (database[person])[TaskStatus::NEW]++;
  }

  //Обновить статусы по данному количеству задач конкретного разработчика,
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person,
                                                 int task_count) {

    TasksInfo updated;
    TasksInfo untouched = GetPersonTasksInfo(person);
    TasksInfo current = GetPersonTasksInfo(person);

    while (untouched[TaskStatus::NEW] != 0 && task_count != 0) {
      MakeTask(untouched, TaskStatus::NEW);
      task_count--;
    }
    if (untouched[TaskStatus::NEW] == 0 && task_count != 0) {
      while (untouched[TaskStatus::IN_PROGRESS] != 0 && task_count != 0) {
        MakeTask(untouched, TaskStatus::IN_PROGRESS);
        task_count--;
      }
      if (untouched[TaskStatus::IN_PROGRESS] == 0 && task_count != 0) {
        while (untouched[TaskStatus::TESTING] != 0 && task_count != 0) {
          MakeTask(untouched, TaskStatus::TESTING);
          task_count--;
        }
        if (untouched[TaskStatus::TESTING] == 0 && task_count != 0) {
          task_count = 0;
        }
      }
    }

    //Остались нетронутые задачи в untouched; Получим из них и полного вектора
    //обновленные задачи
    for (int i = 0; i < 3; i++) {
      updated[TaskStatus(i + 1)] =
          current[TaskStatus(i)] - untouched[TaskStatus(i)];
    }

    //Обновляем информацию о задчах разработчика в database
    for (int i = 0; i < 4; i++) {
      database[person][TaskStatus(i)] =
          updated[TaskStatus(i)] + untouched[TaskStatus(i)];

      if (database[person][TaskStatus(i)] == 0) {
        database[person].erase(TaskStatus(i));
      }
    }

    //Очистим поля TasksInfo от лиших полей - пустых полей
    for (int i = 0; i < 4; i++) {
      if (updated.at(TaskStatus(i)) == 0) {
        updated.erase(TaskStatus(i));
      }

      if (untouched.at(TaskStatus(i)) == 0) {
        untouched.erase(TaskStatus(i));
      }
    }

    //По исловию вернуть надо необновленные исключая выполненные
    untouched.erase(TaskStatus(3));

    return tie(updated, untouched);
  }

  void MakeTask(map<TaskStatus, int> &untouched, TaskStatus status) {
    untouched[status]--;
  }

private:
  map<string, TasksInfo> database;
};
