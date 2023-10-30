```dataview
TABLE WITHOUT ID 
	file.link AS Project,
	Status,
	(length(filter(file.tasks.completed, (t) => t = true))) / (length(file.tasks.text)) * 100 AS "% Ready",
	(length(file.tasks.text)) AS All,
	(length(filter(file.tasks.completed, (t) => t = true))) AS Ready,
	(length(file.tasks.text)) - (length(filter(file.tasks.completed, (t) => t = true))) AS "in-progress"
FROM !#template and #docs  
```
