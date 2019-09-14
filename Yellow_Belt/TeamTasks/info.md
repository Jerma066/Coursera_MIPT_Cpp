Тренировочное задание по программированию: Трекер задач	
	
	Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач команды разработчиков:
	Метод PerformPersonTasks должен реализовывать следующий алгоритм:

		1. Рассмотрим все не выполненные задачи разработчика person.
		
		2. Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все задачи 
		в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
		   
		3. Рассмотрим первые task_count задач и переведём каждую из них в следующий статус 
		в соответствии с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE.
		
		4. Вернём кортеж из двух элементов: информацию о статусах обновившихся задач 
		(включая те, которые оказались в статусе DONE) и информацию о статусах остальных не 
		выполненных задач.
		
		Гарантируется, что task_count является положительным числом. Если task_count превышает 
		текущее количество невыполненных задач разработчика, достаточно считать, что task_count 
		равен количеству невыполненных задач: дважды обновлять статус какой-либо задачи в этом 
		случае не нужно.

		Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, 
		не имеющего задач.