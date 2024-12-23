// Import libraries
#include <stdio.h> // Standard Input/Output library
#include <stdlib.h> // Standard library
#include <string.h> // Include string.h for strcspn

/**
 * This program is a to-do list that allows the user to add, list, mark as done, edit, and delete tasks.
 * It appends the tasks to a file calles "tasks.txt".
 * 
 * @author: Adam Abulmajid
 */
#define MAX_TASKS 100 // Maximum number of tasks

typedef struct Task {
    int id; // Task ID
    int done; // 1 if the task is done, 0 otherwise
    char description[256]; // Task description
}Task;

Task tasks[MAX_TASKS]; // Array of tasks
int task_count = 0; // Number of tasks

// Function for the to-do list
void add_task();
void list_tasks();
void mark_as_done();
void edit_task();
void delete_task();
void save_tasks();
void load_tasks();


// Add a new task 
void add_task() {
    if (task_count == MAX_TASKS) {
        printf("You have reached the maximum number of tasks.\n");
        return;
    }

    Task task; // Create a new task
    task.id = task_count + 1; // Increment the task ID
    printf("Enter task description: ");
    fgets(task.description, 256, stdin); // Read task description
    task.description[strcspn(task.description, "\n")] = 0; // Remove the newline character
    task.done = 0; // Not done

    tasks[task_count++] = task; // Add the task to the array
}

// List all tasks
void list_tasks() {
    if (task_count == 0) {
        printf("No tasks.\n");
        return;
    }

    printf("\nID\tDone\tDescription\n");
    for (int i = 0; i < task_count; i++) {
        Task task = tasks[i];
        printf("%d\t%s\t%s\n", task.id, task.done ? "Yes" : "No", task.description);
    }
}

// Mark a task as done
void mark_as_done() {
    int id;
    printf("Enter the task ID: ");
    scanf("%d", &id); // Read task ID

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            tasks[i].done = 1;
            printf("Task marked as done.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

// Edit a task
void edit_task() {
    int id;
    printf("Enter the task ID: ");
    scanf("%d", &id);

    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            printf("Enter new task description: ");
            getchar(); // Consume the newline character
            fgets(tasks[i].description, 256, stdin); // Read task description
            tasks[i].description[strcspn(tasks[i].description, "\n")] = 0; // Remove the newline character
            printf("Task updated.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

// Delete a task
void delete_task() {
    int id;
    printf("Enter the task ID: ");
    scanf("%d", &id);

//Instead of really deleting the task, I will move the tasks to the left
    for (int i = 0; i < task_count; i++) {
        if (tasks[i].id == id) {
            for (int j = i; j < task_count - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            task_count--;
            printf("Task deleted.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

// Save tasks to a file
void save_tasks() {
    FILE *file = fopen("tasks.txt", "w"); // Open file in write mode
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < task_count; i++) {
        Task task = tasks[i];
        fprintf(file, "%d;%d;%s\n", task.id, task.done, task.description);
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

// Load tasks from a file
void load_tasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        return;
    }
    // Read tasks from the file by reading the ID, done status, and description
    while (fscanf(file, "%d;%d;", &tasks[task_count].id, &tasks[task_count].done) == 2) {
        fgets(tasks[task_count].description, 256, file);
        tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = 0; // Remove the newline character
        task_count++;
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}

int main(){
    load_tasks(); // Load tasks from file
    int choice;

    do {
        printf("\n===== To-Do List =====\n");
        printf("1. Add Task\n");
        printf("2. List Tasks\n");
        printf("3. Mark as Done\n");
        printf("4. Edit Task\n");
        printf("5. Delete Task\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); 
        getchar(); // Consume the newline character (meaning the enter key)

        switch (choice) {
            case 1:
                add_task();
                break;
            case 2:
                list_tasks();
                break;
            case 3:
                mark_as_done();
                break;
            case 4:
                edit_task();
                break;
            case 5:
                delete_task();
                break;
            case 6:
                save_tasks();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
