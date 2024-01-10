#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <conio.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define FILENAME "students.txt"
#define MAX_USERS 1
#define USER_FILENAME "user.txt"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define XOR_KEY 0x7 // 异或加密密钥
void registerUser();

// 用户结构体
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int total_users = 0;

// 加载用户信息
void loadUsersFromFile() {
    FILE *file = fopen(USER_FILENAME, "r");
    if (file == NULL) {
        printf("无法加载用户信息文件。\n");
        registerUser();
        return;
    }

    while (!feof(file) && total_users < MAX_USERS) {
        fscanf(file, "%s %s\n", users[total_users].username, users[total_users].password);
        total_users++;
    }

    fclose(file);
    printf("用户信息已加载。\n");
}

// 保存用户信息
void saveUsersToFile() {
    FILE *file = fopen(USER_FILENAME, "w");
    if (file == NULL) {
        printf("无法保存用户信息到文件。\n");
        return;
    }

    for (int i = 0; i < total_users; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
    printf("用户信息已保存到文件。\n");
}

// 简单的异或加密函数
void simpleEncrypt(char *str) {
    char *ptr = str;
    while (*ptr != '\0') {
        *ptr = *ptr ^ XOR_KEY;
        ptr++;
    }
}

// 简单的异或解密函数
void simpleDecrypt(char *str) {
    char *ptr = str;
    while (*ptr != '\0') {
        *ptr = *ptr ^ XOR_KEY;
        ptr++;
    }
}

// 注册功能
void registerUser() {
    printf("\n====== 注册 ======\n");
    if (total_users >= MAX_USERS) {
        printf("用户数量已达上限，无法注册新用户。\n");
        return;
    }

    struct User new_user;

    printf("请输入用户名：");
    scanf("%s", new_user.username);

    printf("请输入密码：");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) // 输入回车结束输入密码
            break;
        if (ch == 8) { // 处理退格
            if (i > 0) {
                printf("\b \b"); // 退格删除一个字符的显示
                i--;
            }
        } else {
            new_user.password[i++] = ch;
            printf("*"); // 输出星号代替密码显示在屏幕上
        }
    }
    new_user.password[i] = '\0'; // 在密码字符串末尾添加结束符

    simpleEncrypt(new_user.password); // 对密码进行加密

    users[total_users++] = new_user;
    printf("\n");
    saveUsersToFile();
    printf("\n注册成功，程序将会在3秒后跳转到登录页\n");
    sleep(3); // 等待3秒
    system("cls");
}

// 登录功能
int loginUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("请输入用户名：");
    scanf("%s", username);

    printf("请输入密码：");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) // 输入回车结束输入密码
            break;
        if (ch == 8) { // 处理退格
            if (i > 0) {
                printf("\b \b"); // 退格删除一个字符的显示
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*"); // 输出星号代替密码显示在屏幕上
        }
    }
    password[i] = '\0'; // 在密码字符串末尾添加结束符

    simpleEncrypt(password); // 对输入的密码进行加密

    for (int i = 0; i < total_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            simpleDecrypt(users[i].password); // 如果登录成功，解密密码以便后续操作
            printf("\n登录成功，程序将在3秒后跳转到菜单\n");
            sleep(3); // 等待3秒
            system("cls");
            return 1; // 登录成功
        }
    }

    printf("\n用户名或密码错误。\n");
    return 0; // 登录失败
}

//建立学生数据结构体
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

//定义学生数据查找相关功能函数
int findstudent(int student_id) {
    int i;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            return 1;
        }
    }
    return 0;
}

//定义文件保存功能函数
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

//定义学生数据读取相关函数
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

//定义学生数据添加相关函数
void addStudent() {
    if (total_students >= MAX_STUDENTS) {
        printf("学生信息已满，无法添加。\n");
        return;
    }

    struct Student new_student;

    printf("请输入学生学号：");
    scanf("%d", &new_student.student_id);

    if (findstudent(new_student.student_id)) {
        printf("学生信息已存在");
        return;
    }

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

//定义学生学分显示功能相关函数
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

//定义学生学分修改相关功能函数
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

//定义学生数据删除功能相关函数
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

//定义可毕业学生查找功能相关函数
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

    loadUsersFromFile(); // 加载用户信息文件

    int login_attempts = 0;
    int logged_in = 0;

    while (login_attempts < 3 && !logged_in) {
        printf("\n====== 登录 ======\n");
        logged_in = loginUser();
        login_attempts++;
    }

    if (!logged_in) {
        printf("登录尝试次数过多，程序将在5秒后退出。\n");
        sleep(5);
        return 0;
    }

    loadStudentsFromFile();    //加载学生信息文件

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

        //输出目录并等待用户选择功能
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
}
