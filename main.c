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
#define XOR_KEY 0x7 // ��������Կ
void registerUser();

// �û��ṹ��
struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int total_users = 0;

// �����û���Ϣ
void loadUsersFromFile() {
    FILE *file = fopen(USER_FILENAME, "r");
    if (file == NULL) {
        printf("�޷������û���Ϣ�ļ���\n");
        registerUser();
        return;
    }

    while (!feof(file) && total_users < MAX_USERS) {
        fscanf(file, "%s %s\n", users[total_users].username, users[total_users].password);
        total_users++;
    }

    fclose(file);
    printf("�û���Ϣ�Ѽ��ء�\n");
}

// �����û���Ϣ
void saveUsersToFile() {
    FILE *file = fopen(USER_FILENAME, "w");
    if (file == NULL) {
        printf("�޷������û���Ϣ���ļ���\n");
        return;
    }

    for (int i = 0; i < total_users; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
    printf("�û���Ϣ�ѱ��浽�ļ���\n");
}

// �򵥵������ܺ���
void simpleEncrypt(char *str) {
    char *ptr = str;
    while (*ptr != '\0') {
        *ptr = *ptr ^ XOR_KEY;
        ptr++;
    }
}

// �򵥵������ܺ���
void simpleDecrypt(char *str) {
    char *ptr = str;
    while (*ptr != '\0') {
        *ptr = *ptr ^ XOR_KEY;
        ptr++;
    }
}

// ע�Ṧ��
void registerUser() {
    printf("\n====== ע�� ======\n");
    if (total_users >= MAX_USERS) {
        printf("�û������Ѵ����ޣ��޷�ע�����û���\n");
        return;
    }

    struct User new_user;

    printf("�������û�����");
    scanf("%s", new_user.username);

    printf("���������룺");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) // ����س�������������
            break;
        if (ch == 8) { // �����˸�
            if (i > 0) {
                printf("\b \b"); // �˸�ɾ��һ���ַ�����ʾ
                i--;
            }
        } else {
            new_user.password[i++] = ch;
            printf("*"); // ����ǺŴ���������ʾ����Ļ��
        }
    }
    new_user.password[i] = '\0'; // �������ַ���ĩβ��ӽ�����

    simpleEncrypt(new_user.password); // ��������м���

    users[total_users++] = new_user;
    printf("\n");
    saveUsersToFile();
    printf("\nע��ɹ������򽫻���3�����ת����¼ҳ\n");
    sleep(3); // �ȴ�3��
    system("cls");
}

// ��¼����
int loginUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("�������û�����");
    scanf("%s", username);

    printf("���������룺");
    int i = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == 13) // ����س�������������
            break;
        if (ch == 8) { // �����˸�
            if (i > 0) {
                printf("\b \b"); // �˸�ɾ��һ���ַ�����ʾ
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*"); // ����ǺŴ���������ʾ����Ļ��
        }
    }
    password[i] = '\0'; // �������ַ���ĩβ��ӽ�����

    simpleEncrypt(password); // �������������м���

    for (int i = 0; i < total_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            simpleDecrypt(users[i].password); // �����¼�ɹ������������Ա��������
            printf("\n��¼�ɹ���������3�����ת���˵�\n");
            sleep(3); // �ȴ�3��
            system("cls");
            return 1; // ��¼�ɹ�
        }
    }

    printf("\n�û������������\n");
    return 0; // ��¼ʧ��
}

//����ѧ�����ݽṹ��
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

//����ѧ�����ݲ�����ع��ܺ���
int findstudent(int student_id) {
    int i;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            return 1;
        }
    }
    return 0;
}

//�����ļ����湦�ܺ���
void saveStudentsToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("�޷�����ѧ����Ϣ���ļ���\n");
        return;
    }

    for (int i = 0; i < total_students; i++) {
        fprintf(file, "%d %s %s %s %d %d %d %d %d\n",
                students[i].student_id, students[i].name, students[i].class, students[i].enrollment_date,
                students[i].basic_credits, students[i].major_credits, students[i].elective_credits,
                students[i].humanities_credits, students[i].practical_credits);
    }

    fclose(file);
    printf("ѧ����Ϣ�ѱ��浽�ļ���\n");
}

//����ѧ�����ݶ�ȡ��غ���
void loadStudentsFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("�޷�����ѧ����Ϣ�ļ���\n");
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
    printf("ѧ����Ϣ�Ѽ��ء�\n");
}

//����ѧ�����������غ���
void addStudent() {
    if (total_students >= MAX_STUDENTS) {
        printf("ѧ����Ϣ�������޷���ӡ�\n");
        return;
    }

    struct Student new_student;

    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &new_student.student_id);

    if (findstudent(new_student.student_id)) {
        printf("ѧ����Ϣ�Ѵ���");
        return;
    }

    printf("������ѧ��������");
    scanf("%s", new_student.name);
    printf("������ѧ���༶��");
    scanf("%s", new_student.class);
    printf("������ѧ����ѧʱ�䣺");
    scanf("%s", new_student.enrollment_date);

    new_student.basic_credits = 0;
    new_student.major_credits = 0;
    new_student.elective_credits = 0;
    new_student.humanities_credits = 0;
    new_student.practical_credits = 0;

    students[total_students++] = new_student;
    printf("ѧ����Ϣ����ӡ�\n");
}

