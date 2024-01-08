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

void addStudent() {
    if (total_students >= MAX_STUDENTS) {
        printf("ѧ����Ϣ�������޷���ӡ�\n");
        return;
    }

    struct Student new_student;

    printf("������ѧ��ѧ�ţ�");
    scanf("%d", &new_student.student_id);
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
    loadStudentsFromFile();

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

    return 0;
}
