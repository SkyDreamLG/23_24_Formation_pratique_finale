#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define FILENAME "students.txt"

struct Student {
    int student_id;
    char name[MAX_NAME_LENGTH];
    char class[MAX_NAME_LENGTH];
    char enrollment_date[MAX_NAME_LENGTH];
    int basic_credits;
    int major_credits;
    int elective_credits;
    int humanities_credits;
    int practical_credits;
};

struct Student students[MAX_STUDENTS];
int total_students = 0;

void saveStudentsToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("无法保存学生信息到文件。\n");
        return;
    }

    for (int i = 0; i < total_students; i++) {
        fprintf(file, "%d %s %s %s %d %d %d %d %d\n",
                students[i].student_id, students[i].name, students[i].class, students[i].enrollment_date,
                students[i].basic_credits, students[i].major_credits, students[i].elective_credits,
                students[i].humanities_credits, students[i].practical_credits);
    }

    fclose(file);
    printf("学生信息已保存到文件。\n");
}

void loadStudentsFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("无法加载学生信息文件。\n");
        return;
    }

    while (!feof(file) && total_students < MAX_STUDENTS) {
        fscanf(file, "%d %s %s %s %d %d %d %d %d\n",
               &students[total_students].student_id, students[total_students].name,
               students[total_students].class, students[total_students].enrollment_date,
               &students[total_students].basic_credits, &students[total_students].major_credits,
               &students[total_students].elective_credits, &students[total_students].humanities_credits,
               &students[total_students].practical_credits);
        total_students++;
    }

    fclose(file);
    printf("学生信息已加载。\n");
}

void addStudent() {
    if (total_students >= MAX_STUDENTS) {
        printf("学生信息已满，无法添加。\n");
        return;
    }

    struct Student new_student;

    printf("请输入学生学号：");
    scanf("%d", &new_student.student_id);
    printf("请输入学生姓名：");
    scanf("%s", new_student.name);
    printf("请输入学生班级：");
    scanf("%s", new_student.class);
    printf("请输入学生入学时间：");
    scanf("%s", new_student.enrollment_date);

    new_student.basic_credits = 0;
    new_student.major_credits = 0;
    new_student.elective_credits = 0;
    new_student.humanities_credits = 0;
    new_student.practical_credits = 0;

    students[total_students++] = new_student;
    printf("学生信息已添加。\n");
}

void displayStudentCredits(int student_id) {
    int i;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            printf("学号：%d\n", students[i].student_id);
            printf("姓名：%s\n", students[i].name);
            printf("班级：%s\n", students[i].class);
            printf("入学时间：%s\n", students[i].enrollment_date);
            printf("基础课学分：%d\n", students[i].basic_credits);
            printf("专业课学分：%d\n", students[i].major_credits);
            printf("选修课学分：%d\n", students[i].elective_credits);
            printf("人文类课程学分：%d\n", students[i].humanities_credits);
            printf("实践性课程学分：%d\n", students[i].practical_credits);
            return;
        }
    }
    printf("未找到该学生。\n");
}

void modifyStudentCredits(int student_id) {
    int i;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            printf("请输入基础课学分：");
            scanf("%d", &students[i].basic_credits);
            printf("请输入专业课学分：");
            scanf("%d", &students[i].major_credits);
            printf("请输入选修课学分：");
            scanf("%d", &students[i].elective_credits);
            printf("请输入人文类课程学分：");
            scanf("%d", &students[i].humanities_credits);
            printf("请输入实践性课程学分：");
            scanf("%d", &students[i].practical_credits);
            printf("学分信息已修改。\n");
            return;
        }
    }
    printf("未找到该学生。\n");
}

void deleteStudent(int student_id) {
    int i, found = 0;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            found = 1;
            for (int j = i; j < total_students - 1; j++) {
                students[j] = students[j + 1];
            }
            total_students--;
            printf("学生信息已删除。\n");
            break;
        }
    }
    if (!found) {
        printf("未找到该学生。\n");
    }
}

void displayGraduates() {
    printf("已完成学分可以毕业的学生：\n");
    for (int i = 0; i < total_students; i++) {
        if (students[i].basic_credits >= 50 &&
            students[i].major_credits >= 50 &&
            students[i].elective_credits >= 24 &&
            students[i].humanities_credits >= 8 &&
            students[i].practical_credits >= 20) {
            printf("\n");
            printf("学号：%d\n", students[i].student_id);
            printf("姓名：%s\n", students[i].name);
            printf("班级：%s\n", students[i].class);
            printf("入学时间：%s\n", students[i].enrollment_date);
        }
    }
}

int main() {
    loadStudentsFromFile();

    int choice;
    while (1) {
        printf("\n====== 学分管理系统菜单 ======\n");
        printf("1. 添加学生\n");
        printf("2. 显示学生学分\n");
        printf("3. 修改学生学分\n");
        printf("4. 删除学生\n");
        printf("5. 显示已完成学分可以毕业的学生\n");
        printf("6. 保存数据到文件\n");
        printf("7. 退出\n");
        printf("\n==============================\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
            case 1:
                printf("\n====== 添加学生 ======\n");
                addStudent();
                break;
            case 2: {
                int student_id;
                printf("\n====== 显示学生学分 ======\n");
                printf("请输入学生学号：");
                scanf("%d", &student_id);
                displayStudentCredits(student_id);
                break;
            }
            case 3: {
                int student_id;
                printf("\n====== 修改学生学分 ======\n");
                printf("请输入学生学号：");
                scanf("%d", &student_id);
                modifyStudentCredits(student_id);
                break;
            }
            case 4: {
                int student_id;
                printf("\n====== 删除学生 ======\n");
                printf("请输入学生学号：");
                scanf("%d", &student_id);
                deleteStudent(student_id);
                break;
            }
            case 5: {
                printf("\n====== 显示已完成学分可以毕业的学生 ======\n");
                displayGraduates();
                break;
            }
            case 6: {
                printf("\n====== 数据保存 ======\n");
                saveStudentsToFile();
                break;
            }
            case 7: {
                printf("\n====== 退出 ======\n");
                printf("程序已退出。\n");
                saveStudentsToFile();
                printf("此窗口将在5秒后关闭");
                sleep(5);
                exit(0);
                }
            default:
                printf("请输入有效的选项。\n");
        }
    }

    return 0;
}