//����ѧ��ѧ����ʾ������غ���
void displayStudentCredits(int student_id) {
    int i;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            printf("ѧ�ţ�%d\n", students[i].student_id);
            printf("������%s\n", students[i].name);
            printf("�༶��%s\n", students[i].class);
            printf("��ѧʱ�䣺%s\n", students[i].enrollment_date);
            printf("������ѧ�֣�%d\n", students[i].basic_credits);
            printf("רҵ��ѧ�֣�%d\n", students[i].major_credits);
            printf("ѡ�޿�ѧ�֣�%d\n", students[i].elective_credits);
            printf("������γ�ѧ�֣�%d\n", students[i].humanities_credits);
            printf("ʵ���Կγ�ѧ�֣�%d\n", students[i].practical_credits);
            return;
        }
    }
    printf("δ�ҵ���ѧ����\n");
}

//����ѧ��ѧ���޸���ع��ܺ���
void modifyStudentCredits(int student_id) {
    int i;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            printf("�����������ѧ�֣�");
            scanf("%d", &students[i].basic_credits);
            printf("������רҵ��ѧ�֣�");
            scanf("%d", &students[i].major_credits);
            printf("������ѡ�޿�ѧ�֣�");
            scanf("%d", &students[i].elective_credits);
            printf("������������γ�ѧ�֣�");
            scanf("%d", &students[i].humanities_credits);
            printf("������ʵ���Կγ�ѧ�֣�");
            scanf("%d", &students[i].practical_credits);
            printf("ѧ����Ϣ���޸ġ�\n");
            return;
        }
    }
    printf("δ�ҵ���ѧ����\n");
}

//����ѧ������ɾ��������غ���
void deleteStudent(int student_id) {
    int i, found = 0;
    for (i = 0; i < total_students; i++) {
        if (students[i].student_id == student_id) {
            found = 1;
            for (int j = i; j < total_students - 1; j++) {
                students[j] = students[j + 1];
            }
            total_students--;
            printf("ѧ����Ϣ��ɾ����\n");
            break;
        }
    }
    if (!found) {
        printf("δ�ҵ���ѧ����\n");
    }
}

//����ɱ�ҵѧ�����ҹ�����غ���
void displayGraduates() {
    printf("�����ѧ�ֿ��Ա�ҵ��ѧ����\n");
    for (int i = 0; i < total_students; i++) {
        if (students[i].basic_credits >= 50 &&
            students[i].major_credits >= 50 &&
            students[i].elective_credits >= 24 &&
            students[i].humanities_credits >= 8 &&
            students[i].practical_credits >= 20) {
            printf("\n");
            printf("ѧ�ţ�%d\n", students[i].student_id);
            printf("������%s\n", students[i].name);
            printf("�༶��%s\n", students[i].class);
            printf("��ѧʱ�䣺%s\n", students[i].enrollment_date);
        }
    }
}

int main() {

    loadUsersFromFile(); // �����û���Ϣ�ļ�

    int login_attempts = 0;
    int logged_in = 0;

    while (login_attempts < 3 && !logged_in) {
        printf("\n====== ��¼ ======\n");
        logged_in = loginUser();
        login_attempts++;
    }

    if (!logged_in) {
        printf("��¼���Դ������࣬������5����˳���\n");
        sleep(5);
        return 0;
    }

    loadStudentsFromFile();    //����ѧ����Ϣ�ļ�

    int choice;

    while (1) {
        printf("\n====== ѧ�ֹ���ϵͳ�˵� ======\n");
        printf("1. ���ѧ��\n");
        printf("2. ��ʾѧ��ѧ��\n");
        printf("3. �޸�ѧ��ѧ��\n");
        printf("4. ɾ��ѧ��\n");
        printf("5. ��ʾ�����ѧ�ֿ��Ա�ҵ��ѧ��\n");
        printf("6. �������ݵ��ļ�\n");
        printf("7. �˳�\n");
        printf("\n==============================\n");
        printf("��ѡ�������");
        scanf("%d", &choice);
        system("cls");

        //���Ŀ¼���ȴ��û�ѡ����
        switch (choice) {
            case 1:
                printf("\n====== ���ѧ�� ======\n");
                addStudent();
                break;
            case 2: {
                int student_id;
                printf("\n====== ��ʾѧ��ѧ�� ======\n");
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &student_id);
                displayStudentCredits(student_id);
                break;
            }
            case 3: {
                int student_id;
                printf("\n====== �޸�ѧ��ѧ�� ======\n");
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &student_id);
                modifyStudentCredits(student_id);
                break;
            }
            case 4: {
                int student_id;
                printf("\n====== ɾ��ѧ�� ======\n");
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &student_id);
                deleteStudent(student_id);
                break;
            }
            case 5: {
                printf("\n====== ��ʾ�����ѧ�ֿ��Ա�ҵ��ѧ�� ======\n");
                displayGraduates();
                break;
            }
            case 6: {
                printf("\n====== ���ݱ��� ======\n");
                saveStudentsToFile();
                break;
            }
            case 7: {
                printf("\n====== �˳� ======\n");
                printf("�������˳���\n");
                saveStudentsToFile();
                printf("�˴��ڽ���5���ر�");
                sleep(5);
                exit(0);
                }
            default:
                printf("��������Ч��ѡ�\n");
        }
    }
}
