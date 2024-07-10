#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

float get_grade_point(char grade, char sign) {
    float grade_point = 0.0;
    switch (grade) {
        case 'A': grade_point = 4.0; break;
        case 'B': grade_point = 3.0; break;
        case 'C': grade_point = 2.0; break;
        case 'F': grade_point = 0.0; break;
        default: return -1; // 無效的成績
    }
    if (sign == '+') grade_point += 0.3;
    if (sign == '-') grade_point -= 0.3;
    return grade_point;
}

int main() {
    char buffer[MAX_INPUT_LENGTH];
    
    fgets(buffer, sizeof(buffer), stdin);

    size_t length = strlen(buffer);
    if (buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    }

    float total_grade_points = 0.0;
    int total_credits = 0;

    for (size_t i = 0; i < length; i++) {
        if (isdigit(buffer[i])) {
            // 獲取學分數
            int credits = buffer[i] - '0';
            i++;

            if (i < length && isalpha(buffer[i])) {
                // 獲取成績
                char grade = buffer[i];
                char sign = '\0';

                if (i + 1 < length && (buffer[i + 1] == '+' || buffer[i + 1] == '-')) {
                    sign = buffer[i + 1];
                    i++;
                }

                float grade_point = get_grade_point(grade, sign);
                if (grade_point >= 0) {
                    total_grade_points += credits * grade_point;
                    total_credits += credits;
                } else {
                    printf("Invalid grade detected: %c%c\n", grade, sign);
                }
            }
        }
    }

    if (total_credits > 0) {
        float gpa = total_grade_points / total_credits;
        printf("Total GPA: %.2f\n", gpa);
    } else {
        printf("No valid grades found.\n");
    }

    return 0;
}
