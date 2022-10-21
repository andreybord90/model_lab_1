#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))

int n, res;
//float arr_x[] = {0.00, 0.15, 0.30, 0.45, 0.60, 0.75, 0.90, 1.05};
float arr_x[] = {-0.50, -0.25, 0.0, 0.25, 0.50, 0.75,  1.0};
const  float arr_y[] = {0.707, 0.924, 1.0, 0.924, 0.707, 0.383, 0.0, -0.552430};
//const  float arr_y[] = {1.00, 0.838771, 0.655336, 0.450447, 0.225336, -0.018310, -0.278390, -0.552430};
//const  float yP[] = {-1.00, -1.14944, -1.29552,-1.43497,-1.56464, -1.68164, -1.78333, -1.86742};

float arg;
typedef struct data { float value; float x1; float x2; } Values;

int getStart(int number);
Values * getColumn1();
Values * getColumns( Values * node, int length);
float * getNodes();
float getElementPolinome(int i, float * params, float x);
float getPolinome(float * params, float x);

int main() {

    int number=0;

    printf("Введите n: ");
    scanf("%d", &n);

    printf("Введите x: ");
    scanf("%f", &arg);

    for(int i =0; i < ARRAY_SIZE(arr_x); i++){
        if(arr_x[i] < arg){
            number = i;
        }
    }

    res = getStart( number); // получаем индекс первого элемента таблицы значений вблизи x
    float * result = getNodes( ); // рассчитываем значения разделенных разностей
    float x = getPolinome(result, arg); // вычислим полином для заданного x

    printf("Результат x=  %f  \n", x);

    return 0;
}

int getStart(int number) {
    int result;

    if((n+1)/2 > number){
        result = 0;
        return result;
    }
    if(number + (n+1)/2 > ARRAY_SIZE(arr_x)-1){
        result = ARRAY_SIZE(arr_x) - 1 - n;
        return result;
    }
    result = number - (n+1)/2;

    return result;
}

Values * getColumn1(){
    Values *nodes = calloc(n, sizeof(Values));
    for (int i = 0; i < n; i++) {
        nodes[i].value = (arr_y [ i + res ] - arr_y[ i + 1 + res ]) / (arr_x[i + res] - arr_x[ i + 1 + res]);
        nodes[i].x1 = arr_x[ i + res];
        nodes[i].x2 = arr_x[i + 1 + res];
    }
    return nodes;
}

Values * getColumns( Values * node, int length){
    Values *nodes = calloc(length ,sizeof(Values));

    for (int i = 0; i < length; i++) {
        nodes[i].value = (node[i].value-node[i+1].value)/(node[i].x1 - node[i+1].x2);
        nodes[i].x1 = arr_x[res + i ];
        nodes[i].x2 = arr_x[res + i + 1 + n - length];
    }

    return nodes;
}

float *getNodes() {
    float *ptr = calloc(n+1, sizeof(float));
    ptr[0] = arr_y[res];

    Values *column1 = getColumn1( res);
    ptr[1] = column1[0].value;

    Values * temp;
    temp = column1;

    for (int i = 2; i < n+1; ++i) {
        Values * columns =  getColumns(temp , n+1-i);
        ptr[i] = columns[0].value;
        temp = columns;
    }
    free(column1);

    return ptr;
}

float getElementPolinome(int i, float * params, float x){
    float mult = params[i];
    for (int j = 0; j < i; j++) {
        mult *= x-arr_x[j+ res];
    }

    return mult;
}

float getPolinome(float * params,  float x){
    float sum = params[0];
    for (int i = 1; i < n+1; i++) {
        sum+=getElementPolinome(i, params, x);
    }

    return sum;
}